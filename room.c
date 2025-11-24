#include "room.h"


void room_init(struct Room *room, const char *name, bool is_exit)
{
    room->connection_count = 0;
    room->ghost = NULL;
    room->is_exit = is_exit;
    room->hunter_count = 0;
    strcpy(room->name, name);
};

void rooms_connect(struct Room *a, struct Room *b)
{
    a->connected_rooms[a->connection_count++] = b;
    b->connected_rooms[b->connection_count++] = a;
}

