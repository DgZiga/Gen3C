#include "types.h"
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
u16 person_id_by_npc_id(u16 npc_id);
u32 rand();

// Check if the player is in range of a valid random encounter
void exec(u8 tid) {
	struct Script_state *env1 = (struct Script_state *)0x03000EB0;
	void (*second_step_ptr)(u8) = (void (*)(u8))0x08805209;
	
	if(env1->continue_exec || task_is_running(second_step_ptr)){ //If a script or the second step are running, don't run this task
		return;
	}
	
	struct Npc_state *npc_state = (struct Npc_state *)0x02036E38;
	struct Npc_state player = *npc_state;
	
	void *opponent_party = (void *)0x0202402C; //We'll use this as free space: the first 2 bytes will hold the active npc, and the others will contain the applymovement script
	u16 *npc_id_slot = (u16 *)opponent_party;
	u8 *precompiled_script_slot = (u8 *)opponent_party+2;
	u8 *precompiled_script_slot_iterable = precompiled_script_slot;
	
	u16 player_x = player.to_coord.x;
	u16 player_y = player.to_coord.y;
	
	while(npc_state->map_no != 0xFF || npc_state->map_bank != 0xFF || npc_state->local_id != 0xFF){ //If any if these condition is true, then we have reached the end of the npc_state tbl
		if(npc_state->is_trainer == 0 && npc_state->sight_distance != 0){
			u16 npc_x = npc_state->to_coord.x;
			u16 npc_y = npc_state->to_coord.y;
			u16 npc_r = npc_state->sight_distance;
			u8 npc_dir = npc_state->direction;
			u8 direction = 0;
			u8 diff = 0;
			
			//Coordinates checks
			if(npc_dir == 0x11 &&
			   npc_x == player_x &&
			   npc_y + npc_r >= player_y && 
			   npc_y <= player_y){
				diff = player_y - npc_y;
				direction = 0x10;
				
			} else if(npc_dir == 0x22 &&
			   npc_x == player_x &&
			   npc_y - npc_r <= player_y && 
			   npc_y >= player_y){
				diff = npc_y - player_y;
				direction = 0x11;
				
			} else if(npc_dir == 0x33 &&
			   npc_y == player_y &&
			   npc_x - npc_r <= player_x && 
			   npc_x >= player_x){
				diff = npc_x - player_x;
				direction = 0x12;
				
			} else if(npc_dir == 0x44 &&
			   npc_y == player_y &&
			   npc_x + npc_r >= player_x && 
			   npc_x <= player_x){
				diff = player_x - npc_x;
				direction = 0x13;
			}
			
			if(direction){
				*npc_id_slot = npc_state->local_id; //Store npcId for second_step
				
				//Load applymovement script into memory and exec it from there
				u8 script[] = {0x4F /*applymovement*/, npc_state->local_id, 0x00, 0x36, 0x40, 0x02, 0x02, 0x02};
				for(u8 i=0; i<sizeof(script); i++){
					*precompiled_script_slot_iterable = script[i];
					precompiled_script_slot_iterable++;
				}
				u8 i;
				for(i=0; i<diff-1; i++){
					*(precompiled_script_slot_iterable +i) = direction;
				}
				*(precompiled_script_slot_iterable +i) = 0xFE;
				
				
				env1->continue_exec = 1;
				env1->next_offset = (u32)precompiled_script_slot;
				script_exec_env_1(env1);
				
				//Add second task
				add_task_game_freak(second_step_ptr, 1);
				return;
			}
			
		}
		npc_state++;
	}	
}

