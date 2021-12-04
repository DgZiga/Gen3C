#include "main.h"

//Too lazy to actually link ASM properly, using gcc extended ASM syntax
u32 mod(u32 a, u32 b){
	int res;
	asm ("MOV r0, %1\n"
		"MOV r1, %2\n"
		"SWI 0x6\n"
		"MOV %0, r1\n"
		: "=r"(res)
		: "r"(a), "r"(b));
	return res;
}

// Check if the player is in range of a valid random encounter
void exec(u8 tid) {
	struct Script_state *env1 = (struct Script_state *)0x03000EB0;
	void (*second_step_ptr)(u8) = &second_step;			
	
	if(env1->continue_exec || task_is_running(second_step_ptr)){ //If a script or the second step are running, don't run this task, as it would trigger multiple fights 
		return;
	}
	
	struct Npc_show_countdown *npc_show_ctdwn = (struct Npc_show_countdown *)NPC_CTDWN_ADDR; 
	struct Npc_state *npc_state = (struct Npc_state *)0x02036E38;	//Start of NPC_STATE
	struct Npc_state player = *npc_state;							//First NPC_STATE is always the Player
	
	/*We'll use the opponent's party as free space: the first 8 bytes will hold the offset of active npc in RAM, and the others will contain the applymovement script.
	We can use the opponent's party as free space because it will only get written over when entering a battle, but by then we won't be needing the information we're storing there anymore*/
	void *opponent_party = (void *)0x0202402C; 
	struct Npc_state **npc_id_slot = (struct Npc_state **)opponent_party;
	u8 *precompiled_script_slot = (u8 *)opponent_party+4;
	u8 *precompiled_script_slot_iterable = precompiled_script_slot;
	
	u16 player_x = player.to_coord.x;
	u16 player_y = player.to_coord.y;
	
	while(npc_state->map_no != 0xFF || npc_state->map_bank != 0xFF || npc_state->local_id != 0xFF){ //If any if these condition is true, then we have reached the end of the npc_state tbl
		/*Check that the NPC is:
			1) NOT a trainer (otherwise a standard trainer battle should happen)
			2) HAS sight (if both this and 1 are satisfied, then the NPC is a valid target for the routine
			3) Its second bit in the bitfield is not set (if it's set the NPC is moving: running the routine on a moving NPC could cause bugs) */
		if(npc_state->is_trainer == 0 && npc_state->sight_distance != 0 && (npc_state->bitfield & 2) == 0){ 
			
			/*
			Ignore NPCs that are are hidden
			*/
			u8 isInCountdown = 0;
			for(u8 i = 0; i<10; i++){
				if(npc_show_ctdwn[i].person_id == person_id_by_npc_id_and_map_and_bank(npc_state->local_id, npc_state->map_no, npc_state->map_bank)){ //person_id_by_npc_id
					isInCountdown = 1;
					break;
				}
			}
			if(isInCountdown){
				npc_state++;
				continue;
			}
			
			/*Utility vars*/
			u16 npc_x = npc_state->to_coord.x;
			u16 npc_y = npc_state->to_coord.y;
			u16 npc_r = npc_state->sight_distance;
			u8 npc_dir = npc_state->direction;
			u8 direction = 0;
			u8 diff = 0;
			
			//Coordinates checks: check if the player can be seen by the NPC
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
			
			if(direction){ //If direction != 0, then the player can be seen by an NPC
								
				lock_movement(npc_state);	//Stop NPC animation
				
				u8 *walkrun_lock = (u8 *)0x0203707E;	//Prevent player from moving
				*walkrun_lock = 0x1;
				
				*npc_id_slot = npc_state; //Store npcId for second_step
				
				//Load applymovement script into memory and exec it from there
				u8 script[] = {0x4F /*applymovement*/, npc_state->local_id, 0x00, 0x36, 0x40, 0x02, 0x02, 0x02 /*end*/};
				for(u8 i=0; i<sizeof(script); i++){
					*precompiled_script_slot_iterable = script[i];
					precompiled_script_slot_iterable++;
				}
				u8 i;
				for(i=0; i<diff-1; i++){	//Add as many 'walk' directives as needed
					*(precompiled_script_slot_iterable +i) = direction;
				}
				*(precompiled_script_slot_iterable +i) = 0xFE;
				
				//Execute the script
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
	u16 steps = 10;
	struct Script_state *env1 = (struct Script_state *)0x03000EB0;
	void *exec_applymovement_func = (void *)(0x080977AC|1); //Task called by the game engine that actually executes the applymovement cmd; for some reason if this is active wildbattles will fail
	
	struct Npc_state **npc_id_slot = (struct Npc_state **)0x0202402C; //which is really the opponent_party, see the first task for an explanation
	
	void *precompiled_script_slot = (void *)PREC_SCRIPT_SLOT;
	void *precompiled_script_slot_iterable = precompiled_script_slot;
	
	struct Npc_state *npc_state = (struct Npc_state *)0x02036E38;	//Start of NPC_STATE
	struct Npc_state player = *npc_state;				            //First NPC_STATE is always the Player
	struct Npc_state npc = **npc_id_slot;							//Retrieve the NPC_STATE of the NPC the player is about to fight
	
	struct Wild_enocunter_tbl *encounter_tbl = (struct Wild_enocunter_tbl *)ENC_TBL_ADDR; //Start of encounter_tbl in ROM
	struct Npc_show_countdown *npc_show_ctdwn = (struct Npc_show_countdown *)NPC_CTDWN_ADDR; 
	
	u16 diff_x = player.from_coord.x - npc.from_coord.x;
	u16 diff_y = player.from_coord.y - npc.from_coord.y;
	
	//If the movement sequence is complete
	if((diff_x <= 1 || diff_x == 0xFFFF) && (diff_y <= 1 || diff_y == 0xFFFF) &&
	   ((npc.bitfield >> 1)&1) == 0 && ((player.bitfield >> 1)&1) == 0 &&  			//IsNotMoving
	   (npc.bitfield &1) == 1 && (player.bitfield &1) == 1){ 						//IsActive
	    
		del_task_game_freak(get_task_id_by_ptr(exec_applymovement_func)); //For some reason if this task exists wildbattle will fail
		
		//Lookup wild encounter tbl
		u16 person_id = person_id_by_npc_id_and_map_and_bank(npc.local_id, npc.map_no, npc.map_bank);
		while(encounter_tbl->person_id != person_id){
			encounter_tbl++;
		}
		
		struct Encounter selected_encounter;
		do{	//Choose a random encounter
			u8 selected_pkmn = mod(rand(), 4);
			selected_encounter = encounter_tbl->encounters[selected_pkmn];
		}while (selected_encounter.species == 0xFFFF);
		
		//Look for a free spot to add the npc countdown
		for(u8 i = 0; i<10; i++){
			if(npc_show_ctdwn[i].person_id != 0){
				continue;
			}
			npc_show_ctdwn[i] = (struct Npc_show_countdown) {person_id, steps};
			break;
		}
	    
		//Load hidesprite and wildbattle script into memory and exec it
		
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
		*((u8 *)precompiled_script_slot_iterable) = 0x53; //hidesprite
		precompiled_script_slot_iterable++;
		*((u16 *)precompiled_script_slot_iterable) = npc.local_id; 
		precompiled_script_slot_iterable += 2;
		*((u8 *)precompiled_script_slot_iterable) = 0xB7; //dowildbattle
		precompiled_script_slot_iterable++;
		*((u8 *)precompiled_script_slot_iterable) = 0x02; //end
		del_task_game_freak(tid); //Delete this task
		
		env1->next_offset = (u32)precompiled_script_slot;
		env1->continue_exec = 1;
		script_exec_env_1(env1);
		
		release_movement(*npc_id_slot);	//Resume NPC movement (even if hidden)
		u8 *walkrun_lock = (u8 *)0x0203707E;	//allow the player to move again
		*walkrun_lock = 0x0;
	}
}

//To be executed at every step (see /src/hooker.s and /hooks), checks if any npc had its countdown expire and, should that be the case, execs a showsprite
void check_showsprite_every_step(){
	struct Npc_show_countdown *npc_show_ctdwn = (struct Npc_show_countdown *)NPC_CTDWN_ADDR;
	void *precompiled_script_slot = (void *)PREC_SCRIPT_SLOT2;		
	void *precompiled_script_slot_iterable = precompiled_script_slot;
	struct Script_state *env1 = (struct Script_state *)0x03000EB0;
	
	for(u8 i = 0; i<10; i++){	//For every countdown position
		if(npc_show_ctdwn[i].person_id == 0){ //Avoid empty countdown positions
			continue;
		}
		npc_show_ctdwn[i].steps_no--;	//Decrease the number of steps needed
		
		/*Clearflag shows the sprite on the step AFTER it's executed, so execute it on the third-to-last step, so that on the second-to-last, the sprite will show itself and on the last step it will activate*/
		if(npc_show_ctdwn[i].steps_no == 2){	
		
			*((u8 *)precompiled_script_slot_iterable) = 0x2A; //clearflag
			precompiled_script_slot_iterable++;
			*((u16 *)precompiled_script_slot_iterable) = npc_show_ctdwn[i].person_id; 
			precompiled_script_slot_iterable += 2;
			*((u8 *)precompiled_script_slot_iterable) = 0x02; //end
			
			env1->next_offset = (u32)precompiled_script_slot;
			env1->continue_exec = 1;
			script_exec_env_1(env1);
		
		} 
		if(npc_show_ctdwn[i].steps_no == 0){	//Remove the personId from the countdown section, so that it can battle again
			npc_show_ctdwn[i].person_id = 0;
		}
	}
}

//To be called by a callasm by every npc that is a wild pokémon, in case the player actively interacts with them
void wildbattle_on_a_press(){
	
	u16 steps = 10;
	u16 *current_npc  = (u16 *)0x03005074;
	u8  *current_bank  = (u8  *)0x02025530;
	u8  *current_map  = (u8  *)0x02025531;	
	struct Npc_state *npc_state = (struct Npc_state *)0x02036E38;	//Start of NPC_STATE
	struct Npc_state *npc = npc_state + *current_npc;

	struct Wild_enocunter_tbl *encounter_tbl = (struct Wild_enocunter_tbl *)ENC_TBL_ADDR; //Start of encounter_tbl in ROM
	struct Npc_show_countdown *npc_show_ctdwn = (struct Npc_show_countdown *)NPC_CTDWN_ADDR; 
	
	void *precompiled_script_slot = (void *)PREC_SCRIPT_SLOT;		
	void *precompiled_script_slot_iterable = precompiled_script_slot;
	
	struct Script_state *env1 = (struct Script_state *)0x03000EB0;
	
	//Lookup wild encounter tbl
	u16 person_id = person_id_by_npc_id_and_map_and_bank(npc->local_id, *current_map, *current_bank);
	while(encounter_tbl->person_id != person_id){
		encounter_tbl++;
	}
	
	struct Encounter selected_encounter;
	do{	//Choose a random encounter
		u8 selected_pkmn = mod(rand(), 4);
		selected_encounter = encounter_tbl->encounters[selected_pkmn];
	}while (selected_encounter.species == 0xFFFF);
	
	//Look for a free spot to add the npc countdown
	for(u8 i = 0; i<10; i++){
		if(npc_show_ctdwn[i].person_id != 0){
			continue;
		}
		npc_show_ctdwn[i] = (struct Npc_show_countdown) {person_id, steps};
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
	*((u8 *)precompiled_script_slot_iterable) = 0x53; //hidesprite
	precompiled_script_slot_iterable++;
	*((u16 *)precompiled_script_slot_iterable) = npc->local_id; 
	precompiled_script_slot_iterable += 2;
	*((u8 *)precompiled_script_slot_iterable) = 0xB7; //dowildbattle
	precompiled_script_slot_iterable++;
	*((u8 *)precompiled_script_slot_iterable) = 0x02; //end
	
	env1->next_offset = (u32)precompiled_script_slot;
	env1->continue_exec = 1;
	script_exec_env_1(env1);
}