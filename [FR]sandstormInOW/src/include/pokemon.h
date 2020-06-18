struct Pokemon {
    u32 pid;
    u32 otid;
    char nick[10];
    u16 lang;
    char otname[7];
    u8 markings;
    u16 checksum;
    u16 unused;
    u8  data[48];
    u32 status;
    u8 level;
    u8 pokerus;
    u16 current_hp;
    u16 total_hp;
    u16 atk;
    u16 def;
    u16 spd;
    u16 spatk;
    u16 spdef;
};
enum PokemonDataRequest {
    REQUEST_PID = 0x0,
    REQUEST_TID = 0x1,
    REQUEST_NICK = 0x2,
    REQUEST_FONT_LANG = 0x3,
    REQUEST_SANITY_X4 = 0x4,
    REQUEST_SANITY_X5 = 0x5,
    REQUEST_SANITY_X6 = 0x6,
    REQUEST_OT_NAME = 0x7,
    REQUEST_MARKS = 0x8,
    REQUEST_CHECKSUM = 0x9,
    REQUEST_SPECIES = 0xB,
    REQUEST_HELD_ITEM = 0xC,
    REQUEST_MOVE1 = 0xD,
    REQUEST_MOVE2 = 0xE,
    REQUEST_MOVE3 = 0xF,
    REQUEST_MOVE4 = 0x10,
    REQUEST_PP1 = 0x11,
    REQUEST_PP2 = 0x12,
    REQUEST_PP3 = 0x13,
    REQUEST_PP4 = 0x14,
    REQUEST_PP_BONUSES = 0x15,
    REQUEST_COOLNESS = 0x16,
    REQUEST_BEAUTY = 0x17,
    REQUEST_CUTENESS = 0x18,
    REQUEST_EXP_POINTS = 0x19,
    REQUEST_HP_EV = 0x1A,
    REQUEST_ATK_EV = 0x1B,
    REQUEST_DEF_EV = 0x1C,
    REQUEST_SPD_EV = 0x1D,
    REQUEST_SPATK_EV = 0x1E,
    REQUEST_SPDEF_EV = 0x1F,
    REQUEST_HAPPINESS = 0x20,
    REQUEST_SMARTNESS = 0x21,
    REQUEST_POKERUS = 0x22,
    REQUEST_CATCH_LOCATION = 0x23,
    REQUEST_CATCH_LEVEL = 0x24,
    REQUEST_GAME_OF_ORIGIN = 0x25,
    REQUEST_POKEBALL = 0x26,
    REQUEST_HP_IV = 0x27,
    REQUEST_ATK_IV = 0x28,
    REQUEST_DEF_IV = 0x29,
    REQUEST_SPD_IV = 0x2A,
    REQUEST_SPATK_IV = 0x2B,
    REQUEST_SPDEF_IV = 0x2C,
    REQUEST_IS_EGG = 0x2D,
    REQUEST_ABILITY_BIT = 0x2E,
    REQUEST_TOUGHNESS = 0x2F,
    REQUEST_SHEEN = 0x30,
    REQUEST_OT_GENDER = 0x31,
    REQUEST_STATUS_AILMENT = 0x37,
    REQUEST_LEVEL = 0x38,
    REQUEST_CURRENT_HP = 0x39,
    REQUEST_TOTAL_HP = 0x3A,
    REQUEST_ATK = 0x3B,
    REQUEST_DEF = 0x3C,
    REQUEST_SPD = 0x3D,
    REQUEST_SPATK = 0x3E,
    REQUEST_SPDEF = 0x3F,
    REQUEST_POKERUS_REMAINING = 0x40,
    REQUEST_SPECIES2 = 0x41,
    REQUEST_HALL_OF_FAME_RIBBON = 0x43,
    REQUEST_OBEDIENCE = 0x50,
};

struct Pokemon party[6];
u32 pokemon_getattr(struct Pokemon*, enum PokemonDataRequest);
u32 pokemon_setattr(struct Pokemon*, enum PokemonDataRequest, void* dataPtr);