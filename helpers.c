#include "helpers.h"


// ---- House layout ----
void house_populate_rooms(struct House *house)
{
    // Willow House layout from Phasmaphobia, DO NOT MODIFY HOUSE LAYOUT
    house->room_count = 13;

    room_init(house->rooms + 0, "Van", true);
    room_init(house->rooms + 1, "Hallway", false);
    room_init(house->rooms + 2, "Master Bedroom", false);
    room_init(house->rooms + 3, "Boy's Bedroom", false);
    room_init(house->rooms + 4, "Bathroom", false);
    room_init(house->rooms + 5, "Basement", false);
    room_init(house->rooms + 6, "Basement Hallway", false);
    room_init(house->rooms + 7, "Right Storage Room", false);
    room_init(house->rooms + 8, "Left Storage Room", false);
    room_init(house->rooms + 9, "Kitchen", false);
    room_init(house->rooms + 10, "Living Room", false);
    room_init(house->rooms + 11, "Garage", false);
    room_init(house->rooms + 12, "Utility Room", false);

    rooms_connect(house->rooms + 0, house->rooms + 1);   // Van - Hallway
    rooms_connect(house->rooms + 1, house->rooms + 2);   // Hallway - Master Bedroom
    rooms_connect(house->rooms + 1, house->rooms + 3);   // Hallway - Boy's Bedroom
    rooms_connect(house->rooms + 1, house->rooms + 4);   // Hallway - Bathroom
    rooms_connect(house->rooms + 1, house->rooms + 9);   // Hallway - Kitchen
    rooms_connect(house->rooms + 1, house->rooms + 5);   // Hallway - Basement
    rooms_connect(house->rooms + 5, house->rooms + 6);   // Basement - Basement Hallway
    rooms_connect(house->rooms + 6, house->rooms + 7);   // Basement Hallway - Right Storage Room
    rooms_connect(house->rooms + 6, house->rooms + 8);   // Basement Hallway - Left Storage Room
    rooms_connect(house->rooms + 9, house->rooms + 10);  // Kitchen - Living Room
    rooms_connect(house->rooms + 9, house->rooms + 11);  // Kitchen - Garage
    rooms_connect(house->rooms + 11, house->rooms + 12); // Garage - Utility Room

    house->starting_room = house->rooms; // Van is at index 0
}


// ---- to_string functions ----
const char *evidence_to_string(enum EvidenceType evidence)
{
    switch (evidence)
    {
    case EV_EMF:
        return "emf";
    case EV_ORBS:
        return "orbs";
    case EV_RADIO:
        return "radio";
    case EV_TEMPERATURE:
        return "temp";
    case EV_FINGERPRINTS:
        return "prints";
    case EV_WRITING:
        return "writing";
    case EV_INFRARED:
        return "infrared";
    default:
        return "unknown";
    }
}

const char *ghost_to_string(enum GhostType ghost)
{
    switch (ghost)
    {
    case GH_POLTERGEIST:
        return "poltergeist";
    case GH_THE_MIMIC:
        return "the_mimic";
    case GH_HANTU:
        return "hantu";
    case GH_JINN:
        return "jinn";
    case GH_PHANTOM:
        return "phantom";
    case GH_BANSHEE:
        return "banshee";
    case GH_GORYO:
        return "goryo";
    case GH_BULLIES:
        return "bullies";
    case GH_MYLING:
        return "myling";
    case GH_OBAKE:
        return "obake";
    case GH_YUREI:
        return "yurei";
    case GH_ONI:
        return "oni";
    case GH_MOROI:
        return "moroi";
    case GH_REVENANT:
        return "revenant";
    case GH_SHADE:
        return "shade";
    case GH_ONRYO:
        return "onryo";
    case GH_THE_TWINS:
        return "the_twins";
    case GH_DEOGEN:
        return "deogen";
    case GH_THAYE:
        return "thaye";
    case GH_YOKAI:
        return "yokai";
    case GH_WRAITH:
        return "wraith";
    case GH_RAIJU:
        return "raiju";
    case GH_MARE:
        return "mare";
    case GH_SPIRIT:
        return "spirit";
    default:
        return "unknown";
    }
}

const char *exit_reason_to_string(enum LogReason reason)
{
    switch (reason)
    {
    case LR_EVIDENCE:
        return "evidence";
    case LR_BORED:
        return "bored";
    case LR_AFRAID:
        return "afraid";
    default:
        return "unknown";
    }
}

// ---- enum retrieval functions ----
int get_all_evidence_types(const enum EvidenceType **list)
{
    // Stored in the data segment so that we can point to it safely
    static const enum EvidenceType evidence_types[] = {
        EV_EMF,
        EV_ORBS,
        EV_RADIO,
        EV_TEMPERATURE,
        EV_FINGERPRINTS,
        EV_WRITING,
        EV_INFRARED};

    if (list)
    {
        *list = evidence_types;
    }
    return (int)(sizeof(evidence_types) / sizeof(evidence_types[0]));
}

int get_all_ghost_types(const enum GhostType **list)
{
    // Stored in the data segment so that we can point to it safely
    static const enum GhostType ghost_types[] = {
        GH_POLTERGEIST,
        GH_THE_MIMIC,
        GH_HANTU,
        GH_JINN,
        GH_PHANTOM,
        GH_BANSHEE,
        GH_GORYO,
        GH_BULLIES,
        GH_MYLING,
        GH_OBAKE,
        GH_YUREI,
        GH_ONI,
        GH_MOROI,
        GH_REVENANT,
        GH_SHADE,
        GH_ONRYO,
        GH_THE_TWINS,
        GH_DEOGEN,
        GH_THAYE,
        GH_YOKAI,
        GH_WRAITH,
        GH_RAIJU,
        GH_MARE,
        GH_SPIRIT};

    if (list)
    {
        *list = ghost_types;
    }
    return (int)(sizeof(ghost_types) / sizeof(ghost_types[0]));
}

// ---- Thread-safe random number generation ----
int rand_int_threadsafe(int lower_inclusive, int upper_exclusive)
{
    static _Thread_local unsigned seed = 0;

    if (upper_exclusive <= lower_inclusive)
    {
        return lower_inclusive;
    }

    if (seed == 0)
    {
        seed = (unsigned)time(NULL) ^ (unsigned)(uintptr_t)pthread_self();
        if (seed == 0)
        {
            seed = 0xA5A5A5A5u;
        }
    }

    unsigned span = (unsigned)(upper_exclusive - lower_inclusive);
    unsigned value = (unsigned)rand_r(&seed) % span;
    return lower_inclusive + (int)value;
}

// ---- Evidence helpers ----
bool evidence_is_valid_ghost(EvidenceByte mask)
{
    const enum GhostType *ghost_types = NULL;
    int ghost_count = get_all_ghost_types(&ghost_types);

    for (int index = 0; index < ghost_count; index++)
    {
        if (mask == (EvidenceByte)ghost_types[index])
        {
            return true;
        }
    }

    return false;
}

// ---- Logging (Writes CSV logs, DO NOT MODIFY the file outputs: timestamp,type,id,room,device,boredom,fear,action,extra) ----
