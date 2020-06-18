#include "ability.h"

enum PokemonType {
    TYPE_NORMAL,
    TYPE_FIGHTING,
    TYPE_FLYING,
    TYPE_POISON,
    TYPE_GROUND,
    TYPE_ROCK,
    TYPE_BUG,
    TYPE_GHOST,
    TYPE_STEEL,
    TYPE_NONE, /**< ??? Type */
    TYPE_FIRE,
    TYPE_WATER,
    TYPE_GRASS,
    TYPE_ELECTRIC,
    TYPE_PSYCHIC,
    TYPE_ICE,
    TYPE_DRAGON,
    TYPE_DARK,
    TYPE_MAX,
};

struct PokemonBaseStat {
    u8 hp;
    u8 atk;
    u8 def;
    u8 spd;
    u8 spatk;
    u8 spdef;
    enum PokemonType type[2];
    u8 catch_rate;
    u8 xp_yield;
    u16 effort_yield;
    u16 item[2];
    u8 gender_ratio;
    u8 steps_to_hatch;
    u8 base_friendship;
    u8 exp_growth;
    u8 eggroup[2];
    enum PokemonAbility ability[2];
    u8 safari_zone_flee_rate;
    u8 color;
    u16 padding;
};

struct PokemonBaseStat speciesTbl[412];