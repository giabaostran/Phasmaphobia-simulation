#include "defs.h"
/**
 * Run one turn for the hunter.
 *
 * @param house    Pointer to the House.
 * @param hunter   Pointer to the Hunter.
 */
void hunter_take_turn( House *house, Hunter *hunter );

/**
 * Initialize a hunter with name and ID, and add to the house.
 *
 * @param house    Pointer to the House.
 * @param nam      Hunter name string.
 * @param id       Hunter ID.
 */
void hunter_init( House *house, char *nam, int id );

/**
 * Handle hunter exit and cleanup.
 *
 * @param hunter   Pointer to the Hunter.
 */
void hunter_exit( Hunter *hunter );

/**
 * Move the hunter to a connected room.
 *
 * @param hunter   Pointer to the Hunter.
 */
void hunter_move( Hunter *hunter );

/**
 * Collect evidence from the current room.
 *
 * @param hunter   Pointer to the Hunter.
 */
void hunter_get_evidence( Hunter *hunter );

/**
 * Swap the hunter's active device.
 *
 * @param hunter   Pointer to the Hunter.
 */
void hunter_swap_device( Hunter *hunter );

/**
 * Clear the hunter's stored path.
 *
 * @param hunter   Pointer to the Hunter.
 */
void hunter_clean_path( Hunter *hunter );

/**
 * Reset the hunter's path to default state.
 *
 * @param hunter   Pointer to the Hunter.
 */
void hunter_reset_path( Hunter *hunter );

/**
 * Return the device assigned to the hunter.
 *
 * @return EvidenceByte representing the device.
 */
EvidenceByte hunter_receives_device();

