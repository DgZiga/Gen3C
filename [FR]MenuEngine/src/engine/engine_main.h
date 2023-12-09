#ifndef ENGINE_MAIN_H
#define ENGINE_MAIN_H

#define BY_ITEM(id)  \
void gui_##id##_by_item_run_eventually(){\
	new_gui_main(IMPLEMENTED_INTERFACES[id]);\
}\
void gui_##id##_by_item_task(u8 task_id){\
	c2_exit_to_overworld_2_switch();\
	*run_eventually = gui_##id##_by_item_run_eventually;\
	run_eventually_start(task_id);\
}\
void gui_##id##_new_gui_by_item(){\
	task_add(gui_##id##_by_item_task, 0);\
}
#include <pokeagb/pokeagb.h>
#include "../interface_definition.h"
int new_gui_main(const struct InterfaceDefinition* def);
POKEAGB_EXTERN void run_eventually_start(u8 task_id);


#include "../include/agb_debug/debug.c"
#include "../input_handler.h"
#include "../poketools.h"
#include "../interface_definition.h"
#include "setup.h"
#include "gui.h"


#define CURSOR_TILES_TAG 0x6F
#define CURSOR_PALS_TAG 0x08


#endif