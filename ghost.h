#include "defs.h"
#include <stdlib.h>

void ghost_init(struct House *house, struct Ghost *ghost);

void handle_ghost_turn(struct Ghost *ghost);

void ghost_move(struct Ghost *ghost);

void ghost_haunt(struct Ghost *ghost);

void ghost_scare(struct Ghost *ghost);

void ghost_exit(struct Ghost *ghost);

/**
 * COMPLETE: Check if any hunter is presenting in the room.
 *
 * @param room     Pointer to the Room struct.
 *
 * @return         Boolean if any it has any hunter
 */
bool ghost_find_hunter(struct Room *room);
