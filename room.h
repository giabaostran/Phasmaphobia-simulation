#include "defs.h"
#include <string.h>

/**
 * COMPLETE: Initializes a Room structure with the given name and exit flag.
 *
 * @param room     Pointer to the Room struct to initialize.
 * @param name     Null-terminated string representing the room's name.
 * @param is_exit  Boolean indicating whether the room is an exit.
 *
 * @return         Nothing
 */
void room_init(struct Room *room, const char *name, bool is_exit);

/**
 * COMPLETE: Connect two rooms by adding reference from one to another.
 *
 * @param a     Pointer to the Room struct.
 * @param b     Pointer to the Room struct.
 *
 * @return         Nothing
 */
void rooms_connect(struct Room *a, struct Room *b);

