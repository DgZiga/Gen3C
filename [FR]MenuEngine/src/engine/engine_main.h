#ifndef ENGINE_MAIN_H
#define ENGINE_MAIN_H

#include <pokeagb/pokeagb.h>
#include "../include/agb_debug/debug.c"
#include "../input_handler.h"
#include "../poketools.h"
#include "../interface_definition.h"
#include "setup.h"
#include "gui.h"

#define CURSOR_TILES_TAG 0x6F
#define CURSOR_PALS_TAG 0x08

int new_menu_main(const struct InterfaceDefinition* def);


#endif