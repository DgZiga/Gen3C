#ifndef CONFIG_H
#define CONFIG_H

#include "include/new_menu/new_menu.h"
#include "include/new_menu_2/new_menu.h"
#include "include/encounters_menu/encounters_menu.h"

#define OAM_TABLE_START 0x83A3BB0 		//Default BPRE
#define OAM_TABLE_SIZE 0x99 			//Default BPRE
#define OAM_PAL_TABLE_START 0x83A5158 	//Default BPRE
#define OAM_PAL_TABLE_SIZE 18 			//Default BPRE

const struct InterfaceDefinition* const IMPLEMENTED_INTERFACES[] = {&NEW_MENU_DEFINITION, &NEW_MENU_2_DEFINITION, &ENCOUNTERS_MENU_DEFINITION};

#define TOOL_COUNT sizeof(IMPLEMENTED_INTERFACES)/sizeof(IMPLEMENTED_INTERFACES[0])

#include "engine/engine_main.h"

BY_ITEM(0);
BY_ITEM(1);



#endif