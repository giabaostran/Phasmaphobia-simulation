#ifndef DEFS_H
#define DEFS_H

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <semaphore.h>
#include <pthread.h>
#include <sys/time.h>
#include <time.h>
#include <stdio.h>

#define MAX_ROOM_NAME 64
#define MAX_HUNTER_NAME 64
#define MAX_ROOMS 24
#define MAX_ROOM_OCCUPANCY 8
#define EVIDENCE_PER_GHOST 3
#define MAX_CONNECTIONS 8
#define GHOST_TYPE_COUNT 24
#define EVIDENCE_TYPE_COUNT 7
#define ENTITY_BOREDOM_MAX 50
#define HUNTER_FEAR_MAX 20
#define DEFAULT_GHOST_ID 68057

typedef unsigned char EvidenceByte;

typedef enum {
    LOG_ENTITY_HUNTER = 0,
    LOG_ENTITY_GHOST = 1
} LogEntityType;

typedef struct {
    LogEntityType entity_type;
    int entity_id;
    const char *room;
    const char *device;
    int boredom;
    int fear;
    const char *action;
    const char *extra;
} LogRecord;

typedef enum {
    LR_EVIDENCE = 0,
    LR_BORED = 1,
    LR_AFRAID = 2
} LogReason;

typedef enum {
    EV_EMF = 1 << 0,
    EV_ORBS = 1 << 1,
    EV_RADIO = 1 << 2,
    EV_TEMPERATURE = 1 << 3,
    EV_FINGERPRINTS = 1 << 4,
    EV_WRITING = 1 << 5,
    EV_INFRARED = 1 << 6
} EvidenceType;

typedef enum {
    GH_POLTERGEIST = EV_FINGERPRINTS | EV_TEMPERATURE | EV_WRITING,
    GH_THE_MIMIC = EV_FINGERPRINTS | EV_TEMPERATURE | EV_RADIO,
    GH_HANTU = EV_FINGERPRINTS | EV_TEMPERATURE | EV_ORBS,
    GH_JINN = EV_FINGERPRINTS | EV_TEMPERATURE | EV_EMF,
    GH_PHANTOM = EV_FINGERPRINTS | EV_INFRARED | EV_RADIO,
    GH_BANSHEE = EV_FINGERPRINTS | EV_INFRARED | EV_ORBS,
    GH_GORYO = EV_FINGERPRINTS | EV_INFRARED | EV_EMF,
    GH_BULLIES = EV_FINGERPRINTS | EV_WRITING | EV_RADIO,
    GH_MYLING = EV_FINGERPRINTS | EV_WRITING | EV_EMF,
    GH_OBAKE = EV_FINGERPRINTS | EV_ORBS | EV_EMF,
    GH_YUREI = EV_TEMPERATURE | EV_INFRARED | EV_ORBS,
    GH_ONI = EV_TEMPERATURE | EV_INFRARED | EV_EMF,
    GH_MOROI = EV_TEMPERATURE | EV_WRITING | EV_RADIO,
    GH_REVENANT = EV_TEMPERATURE | EV_WRITING | EV_ORBS,
    GH_SHADE = EV_TEMPERATURE | EV_WRITING | EV_EMF,
    GH_ONRYO = EV_TEMPERATURE | EV_RADIO | EV_ORBS,
    GH_THE_TWINS = EV_TEMPERATURE | EV_RADIO | EV_EMF,
    GH_DEOGEN = EV_INFRARED | EV_WRITING | EV_RADIO,
    GH_THAYE = EV_INFRARED | EV_WRITING | EV_ORBS,
    GH_YOKAI = EV_INFRARED | EV_RADIO | EV_ORBS,
    GH_WRAITH = EV_INFRARED | EV_RADIO | EV_EMF,
    GH_RAIJU = EV_INFRARED | EV_ORBS | EV_EMF,
    GH_MARE = EV_WRITING | EV_RADIO | EV_ORBS,
    GH_SPIRIT = EV_WRITING | EV_RADIO | EV_EMF
} GhostType;

typedef struct CaseFile {
    EvidenceByte collected;
    GhostType ghost;
    bool solved;
    sem_t mutex;
} CaseFile;

typedef struct Room Room;
typedef struct Ghost Ghost;
typedef struct Hunter Hunter;

struct Room {
    char name[MAX_ROOM_NAME];
    Room *connected_rooms[MAX_ROOMS];
    int connection_count;
    Ghost *ghost;
    Hunter *hunters[MAX_ROOM_OCCUPANCY];
    int hunter_count;
    bool is_exit;
    EvidenceByte evidence;
};

typedef struct RoomNode {
    Room *room;
    struct RoomNode *next;
} RoomNode;

typedef struct RoomStack {
    RoomNode *head;
} RoomStack;

struct Hunter {
    int id;
    char name[MAX_HUNTER_NAME];
    Room *current_room;
    Room *starting_room;
    CaseFile *case_file;
    EvidenceByte device;
    RoomStack room_stack;
    int fear;
    int boredom;
    LogReason exit_reason;
    bool has_exit;
    bool found_evidence;
};

typedef struct HunterNode {
    Hunter *hunter;
    struct HunterNode *next;
} HunterNode;

typedef struct HunterArray {
    HunterNode *head;
} HunterArray;

struct Ghost {
    int id;
    GhostType type;
    Room *current_room;
    int boredom;
    bool has_exit;
};

typedef struct House {
    Room rooms[MAX_ROOMS];
    Room *starting_room;
    HunterArray hunters;
    CaseFile *case_file;
    int room_count;
    int hunter_count;
    int successful_exit_count;
    int failed_exit_count;
} House;

#endif // DEFS_H
