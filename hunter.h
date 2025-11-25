#include "ghost.h"
#include "defs.h"
#include "log.h"

void hunter_take_turn(struct Hunter *hunter);
void hunter_init(struct House *house, char *nam, int id);
void hunter_exit(struct Hunter *hunter);
void hunter_move(struct Hunter *hunter);
void hunter_get_evidence(struct Hunter *hunter);

