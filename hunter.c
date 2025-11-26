#include "hunter.h"
#include "room.h"

void hunter_init(House *house, char *name, int id) {
    Hunter *hunter = malloc(sizeof(Hunter));
    strcpy(hunter->name, name);
    hunter->id = id;
    hunter->boredom = hunter->fear = 0;
    hunter->has_exit = false;
    hunter->starting_room = hunter->current_room = house->starting_room;
    hunter->case_file = house->case_file;
    hunter->device = hunter_receives_device();
    hunter->found_evidence = false;

    RoomNode *room_node = malloc(sizeof(RoomNode));
    room_node->room = house->starting_room;
    room_node->next = NULL;
    hunter->room_stack.head = room_node;

    HunterNode *hunter_node = malloc(sizeof(HunterNode));
    hunter_node->next = house->hunters.head;
    hunter_node->hunter = hunter;
    house->hunters.head = hunter_node;
    // This only exception allow more hunter than the limit to be in the room
    house->starting_room->hunters[house->starting_room->hunter_count++] = hunter_node->hunter;
    house->hunter_count++;
    log_hunter_init(hunter->id, hunter->current_room->name, hunter->name, hunter->device);
}

EvidenceByte hunter_receives_device() {
    return 1 << (rand() % EVIDENCE_TYPE_COUNT);
}

void hunter_gets_scared(Hunter *hunter) {
    hunter->fear++;
    // They are too scared to be bored
    hunter->boredom = 0;
}

void hunter_swap_device(Hunter *hunter) {
    EvidenceByte new_device;
    EvidenceByte old_device = hunter->device;
    // Keep asking for a new weapon while it is the same as what the hunter is having
    while ((new_device = hunter_receives_device()) == hunter->device);
    // Give weapon to the hunter
    hunter->device = new_device;
    // Reset the flag indicating he hasn't found any evidence with the new device
    hunter->found_evidence = false;
    // Log
    log_swap(hunter->id, hunter->boredom, hunter->fear, old_device, new_device);
}

void hunter_take_turn(House *house, Hunter *hunter) {
    // 0. If the hunter is at the exit/van
    if (hunter->current_room->is_exit) {
        // If the ghost has been identified, then the hunter can now exit
        if (hunter->case_file->solved) {
            // Set hunter exit reason
            hunter->exit_reason = LR_EVIDENCE;
            // Exit
            house->successful_exit_count++;
            hunter_exit(hunter);
            return;
        }
        // If the current device has been used to find an evidence, swap it
        if (hunter->found_evidence) {
            hunter_swap_device(hunter);
        }
        // Clear his travel history and start fresh
        hunter_reset_path(hunter);
    }

    // 1. If there is a ghost in the current room
    if (hunter->current_room->ghost != NULL) {
        // Hunter gets scared
        hunter_gets_scared(hunter);
        // If the hunter is too scared he will leave the simulation
        if (hunter->fear >= HUNTER_FEAR_MAX) {
            hunter->exit_reason = LR_AFRAID;
            hunter_exit(hunter);
            // Increment number of hunter who "gave up"
            house->failed_exit_count++;
            return;
        }
    }

    // 2. If the hunter is too bored he will leave the simulation
    else if (++hunter->boredom >= ENTITY_BOREDOM_MAX) {
        hunter->exit_reason = LR_BORED;
        hunter_exit(hunter);
        // Increment number of hunter who "gave up"
        house->failed_exit_count++;
        return;
    }

    // 3. If user still brave enough to stay or not too bored
    hunter_get_evidence(hunter);

    // 4. Time to keep moving
    hunter_move(hunter);
}

void hunter_exit(Hunter *hunter) {
    Room *current_room = hunter->current_room;
    // remove hunter from the room they're in
    room_remove_hunter(hunter->current_room, hunter);
    // set hunter status
    hunter->has_exit = true;
    // Remove their travel history because it is not used anymore
    hunter_clean_path(hunter);
    // Log
    log_exit(hunter->id, hunter->boredom, hunter->fear, current_room->name, hunter->device, hunter->exit_reason);
}

