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

void room_remove_hunter(struct Room *room, struct Hunter *hunter)
{
    // Find the hunter inside room
    for (size_t i = 0; i < MAX_ROOM_OCCUPANCY; i++)
    {
        if (room->hunters[i] == hunter)
        {
            room->hunters[i] = NULL;
            for (size_t j = i; j < MAX_ROOM_OCCUPANCY - 1; j++)
                room->hunters[j] = room->hunters[j + 1];
            room->hunters[MAX_ROOM_OCCUPANCY - 1] = NULL;
            room->hunter_count--;
            break;
        }
    }
    hunter->current_room = NULL;
}
