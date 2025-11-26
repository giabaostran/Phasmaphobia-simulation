#include "log.h"


void log_move(int hunter_id, int boredom, int fear, const char *from_room, const char *to_room,  EvidenceType device)
{
     LogRecord record = {
        .entity_type = LOG_ENTITY_HUNTER,
        .entity_id = hunter_id,
        .room = from_room,
        .device = evidence_to_string(device),
        .boredom = boredom,
        .fear = fear,
        .action = "MOVE",
        .extra = to_room};

    write_log_record(&record);

    printf("Hunter %d using %s moved from %s to %s (bored=%d fear=%d)\n",
           hunter_id,
           evidence_to_string(device),
           from_room ? from_room : "",
           to_room ? to_room : "",
           boredom,
           fear);
}

void log_evidence(int hunter_id, int boredom, int fear, const char *room_name,  EvidenceType device)
{
    const char *evidence = evidence_to_string(device);
     LogRecord record = {
        .entity_type = LOG_ENTITY_HUNTER,
        .entity_id = hunter_id,
        .room = room_name,
        .device = evidence,
        .boredom = boredom,
        .fear = fear,
        .action = "EVIDENCE",
        .extra = evidence};

    write_log_record(&record);

    printf("Hunter %d using %s gathered evidence in %s (bored=%d fear=%d)\n",
           hunter_id,
           evidence,
           room_name ? room_name : "",
           boredom,
           fear);
}

void log_swap(int hunter_id, int boredom, int fear,  EvidenceType from_device,  EvidenceType to_device)
{
    char extra[64];
    const char *from_text = evidence_to_string(from_device);
    const char *to_text = evidence_to_string(to_device);
    snprintf(extra, sizeof(extra), "%s->%s", from_text, to_text);

     LogRecord record = {
        .entity_type = LOG_ENTITY_HUNTER,
        .entity_id = hunter_id,
        .room = NULL,
        .device = to_text,
        .boredom = boredom,
        .fear = fear,
        .action = "SWAP",
        .extra = extra};

    write_log_record(&record);

    printf("Hunter %d swapped devices: %s -> %s (bored=%d fear=%d)\n",
           hunter_id,
           from_text,
           to_text,
           boredom,
           fear);
}

void log_exit(int hunter_id, int boredom, int fear, const char *room_name,  EvidenceType device,  LogReason reason)
{
    const char *device_text = evidence_to_string(device);
    const char *reason_text = exit_reason_to_string(reason);

     LogRecord record = {
        .entity_type = LOG_ENTITY_HUNTER,
        .entity_id = hunter_id,
        .room = room_name,
        .device = device_text,
        .boredom = boredom,
        .fear = fear,
        .action = "EXIT",
        .extra = reason_text};

    write_log_record(&record);

    printf("Hunter %d using %s exited at %s (reason=%s, bored=%d fear=%d)\n",
           hunter_id,
           device_text,
           room_name ? room_name : "",
           reason_text,
           boredom,
           fear);
}

void log_return_to_van(int hunter_id, int boredom, int fear, const char *room_name,  EvidenceType device, bool heading_home)
{
    const char *device_text = evidence_to_string(device);
    const char *extra = heading_home ? "start" : "complete";
    const char *action = heading_home ? "RETURN_START" : "RETURN_COMPLETE";

     LogRecord record = {
        .entity_type = LOG_ENTITY_HUNTER,
        .entity_id = hunter_id,
        .room = room_name,
        .device = device_text,
        .boredom = boredom,
        .fear = fear,
        .action = action,
        .extra = extra};

    write_log_record(&record);

    if (heading_home)
    {
        printf("Hunter %d using %s heading to van from %s (bored=%d fear=%d)\n",
               hunter_id,
               device_text,
               room_name ? room_name : "",
               boredom,
               fear);
    }
    else
    {
        printf("Hunter %d using %s finished return at %s (bored=%d fear=%d)\n",
               hunter_id,
               device_text,
               room_name ? room_name : "",
               boredom,
               fear);
    }
}

void log_hunter_init(int hunter_id, const char *room_name, const char *hunter_name,  EvidenceType device)
{
    const char *device_text = evidence_to_string(device);
     LogRecord record = {
        .entity_type = LOG_ENTITY_HUNTER,
        .entity_id = hunter_id,
        .room = room_name,
        .device = device_text,
        .boredom = 0,
        .fear = 0,
        .action = "INIT",
        .extra = hunter_name ? hunter_name : ""};

    write_log_record(&record);
    printf("Hunter %d (%s) initialized in %s with %s\n",
           hunter_id,
           hunter_name ? hunter_name : "unknown",
           room_name ? room_name : "",
           device_text);
}

