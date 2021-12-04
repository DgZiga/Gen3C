#ifndef MAIN_H
#define MAIN_H

#include "types.h"
#include "config.h"
#include "include/npc_state.h"
#include "include/script_state.h"
#include "include/wild_encounter_custom_table.h"
#include "include/npc_show_countdown.h"

u8 flag_check(u16 flag_id);
void add_task_game_freak(void (*exec_ptr)(u8), u8 priority);
void script_exec_env_1(void *ptr);
void script_exec_env_2(void *ptr);
void play_sound(u32 sound_id);
void * get_script_by_npc_id(u16 npc_id);
u8 task_is_running(void *task_ptr);
void del_task_game_freak(u8 tid);
u8 get_task_id_by_ptr(void (*exec_ptr)(u8));
u16 person_id_by_npc_id_and_map_and_bank(u8 npc_id, u8 map, u8 bank);
u32 rand();
void lock_movement(struct Npc_state *npc_state);
void release_movement(struct Npc_state *npc_state);
u32 mod(u32 a, u32 b);


void exec(u8 tid);
void second_step(u8 tid);
void check_showsprite_every_step();
void wildbattle_on_a_press();

#endif