void hunter_clean_path(Hunter *hunter) {
    RoomNode *agent = hunter->room_stack.head;
    while (agent != NULL) {
        RoomNode *next = agent->next; // save the link first
        free(agent);
        agent = next;
    }
}

void hunter_reset_path(Hunter *hunter) {
    hunter_clean_path(hunter);
    RoomNode *new_node = malloc(sizeof(RoomNode));
    new_node->room = hunter->starting_room;
    new_node->next = NULL;
    hunter->room_stack.head = new_node;
}

Room *hunter_pick_random_room(Room *room) {
    int rand_room = rand() % room->connection_count;
    return room->connected_rooms[rand_room];
}

void hunter_move(Hunter *hunter) {
    Room *old_room = hunter->current_room;
    Room *new_room;
    bool shortcut_found = false;

    // If case is solved , the hunter make their way back to the exit room. Or if evidence is found using current tool, go back to the exit/van to swap
    if (hunter->case_file->solved || hunter->found_evidence) {
        // Proactively check if the current has any shortcut to the exit/van
        Room *current_room = hunter->current_room;
        for (int i = 0; i < current_room->connection_count; ++i) {
            if (current_room->connected_rooms[i] == hunter->starting_room && hunter->starting_room->hunter_count <
                MAX_ROOM_OCCUPANCY) {
                new_room = hunter->starting_room;
                shortcut_found = true;
                break;
            }
        }

        if (!shortcut_found) {
            // Store the head because we will lose track of it
            RoomNode *old_room_node = hunter->room_stack.head;
            // If the next room is full then we don't move
            if (old_room_node->next->room->hunter_count >= MAX_ROOM_OCCUPANCY)
                return;
            // Remove reference to the top room on the stack
            hunter->room_stack.head = old_room_node->next;
            free(old_room_node);
            new_room = hunter->room_stack.head->room;
        }
    } else {
        // case is not solved so keep moving the rooms in search of evidence
        // Pick a connected room randomly
        new_room = hunter_pick_random_room(old_room);
        // If the next room is full then we don't move
        if (new_room->hunter_count >= MAX_ROOM_OCCUPANCY)
            return;
        // Add the new room to his path history
        RoomNode *new_room_node = malloc(sizeof(RoomNode));
        new_room_node->room = new_room;
        new_room_node->next = hunter->room_stack.head;
        hunter->room_stack.head = new_room_node;
    }

    // Remove hunter from old room
    room_remove_hunter(old_room, hunter);

    // Move hunter
    room_add_hunter(new_room, hunter);

    // Log move
    if (new_room->is_exit)
        log_return_to_van(hunter->id, hunter->boredom, hunter->fear, old_room->name, hunter->device,
                          hunter->case_file->solved);
    else
        log_move(hunter->id, hunter->boredom, hunter->fear, old_room->name, new_room->name, hunter->device);
}


void hunter_get_evidence(Hunter *hunter) {
    EvidenceType evidence = hunter->device & hunter->current_room->evidence;
    CaseFile *case_file = hunter->case_file;
    // If no evidence is found
    if (evidence == 0)
        return;
    // Clear the evidence from the room
    hunter->current_room->evidence &= ~evidence;
    // If such evidence is already recorded, ignore it
    if ((case_file->collected & evidence) != 0)
        return;
    // Record the evidence in the log book
    case_file->collected |= evidence;
    // Mark hunter has found some evidence with current tool
    hunter->found_evidence = true;
    // If all evidence has been recoreded then case is solved
    if (++case_file->evidence_found == EVIDENCE_PER_GHOST)
        case_file->solved = true;
    log_evidence(hunter->id, hunter->boredom, hunter->fear, hunter->current_room->name, hunter->device);
}