void log_ghost_init(int ghost_id, const char *room_name,  GhostType type)
{
    const char *type_text = ghost_to_string(type);
     LogRecord record = {
        .entity_type = LOG_ENTITY_GHOST,
        .entity_id = ghost_id,
        .room = room_name,
        .device = NULL,
        .boredom = 0,
        .fear = 0,
        .action = "INIT",
        .extra = type_text};

    write_log_record(&record);
    printf("Ghost %d (%s) initialized in %s\n",
           ghost_id,
           type_text,
           room_name ? room_name : "");
}

void log_ghost_move(int ghost_id, int boredom, const char *from_room, const char *to_room)
{
     LogRecord record = {
        .entity_type = LOG_ENTITY_GHOST,
        .entity_id = ghost_id,
        .room = from_room,
        .device = NULL,
        .boredom = boredom,
        .fear = 0,
        .action = "MOVE",
        .extra = to_room};

    write_log_record(&record);

    printf("Ghost %d [bored=%d] MOVE %s -> %s\n",
           ghost_id,
           boredom,
           from_room ? from_room : "",
           to_room ? to_room : "");
}

void log_ghost_evidence(int ghost_id, int boredom, const char *room_name,  EvidenceType evidence)
{
    const char *evidence_text = evidence_to_string(evidence);

     LogRecord record = {
        .entity_type = LOG_ENTITY_GHOST,
        .entity_id = ghost_id,
        .room = room_name,
        .device = NULL,
        .boredom = boredom,
        .fear = 0,
        .action = "EVIDENCE",
        .extra = evidence_text};

    write_log_record(&record);

    printf("Ghost %d [bored=%d] EVIDENCE %s in %s\n",
           ghost_id,
           boredom,
           evidence_text,
           room_name ? room_name : "");
}

void log_ghost_exit(int ghost_id, int boredom, const char *room_name)
{
     LogRecord record = {
        .entity_type = LOG_ENTITY_GHOST,
        .entity_id = ghost_id,
        .room = room_name,
        .device = NULL,
        .boredom = boredom,
        .fear = 0,
        .action = "EXIT",
        .extra = ""};

    write_log_record(&record);

    printf("Ghost %d [bored=%d] EXIT %s\n",
           ghost_id,
           boredom,
           room_name ? room_name : "");
}

void log_ghost_idle(int ghost_id, int boredom, const char *room_name)
{
     LogRecord record = {
        .entity_type = LOG_ENTITY_GHOST,
        .entity_id = ghost_id,
        .room = room_name,
        .device = NULL,
        .boredom = boredom,
        .fear = 0,
        .action = "IDLE",
        .extra = ""};

    write_log_record(&record);

    printf("Ghost %d [bored=%d] IDLE in %s\n",
           ghost_id,
           boredom,
           room_name ? room_name : "");
}

static const char *log_entity_type_to_string( LogEntityType type)
{
    switch (type)
    {
    case LOG_ENTITY_HUNTER:
        return "hunter";
    case LOG_ENTITY_GHOST:
        return "ghost";
    default:
        return "unknown";
    }
}

static void write_log_record(const  LogRecord *record)
{
    static _Thread_local unsigned line_count = 0;

    if (line_count >= 100000)
    {
        fprintf(stderr, "Log capped for entity %d; stopping to prevent infinite growth.\n", record->entity_id);
        exit(1);
    }

    char filename[64];
    snprintf(filename, sizeof(filename), "log_%d.csv", record->entity_id);

    FILE *log_file = fopen(filename, "a");

    if (!log_file)
    {
        return;
    }

  
    struct timeval tv;
    gettimeofday(&tv, NULL);
    long long timestamp = (long long)tv.tv_sec * 1000LL + (long long)tv.tv_usec / 1000LL;

    const char *entity = log_entity_type_to_string(record->entity_type);
    const char *room = record->room ? record->room : "";
    const char *device = record->device ? record->device : "";
    const char *action = record->action ? record->action : "";
    const char *extra = record->extra ? record->extra : "";

    fprintf(log_file,
            "%lld,%s,%d,%s,%s,%d,%d,%s,%s\n",
            timestamp,
            entity,
            record->entity_id,
            room,
            device,
            record->boredom,
            record->fear,
            action,
            extra);

    fclose(log_file);
    line_count++;

    // Short pause helps ensure successive logs receive distinct timestamps.
    struct timespec pause = {0, 2 * 1000 * 1000}; // 2 ms
    nanosleep(&pause, NULL);
}

