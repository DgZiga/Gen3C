#ifndef POKETOOLS_H
#define POKETOOLS_H
#include <pokeagb/pokeagb.h>
#include "engine/engine_main.h"
#include "input_handler.h"
#include "config.h"


void clear_tmp_menu();
void sm_poketools();
void close_startmenu();
bool make_choice(u32 choice_id);

extern const pchar menu_text[];

#endif