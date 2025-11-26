#include "room.h"

void room_init(Room *room, const char *name, bool is_exit) {
    room->connection_count = 0;
    room->ghost = NULL;
    room->is_exit = is_exit;
    room->hunter_count = 0;
    strcpy(room->name, name);
};

void rooms_connect(Room *a, Room *b) {
    a->connected_rooms[a->connection_count++] = b;
    b->connected_rooms[b->connection_count++] = a;
}

void room_remove_hunter(Room *room, Hunter *hunter) {
    // Find the hunter inside the room
    for (size_t i = 0; i < MAX_ROOM_OCCUPANCY; i++) {
        // if matches
        if (room->hunters[i] == hunter) {
            // Set the hunter at the index to be null
            room->hunters[i] = NULL;
            // Shift the other hunters
            for (size_t j = i; j < MAX_ROOM_OCCUPANCY - 1; j++)
                room->hunters[j] = room->hunters[j + 1];
            room->hunters[MAX_ROOM_OCCUPANCY - 1] = NULL;
            room->hunter_count--;
            break;
        }
    }
    // The hunter no longer be in the current room
    hunter->current_room = NULL;
}

void room_add_hunter(Room *room, Hunter *hunter) {
    room->hunters[room->hunter_count++] = hunter;
    hunter->current_room = room;
}
