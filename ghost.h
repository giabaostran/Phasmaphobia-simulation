#include "defs.h"

/**
 * Initializes a Ghost ure and spawns it in a random room.
 *
 * @param house  Pointer to the House containing the rooms.
 * @param ghost  The ghost ure to initialize.
 *
 * @return       Nothing.
 */
void ghost_init( House *house,  Ghost *ghost);

/**
 * Simulate ghost's behavior in a turn.
 *
 * Behavior rules:
 * - If 1 or more hunter are present in the ghost's current room, it ghost must scare them and be unable to move.
 * - Else, the ghost gains boredom, and may exit if it... is fed up.
 * - If still active, the ghost either haunts the room or moves to another one or stay doing nothing.
 *
 * @param ghost  Pointer to the ghost acting this turn.
 */
void ghost_take_turn( House *house,  Ghost *ghost);

/**
 * Moves the ghost from its current room to one of the connected rooms randomly.
 *
 * @param ghost  The ghost that will move.
 *
 * @return       Nothing. The ghost's current_room is updated.
 */
void ghost_move( House *house,  Ghost *ghost);

/**
 *  Simulate ghost behavior of haunting a room, leaving a permanent artifact to the room its currently in
 *
 * @param ghost  The ghost performing a haunt action.
 */
void ghost_haunt( Ghost *ghost);

/**
 * Performs a scare action on the huntersin the ghost's current room.
 *
 * @param ghost  The ghost performing the scare.
 *
 * @return       Nothing. Affected hunters will have their fear updated.
 */
void ghost_scare( Ghost *ghost);

/**
 * Handles the ghost leaving the house because its boredom reaches the limit.
 *
 * @param ghost  The ghost exiting the house.
 *
 * @return       Nothing. The ghost is marked as having exited.
 */
void ghost_exit( Ghost *ghost);

/**
 * Search to see if any hunter is in the room.
 *
 * @param ghost  Pointer to the Ghost performing inspection of its current room.
 *
 * @return      true if one or more hunters are in the room; false otherwise.
 */
bool ghost_find_hunter( Ghost *ghost);

/**
 * Doing nothing but chilling
 *
 * @param ghost  Pointer to the Ghost .
 *
 * @return      nothing
 */
void ghost_idle( Ghost *ghost);

/**
 * Randomly choose a ghost to assign
 *
 * @param  Nothing
 *
 * @return a ghost
 */
 GhostType ghost_random();