//Wait for the applymovement to end and exec wildbattle and hidesprite
void second_step(u8 tid){
	struct Script_state *env1 = (struct Script_state *)0x03000EB0;
	void *exec_applymovement_func = (void *)(0x080977AC|1); //Task called by the game engine that actually executes the applymovement cmd; for some reason if this is active wildbattles will fail
	
	u16 *npc_id_slot = (u16 *)0x0202402C; //which is really the opponent_party, see the first task for an explanation
	
	void *precompiled_script_slot = (void *)0x0202F1E4;
	void *precompiled_script_slot_iterable = precompiled_script_slot;
	
	struct Npc_state *npc_state = (struct Npc_state *)0x02036E38;
	struct Npc_state player = *npc_state;
	struct Npc_state npc = *(npc_state+ *npc_id_slot);
	
	struct Wild_enocunter_tbl *encounter_tbl = (struct Wild_enocunter_tbl *)0x08FFD8E0; //last 10Kb of the ROM, to be sure
	struct Npc_show_countdown *npc_show_ctdwn = (struct Npc_show_countdown *)(0x02029314 /*Start_of_box*/ + 0x5DE0 /*Box #10*/ + 0x28*5 /*Task_engine_len*/);
	
	u16 diff_x = player.from_coord.x - npc.from_coord.x;
	u16 diff_y = player.from_coord.y - npc.from_coord.y;
	
	//If the movement sequence is complete
	if((diff_x <= 1 || diff_x == 0xFFFF) && (diff_y <= 1 || diff_y == 0xFFFF) &&
	   ((npc.bitfield >> 1)&1) == 0 && ((player.bitfield >> 1)&1) == 0 &&  			//IsNotMoving
	   (npc.bitfield &1) == 1 && (player.bitfield &1) == 1){ 						//IsActive
	    
		del_task_game_freak(get_task_id_by_ptr(exec_applymovement_func)); //For some reason if this task exists wildbattle will fail
		
		//Lookup wild encounter tbl
		u16 person_id = person_id_by_npc_id(npc.local_id);
		while(encounter_tbl->person_id != person_id){
			encounter_tbl++;
		}
		
		struct Encounter selected_encounter;
		do{	//Choose a random encounter
			u8 selected_pkmn = rand() % sizeof(encounter_tbl->encounters);
			selected_encounter = encounter_tbl->encounters[selected_pkmn];
		}while (selected_encounter.species == 0xFFFF);
		
		//Look for a free spot to add the npc countdown
		for(u8 i = 0; i<10; i++){
			if(npc_show_ctdwn[i].person_id != 0){
				continue;
			}
			npc_show_ctdwn[i] = (struct Npc_show_countdown) {person_id, 3};
			break;
		}
	    
		//Load "hidesprite" and wildbattle script into memory and exec it
		
		*((u8 *)precompiled_script_slot_iterable) = 0x29; //setflag
		precompiled_script_slot_iterable++;
		*((u16 *)precompiled_script_slot_iterable) = person_id; 
		precompiled_script_slot_iterable+= 2;
		*((u8 *)precompiled_script_slot_iterable) = 0xB6; //wildbattle
		precompiled_script_slot_iterable++;
		*((u16 *)precompiled_script_slot_iterable) = selected_encounter.species; 
		precompiled_script_slot_iterable+= 2;
		*((u8 *)precompiled_script_slot_iterable) = selected_encounter.lvl; 
		precompiled_script_slot_iterable++;
		*((u16 *)precompiled_script_slot_iterable) = 0x0000; 
		precompiled_script_slot_iterable+= 2;
		*((u8 *)precompiled_script_slot_iterable) = 0xB7; //dowildbattle
		precompiled_script_slot_iterable++;
		*((u8 *)precompiled_script_slot_iterable) = 0x02; //end
		
		del_task_game_freak(tid); //Delete this task
		
		env1->next_offset = (u32)precompiled_script_slot;
		env1->continue_exec = 1;
		script_exec_env_1(env1);
	}
}

