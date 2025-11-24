#include "defs.h"
#include "helpers.h"
#include "ghost.h"

int main()
{

    /*
    4. Create threads for the ghost and each hunter.
    5. Wait for all threads to complete.
    6. Print final results to the console:
         - Type of ghost encountered.
         - The reason that each hunter exited
         - The evidence collected by each hunter and which ghost is represented by that evidence.
    7. Clean up all dynamically allocated resources and call sem_destroy() on all semaphores.
    */
    srand(time(NULL));

    // 1. Initialize a House structure.
    struct House house;
    // 2. Populate the House with rooms using the provided helper function.
    house_populate_rooms(&house);
    // 3. Initialize all of the ghost data and hunters.
    struct Ghost ghost;
    ghost_init(&house, &ghost);
    while (ghost.boredom != ENTITY_BOREDOM_MAX)
    {
        handle_ghost_turn(&ghost);
    }

    return 0;
}
