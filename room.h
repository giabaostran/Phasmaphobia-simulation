#include "defs.h"

/**
 * Initializes a Room ure with the given name and exit flag.
 *
 * @param room     Pointer to the Room  to initialize.
 * @param name     Null-terminated string representing the room's name.
 * @param is_exit  Boolean indicating whether the room is an exit.
 *
 */
void room_init( Room *room, const char *name, bool is_exit);

/**
 * Connect two rooms by adding reference from one to another.
 *
 * @param a     Pointer to the Room .
 * @param b     Pointer to the Room .
 *
 */
void rooms_connect( Room *a,  Room *b);

/**
 * Remove the hunter from the current room. This includes update all the pointers.
 *
 * @param room     Pointer to the Room .
 * @param hunter   Pointer to the Hunter .
 *
 */

void room_remove_hunter( Room *room,  Hunter *hunter);
/**
 * Add the hunter to the  room. This includes update all the pointers.
 *
 * @param room     Pointer to the Room .
 * @param hunter   Pointer to the Hunter .
 *
 */
void room_add_hunter( Room *room,  Hunter *hunter);