//To be executed at every step (see /src/hooker.s and /hooks), checks if any npc had its countdown expire and, should that be the case, execs a showsprite
void check_showsprite_every_step(){
	struct Npc_show_countdown *npc_show_ctdwn = (struct Npc_show_countdown *)(0x02029314 /*Start_of_box*/ + 0x5DE0 /*Box #10*/ + 0x28*5 /*Task_engine_len*/);
	void *precompiled_script_slot = (void *)0x0202F1E4 + 1; //+1 because we want 0x55 (showsprite command) not to be 2-Aligned, so that we can write the npcId as a halfword later
	void *precompiled_script_slot_iterable = precompiled_script_slot;
	struct Script_state *env1 = (struct Script_state *)0x03000EB0;
	
	for(u8 i = 0; i<10; i++){
		if(npc_show_ctdwn[i].person_id == 0){ 
			continue;
		}
		npc_show_ctdwn[i].steps_no--;
		
		if(npc_show_ctdwn[i].steps_no == 0){
			/* *((u8 *)precompiled_script_slot_iterable) = 0x55; //showsprite
			precompiled_script_slot_iterable++;
			*((u16 *)precompiled_script_slot_iterable) = npc_show_ctdwn[i].npc_id; 
			precompiled_script_slot_iterable += 2;
			*((u8 *)precompiled_script_slot_iterable) = 0x55; //showsprite
			*/
			
			*((u8 *)precompiled_script_slot_iterable) = 0x2A; //clearflag
			precompiled_script_slot_iterable++;
			*((u16 *)precompiled_script_slot_iterable) = npc_show_ctdwn[i].person_id; 
			precompiled_script_slot_iterable += 2;
			*((u8 *)precompiled_script_slot_iterable) = 0x25; //special
			precompiled_script_slot_iterable++;
			*((u16 *)precompiled_script_slot_iterable) = 0x8E; //Special 0x8E refreshes screen
			precompiled_script_slot_iterable += 2;
			*((u8 *)precompiled_script_slot_iterable) = 0x02; //end
			
			env1->next_offset = (u32)precompiled_script_slot;
			env1->continue_exec = 1;
			script_exec_env_1(env1);
		
			npc_show_ctdwn[i].person_id = 0;
		}
	}
}

//To be called by a callasm by every npc that is a wild pokémon, in case the player actively interacts with them
void wildbattle_on_a_press(){
	
	u16 *current_npc = (u16 *)0x03005074;
	struct Wild_enocunter_tbl *encounter_tbl = (struct Wild_enocunter_tbl *)0x08FFD8E0; //last 10Kb of the ROM, to be sure*/
	struct Npc_show_countdown *npc_show_ctdwn = (struct Npc_show_countdown *)(0x02029314 /*Start_of_box*/ + 0x5DE0 /*Box #10*/ + 0x28*5 /*Task_engine_len*/);
	
	void *precompiled_script_slot = (void *)0x0202F1E4;
	void *precompiled_script_slot_iterable = precompiled_script_slot;
	
	struct Script_state *env1 = (struct Script_state *)0x03000EB0;
	
	//Lookup wild encounter tbl
	u16 person_id = person_id_by_npc_id(*current_npc);
	while(encounter_tbl->person_id != person_id){
		encounter_tbl++;
	}
	
	struct Encounter selected_encounter;
	do{	//Choose a random encounter
		u8 selected_pkmn = rand() % sizeof(encounter_tbl->encounters);
		selected_encounter = encounter_tbl->encounters[selected_pkmn];
	}while (selected_encounter.species == 0xFFFF);
	
	//Look for a free spot to add the npc countdown
	for(u8 i = 0; i<10; i++){
		if(npc_show_ctdwn[i].person_id != 0){
			continue;
		}
		npc_show_ctdwn[i] = (struct Npc_show_countdown) {person_id, 3};
		break;
	}
	
	//Load "hidesprite" and wildbattle script into memory and exec it
	
	*((u8 *)precompiled_script_slot_iterable) = 0x29; //setflag
	precompiled_script_slot_iterable++;
	*((u16 *)precompiled_script_slot_iterable) = person_id; 
	precompiled_script_slot_iterable+= 2;
	*((u8 *)precompiled_script_slot_iterable) = 0xB6; //wildbattle
	precompiled_script_slot_iterable++;
	*((u16 *)precompiled_script_slot_iterable) = selected_encounter.species; 
	precompiled_script_slot_iterable+= 2;
	*((u8 *)precompiled_script_slot_iterable) = selected_encounter.lvl; 
	precompiled_script_slot_iterable++;
	*((u16 *)precompiled_script_slot_iterable) = 0x0000; 
	precompiled_script_slot_iterable+= 2;
	*((u8 *)precompiled_script_slot_iterable) = 0xB7; //dowildbattle
	precompiled_script_slot_iterable++;
	*((u8 *)precompiled_script_slot_iterable) = 0x02; //end
	
	env1->next_offset = (u32)precompiled_script_slot;
	env1->continue_exec = 1;
	script_exec_env_1(env1);
}