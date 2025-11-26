
#ifndef LOG_H
#define LOG_H

#include "defs.h"
#include "helpers.h"

// These s are just for logging purposes, not needed elsewhere
typedef enum
{
    LOG_ENTITY_HUNTER = 0,
    LOG_ENTITY_GHOST = 1
} LogEntityType;

typedef struct 

{
    LogEntityType entity_type;
    int entity_id;
    const char *room;
    const char *device;
    int boredom;
    int fear;
    const char *action;
    const char *extra;
} LogRecord;

void log_move(int hunter_id, int boredom, int fear, const char *from_room, const char *to_room,  EvidenceType device);
void log_evidence(int hunter_id, int boredom, int fear, const char *room_name,  EvidenceType device);
void log_swap(int hunter_id, int boredom, int fear,  EvidenceType from_device,  EvidenceType to_device);
void log_exit(int hunter_id, int boredom, int fear, const char *room_name,  EvidenceType device,  LogReason reason);
void log_return_to_van(int hunter_id, int boredom, int fear, const char *room_name,  EvidenceType device, bool heading_home);
void log_hunter_init(int hunter_id, const char *room_name, const char *hunter_name,  EvidenceType device);
void log_ghost_init(int ghost_id, const char *room_name,  GhostType type);
void log_ghost_move(int ghost_id, int boredom, const char *from_room, const char *to_room);
void log_ghost_evidence(int ghost_id, int boredom, const char *room_name,  EvidenceType evidence);
void log_ghost_exit(int ghost_id, int boredom, const char *room_name);
void log_ghost_idle(int ghost_id, int boredom, const char *room_name);
static const char *log_entity_type_to_string( LogEntityType type);
static void write_log_record(const  LogRecord *record);
#endif
