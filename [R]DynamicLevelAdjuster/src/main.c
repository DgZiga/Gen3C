#include "types.h"
#include "include/trainer.h"
#include "include/pokemon.h"

u8 check_flag(u16 flag_id);

/* Parameters r0 and r1 are "padders" so that lvl and pkmnIdx will be recognized as r2 and r3 */
u32 exec(u32 r0, u32 r1, u32 default_lvl, u32 pkmn_idx) {
	
	struct Pokemon *player_party = (struct Pokemon *) 0x03004360;
	struct Trainer *trainer_tbl = (struct Trainer *) 0x081F04FC;
	u16 *trainer_id = (u16 *)0x0202FF5E;
	u8 tolerance = 10;

	if(!check_flag(0x1200)){
		return default_lvl;
	}
	
	u8 avg_lvl;
	u8 modifier;
	
	// ------ RETRIEVE AVG_LVL ------//
	u8 valid_pkmn = 0;
	u8 max_lvl = 0;
	u16 sum_of_levels = 0; 
	
	//First loop: evaluate valid_pkmn and max_lvl
	for(u8 i=0; i < 6; i++){
		if(player_party[i].pid != 0 && player_party[i].checksum != 0 ){
			if(player_party[i].level > max_lvl){
				max_lvl = player_party[i].level;
			}
		}
	}
	
	u8 threshold = max_lvl < tolerance ? 1 : max_lvl - tolerance;
	
	//Second loop: evaluate sum_of_levels (This needs to be separated from the first loop as we only want to take into consideration pokémons that are at most 'tolerance' levels down from the highest one
	for(u8 i=0; i < 6; i++){
		if(player_party[i].level > threshold ){ //Don't check for pkmn existance: level will be 0 if the slot is empty anyway
			valid_pkmn++;
			sum_of_levels += player_party[i].level;
		}
	}
	
	avg_lvl = sum_of_levels / valid_pkmn;
	
	// ------ CHECK THAT CONTINUING TO EXECUTE THIS ROUTINE WOULD MAKE SENSE ------//
	if(default_lvl > avg_lvl){
		return default_lvl;
	}
	
	// ------ RETRIEVE MODIFIER ------//
	u32 ai_bitmap = trainer_tbl[*trainer_id].ai_flags;
	
	u8 ai_bits_set = 0; //Count number of set bits in the AI to understand how "smart" is this trainer
	while(ai_bitmap){
		ai_bits_set += ai_bitmap & 1;
		ai_bitmap >>= 1;
	}
	
	if(ai_bits_set <= 2){
		modifier = 1;
	}else if(ai_bits_set <= 4){
		modifier = 2;
	}else {
		modifier = 3;
	}
	
	// ------ EVALUATE LVL ------//
	u8 cap = 3 + default_lvl + ((pkmn_idx +2) >>1) * modifier;
	
	if(avg_lvl > cap){
		return cap;
	} else{
		return avg_lvl;
	}
}
