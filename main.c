#include "defs.h"
#include "helpers.h"
#include "ghost.h"
#include "hunter.h"

int main() {
    // time_t fixed_seconds = 10;
    // 1. Initialize a House structure.
    // srand(time(NULL));
    srand(4);
    struct CaseFile case_file = {.evidence_found = 0, .solved = false};
    struct House house = {.case_file = &case_file, .hunter_count = 0};
    // 2. Populate the House with rooms using the provided helper function.
    house_populate_rooms(&house);
    // 3. Initialize all of the ghost data and hunters.
    struct Ghost ghost;
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

        struct HunterNode *agent = house.hunters.head;

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

        if (ghost.has_exit && (house.successful_exit_count + house.failed_exit_count) == house.hunter_count)
            break;
    }

    printf("\nInvestigation Results:\n");
    printf("=============================================\n");
    struct HunterNode *agent = house.hunters.head;
    while (agent != NULL) {
        struct Hunter *hunter = agent->hunter;
        printf("-[%s] Hunter %s (ID_%d) exited because of [%s] (bored=%d, fear=%d)\n",
               hunter->exit_reason == LR_EVIDENCE ? "✅" : "❌",
               hunter->name,
               hunter->id,
               exit_reason_to_string(hunter->exit_reason),
               hunter->boredom,
               hunter->fear);
        agent = agent->next;
    }

    printf("\nShare Case File Checklist:\n");
    printf("----------------------------------------------\n");
    for (int i = 0; i < EVIDENCE_TYPE_COUNT; i++) {
        int mask = 1 << i;
        printf("  [%s] %s\n", (case_file.collected & mask) != 0 ? "✅" : "❌", evidence_to_string(mask));
    }


    printf("\nVictory Results:\n");
    printf("----------------------------------------------\n");
    printf("- Hunters exited after identifying the ghost: %d/%d\n", house.successful_exit_count, house.hunter_count);
    printf("- Ghost guess: %s\n", ghost_to_string(case_file.collected));
    printf("- Actual ghost: %s\n", ghost_to_string(ghost.type));

    printf("Overall result: %s Win!!!", ghost_win ? "Ghost" : "Hunter(s)");

    return 0;
}
