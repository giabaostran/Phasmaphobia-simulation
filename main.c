#include "defs.h"
#include "helpers.h"
#include "ghost.h"
#include "hunter.h"

int main() {
    // 1. Initialize a House ure.
    srand(4);
    CaseFile case_file = {.ghost = 0, .solved = false};
    House house = {.case_file = &case_file, .hunter_count = 0};
    // 2. Populate the House with rooms using the provided helper function.
    house_populate_rooms(&house);
    // 3. Initialize all of the ghost data and hunters.
    Ghost ghost;
    ghost_init(&house, &ghost);
    // buffer to hold user input
    char buffer[MAX_HUNTER_NAME];
    int id;
    // keep creating more hunter until user say stop
    while (true) {
        printf("Enter hunter name (max 63 characters) or 'done' to finish: ");
        fgets(buffer, MAX_HUNTER_NAME, stdin);
        buffer[strcspn(buffer, "\n")] = '\0'; // remove new line char from buffer
        if (strcasecmp(buffer, "done") == 0)
            break;
        printf("Enter hunter ID (Integer): ");
        scanf("%d", &id);
        while (getchar() != '\n') // Clean the input stream buffer
            ;
        hunter_init(&house, buffer, id);
    }

    bool ghost_win = false, hunter_win = false;
    printf("==== GAME START =====\n");
    while (true) {
        if (ghost.has_exit == false)
            ghost_take_turn(&house, &ghost);

        HunterNode *agent = house.hunters.head;

        while (agent != NULL) {
            if (agent->hunter->has_exit == false)
                hunter_take_turn(&house, agent->hunter);
            agent = agent->next;
        }

        // The ghost must not win before hunter, all the evidence must be collected and at least 1 hunter exit successfully
        if (!ghost_win && case_file.solved && house.successful_exit_count != 0)
            hunter_win = true;
        // The hunters must not win before ghost, and the ghost leave before any hunter escape successfully
        if (!hunter_win && ghost.has_exit && house.successful_exit_count == 0)
            ghost_win = true;
        // if both ghosts and hunters leave the simulation
        if (ghost.has_exit && (house.successful_exit_count + house.failed_exit_count) == house.hunter_count)
            break;
    }

    display_result(house, ghost, ghost_win);

    return 0;
}
