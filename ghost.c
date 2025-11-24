#include "ghost.h"


// Array-based ghost list for random access
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

void ghost_init(struct House *house, struct Ghost *ghost)
{
    // Initialization
    ghost->id = DEFAULT_GHOST_ID;
    ghost->type = ghost_list[rand() % GHOST_TYPE_COUNT]; // This value is hard-coded for now
    ghost->boredom = 0;
    ghost->has_exit = false; // determine if a ghost has exit the si
    int r = rand() % house->room_count;
    // Randomly spawn ghost to a room
    ghost->current_room = &house->rooms[r];

    // Log ghost initialization
    log_ghost_init(ghost->id, ghost->current_room->name, ghost->type);
}
bool ghost_find_hunter(struct Ghost *ghost)
{
    // return if any hunter is in the room
    return ghost->current_room->hunter_count > 0;
}

void ghost_scare(struct Ghost *ghost)
{
    // Ghost is scaring someone, very excited thusby
    ghost->boredom = 0;
}

void ghost_haunt(struct Ghost *ghost)
{

    struct Room *current_room = ghost->current_room;
    // current_room->evidence = ghost;

    // Randomly choose one of the evidence of the ghost to leave at the room
    unsigned char count = rand() % 3 + 1;
    // Create a mask
    enum EvidenceType mask = 1;
    // Use bitwise op to extract the chosen evidence type
    while (true)
    {
        if (mask & ghost->type)
            if (--count == 0)
                break;
        mask <<= 1;
    }
    log_ghost_evidence(ghost->id, ghost->boredom, current_room->name, mask);
};

void ghost_move(struct Ghost *ghost)
{
    struct Room *current_room = ghost->current_room;
    // Pick a random room to move to
    int rand_room = rand() % current_room->connection_count;
    // Move the ghost to the next-room
    ghost->current_room = current_room->connected_rooms[rand_room];
    // Make ghost presensence known to the room it just moves to
    ghost->current_room->ghost = ghost;
    // Clear its presence from the room it just exited
    current_room->ghost = NULL;
    // Log it down
    log_ghost_move(ghost->id, ghost->boredom, current_room->name, ghost->current_room->name);
}

void ghost_exit(struct Ghost *ghost)
{
    ghost->has_exit = true;
    ghost->current_room = NULL;
    log_ghost_exit(ghost->id, ghost->boredom, ghost->current_room->name);
}

void ghost_idle(struct Ghost *ghost)
{
    log_ghost_idle(ghost->id, ghost->boredom, ghost->current_room->name);
}

void ghost_take_turn(struct Ghost *ghost)
{

    struct Room *room = ghost->current_room;

    // 1. ENFORCED ACTION: if any hunter is presenting in the room, ghost must scare them
    if (ghost->current_room->hunter_count > 0)
    {
        printf("{}");
        ghost_scare(ghost);
        return;
    }
    // 2. No hunter presents, ghost becomes more bored. If reached max boredom, it leaves the house
    else if (++ghost->boredom >= ENTITY_BOREDOM_MAX)
    {
        ghost_exit(ghost);
        return;
    }

    // 3. Picking alternate activities for the ghost
    int option = rand() % 3;
    switch (option)
    {
    case 0: // Haunt the current room
        ghost_haunt(ghost);
        break;

    case 1: // Move to the next room
        ghost_move(ghost);
        break;

    default: // Ghost idle doing nothing
        ghost_idle(ghost);
        break;
    }
}
