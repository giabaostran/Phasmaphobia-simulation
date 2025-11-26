#include "ghost.h"

enum GhostType ghost_random() {
    enum GhostType ghost_list[] = {
        GH_POLTERGEIST,
        GH_THE_MIMIC,
        GH_HANTU,
        GH_JINN,
        GH_PHANTOM,
        GH_BANSHEE,
        GH_GORYO,
        GH_BULLIES,
        GH_MYLING,
        GH_OBAKE,
        GH_YUREI,
        GH_ONI,
        GH_MOROI,
        GH_REVENANT,
        GH_SHADE,
        GH_ONRYO,
        GH_THE_TWINS,
        GH_DEOGEN,
        GH_THAYE,
        GH_YOKAI,
        GH_WRAITH,
        GH_RAIJU,
        GH_MARE,
        GH_SPIRIT,
    };
    return ghost_list[rand() % (sizeof(ghost_list) / sizeof(ghost_list[0]) - 1)];
}

void ghost_init(struct House *house, struct Ghost *ghost) {
    // Initialization
    ghost->id = DEFAULT_GHOST_ID;
    ghost->type = ghost_random(); // This value is hard-coded for now
    ghost->boredom = 0;
    ghost->has_exit = false; // determine if a ghost has exit the simulation
    int r = (rand() % (house->room_count - 1)) + 1; // pick a random room to spaw the ghost in, except the exit room
    // Randomly spawn ghost to a room
    ghost->current_room = &house->rooms[r];
    ghost->current_room->ghost = ghost;
    // Log ghost initialization
    log_ghost_init(ghost->id, ghost->current_room->name, ghost->type);
}

bool ghost_find_hunter(struct Ghost *ghost) {
    // return if any hunter is in the room
    return ghost->current_room->hunter_count > 0;
}

void ghost_scare(struct Ghost *ghost) {
    // Ghost is scaring someone, very excited thusby
    ghost->boredom = 0;
    int option = rand() % 2;
    // Ghost chooses to stay still or leave a piece of evidence
    switch (option) {
        case 0: // Haunt the current room
            ghost_haunt(ghost);
            break;

        default: // Ghost idle doing nothing
            ghost_idle(ghost);
            break;
    }
}

void ghost_haunt(struct Ghost *ghost) {
    struct Room *current_room = ghost->current_room;
    // Randomly choose one of the 3 evidence of the ghost to leave at the room
    unsigned char count = rand() % 3 + 1;
    // Create a mask
    enum EvidenceType mask = 1;
    // Use bitwise op to extract the chosen evidence type
    while (true) {
        if (mask & ghost->type)
            if (--count == 0)
                break;
        mask <<= 1;
    }
    // Apply the effect to the room
    current_room->evidence |= mask;
    log_ghost_evidence(ghost->id, ghost->boredom, current_room->name, mask);
};

void ghost_move(struct House *house, struct Ghost *ghost) {
    struct Room *current_room = ghost->current_room;
    int rand_room;
    // Pick a random room to move to
    // But if the room is the starting point (saferoom) then we must pick again
    while (current_room->connected_rooms[(rand_room = rand() % current_room->connection_count)] == house->
           starting_room);

    // Clear its presence from the room it just exited
    current_room->ghost = NULL;
    // Move the ghost to that next room
    ghost->current_room = current_room->connected_rooms[rand_room];
    // Make ghost presensence known to the room it just moves to
    ghost->current_room->ghost = ghost;
    // Log it down
    log_ghost_move(ghost->id, ghost->boredom, current_room->name, ghost->current_room->name);
}

void ghost_exit(struct Ghost *ghost) {
    struct Room *current_room = ghost->current_room;
    // Remove ghost presence from the room
    current_room->ghost = NULL;
    // Ghost no longer in any room
    ghost->current_room = NULL;
    // Log
    ghost->has_exit = true;
    log_ghost_exit(ghost->id, ghost->boredom, current_room->name);
}

void ghost_idle(struct Ghost *ghost) {
    // Literally doing nothing
    log_ghost_idle(ghost->id, ghost->boredom, ghost->current_room->name);
}

void ghost_take_turn(struct House *house, struct Ghost *ghost) {
    // 1. ENFORCED ACTION: if any hunter is presenting in the room, ghost must scare them
    if (ghost->current_room->hunter_count > 0) {
        ghost_scare(ghost);
        return;
    }
    // 2. No hunter presents, ghost becomes more bored. If reached max boredom, it leaves the house
    else if (++ghost->boredom >= ENTITY_BOREDOM_MAX) {
        ghost_exit(ghost);
        return;
    }

    // 3. Picking alternate activities for the ghost
    int option = rand() % 3;
    switch (option) {
        case 0: // Haunt the current room
            ghost_haunt(ghost);
            break;

        case 1: // Move on to the next room
            ghost_move(house, ghost);
            break;

        default: // Ghost idle doing nothing
            ghost_idle(ghost);
    }
}
