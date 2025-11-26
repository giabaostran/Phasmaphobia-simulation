#include "ghost.h"
#include "defs.h"
#include "helpers.h"

void hunter_take_turn( House *house,  Hunter *hunter);
void hunter_init( House *house, char *nam, int id);
void hunter_exit( Hunter *hunter);
void hunter_move( Hunter *hunter);
void hunter_get_evidence( Hunter *hunter);
void hunter_swap_device( Hunter *hunter) ;
void hunter_clean_path( Hunter *hunter) ;
void hunter_reset_path( Hunter *hunter) ;
EvidenceByte hunter_receives_device() ;

