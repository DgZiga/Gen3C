#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H
#include <pokeagb/pokeagb.h>
#include "poketools.h"
#include "config.h"


u32 *free_space = (u32*) (&(party_opponent[0]).base.nick[0]);// 0x2024034 = 0x0202402C + 8
u32* boxid_addr = (u32*) (&(party_opponent[0]).base.nick[4]);
struct InterfaceDefinition** interface_def_addr = (struct InterfaceDefinition**)(&(party_opponent[0]).base.nick[8]);
const u8 *curr_choice_id_addr = (u8*) 0x0203ADE6;

bool hijack_A_pressed();
u8 hijack();
u8 hijack_close_tmp_menu();

#endif