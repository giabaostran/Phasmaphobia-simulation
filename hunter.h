#include "ghost.h"
#include "defs.h"
#include "log.h"
#include "helpers.h"

void hunter_take_turn(struct House *house, struct Hunter *hunter);
void hunter_init(struct House *house, char *nam, int id);
void hunter_exit(struct Hunter *hunter);
void hunter_move(struct Hunter *hunter);
void hunter_get_evidence(struct Hunter *hunter);
void hunter_swap_device(struct Hunter *hunter) ;
void hunter_clean_path(struct Hunter *hunter) ;
void hunter_reset_path(struct Hunter *hunter) ;
EvidenceByte hunter_receives_device() ;

