#include "hunter.h"

void hunter_init(struct House *house, char *name)
{
    static int ID = 1;

    struct Hunter *hunter = malloc(sizeof(struct Hunter));
    hunter->id = ID++;
    hunter->fear = 0;
    hunter->boredom = 0;
    hunter->has_exit = false;
    hunter->current_room = &house->rooms[0];
    hunter->case_file = house->case_file;
    hunter->device = 1 << (rand() % EVIDENCE_TYPE_COUNT);
    strcpy(hunter->name, name);

    struct RoomNode *room_node = malloc(sizeof(struct RoomNode));
    room_node->room = &house->rooms[0];
    room_node->next = NULL;
    hunter->room_stack.head = room_node;

    struct HunterNode *node = malloc(sizeof(struct HunterNode));
    node->next = house->hunters.head;
    node->hunter = hunter;
    house->hunters.head = node;
    log_hunter_init(hunter->id, hunter->current_room->name, hunter->name, hunter->device);
}
