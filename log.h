
#ifndef LOG_H
#define LOG_H

#include "defs.h"
#include "helpers.h"

// These enums are just for logging purposes, not needed elsewhere
enum LogEntityType
{
    LOG_ENTITY_HUNTER = 0,
    LOG_ENTITY_GHOST = 1
};

struct LogRecord
{
    enum LogEntityType entity_type;
    int entity_id;
    const char *room;
    const char *device;
    int boredom;
    int fear;
    const char *action;
    const char *extra;
};
void log_move(int hunter_id, int boredom, int fear, const char *from_room, const char *to_room, enum EvidenceType device);
void log_evidence(int hunter_id, int boredom, int fear, const char *room_name, enum EvidenceType device);
void log_swap(int hunter_id, int boredom, int fear, enum EvidenceType from_device, enum EvidenceType to_device);
void log_exit(int hunter_id, int boredom, int fear, const char *room_name, enum EvidenceType device, enum LogReason reason);
void log_return_to_van(int hunter_id, int boredom, int fear, const char *room_name, enum EvidenceType device, bool heading_home);
void log_hunter_init(int hunter_id, const char *room_name, const char *hunter_name, enum EvidenceType device);
void log_ghost_init(int ghost_id, const char *room_name, enum GhostType type);
void log_ghost_move(int ghost_id, int boredom, const char *from_room, const char *to_room);
void log_ghost_evidence(int ghost_id, int boredom, const char *room_name, enum EvidenceType evidence);
void log_ghost_exit(int ghost_id, int boredom, const char *room_name);
void log_ghost_idle(int ghost_id, int boredom, const char *room_name);
static const char *log_entity_type_to_string(enum LogEntityType type);
static void write_log_record(const struct LogRecord *record);
#endif
