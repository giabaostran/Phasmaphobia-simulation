#include "defs.h"

/**
 * COMPLETE: Initializes a Room ure with the given name and exit flag.
 *
 * @param room     Pointer to the Room  to initialize.
 * @param name     Null-terminated string representing the room's name.
 * @param is_exit  Boolean indicating whether the room is an exit.
 *
 * @return         Nothing
 */
void room_init( Room *room, const char *name, bool is_exit);

/**
 * COMPLETE: Connect two rooms by adding reference from one to another.
 *
 * @param a     Pointer to the Room .
 * @param b     Pointer to the Room .
 *
 * @return         Nothing
 */
void rooms_connect( Room *a,  Room *b);

void room_remove_hunter( Room *room,  Hunter *Hunter);

void room_add_hunter( Room *room,  Hunter *hunter);