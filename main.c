#include "defs.h"
#include "helpers.h"
#include "ghost.h"
#include "hunter.h"

int main() {
    /*
    4. Create threads for the ghost and each hunter.
    5. Wait for all threads to complete.
    6. Print final results to the console:
         - Type of ghost encountered.
         - The reason that each hunter exited
         - The evidence collected by each hunter and which ghost is represented by that evidence.
    7. Clean up all dynamically allocated resources and call sem_destroy() on all semaphores.
    */


    // 1. Initialize a House structure.
    srand(time(NULL));
    struct CaseFile case_file = {.evidence_found = 0, .solved = false};
    struct House house = {.case_file = &case_file, .hunter_count = 0};
    // 2. Populate the House with rooms using the provided helper function.
    house_populate_rooms(&house);
    // 3. Initialize all of the ghost data and hunters.
    struct Ghost ghost;
    ghost_init(&house, &ghost);

    char buffer[MAX_HUNTER_NAME];

    while (true) {
        printf("Enter hunter name (max 63 characters) or 'done' to finish: ");
        fgets(buffer, MAX_HUNTER_NAME, stdin);
        buffer[strcspn(buffer, "\n")] = '\0'; // remove new line char from buffer
        if (strcasecmp(buffer, "done") == 0)
            break;
        int id;
        printf("Enter hunter ID (Integer): ");
        scanf("%d", &id);
        while (getchar() != '\n') // Clean the input stream buffer
            ;
        hunter_init(&house, buffer, id);
    }

    bool ghost_win, hunter_win;
    printf("==== GAME START =====\n");
    while (true) {
        if (ghost.has_exit == false)
            ghost_take_turn(&house, &ghost);
        struct HunterNode *agent = house.hunters.head;
        while (agent != NULL) {
            if (agent->hunter->has_exit == false)
                hunter_take_turn(&house, agent->hunter);
            agent = agent->next;
        }
        if (ghost.has_exit && house.hunter_count == 0)
            break;
    }

    return
            0;
}
