#ifndef ENCOUNTERS_MENU_H
#define ENCOUNTERS_MENU_H
#include <pokeagb/pokeagb.h>
#include "../interface_definition.h"
#include "built_graphics/encounters_menu_gui.h"
#define rgb5(r, g, b) (u16)((r >> 3) | ((g >> 3) << 5) | ((b >> 3) << 10))

extern const struct InterfaceDefinition ENCOUNTERS_MENU_DEFINITION;
#include "../../engine/gui.h"
#include "../../engine/sprite_util.h"

#define CURSOR_TILES_TAG 0x6F
#define CURSOR_PALS_TAG 0x08


#endif