#include "types.h"
#include "include.h"

u8 flag_check(u16 flag_id);
u16 *var_8000 = (u16 *)0x20370B8;

void play_sound(u32 sound_id);

void do_dmg(u8 party_i, u32 currentHp){
	u32 maxHp = pokemon_getattr(&party[party_i], REQUEST_TOTAL_HP);
	u32 dmg = maxHp / 16 > 0 ? maxHp / 16 : 1;
	u32 newHp = currentHp - dmg <= 0 ? 1 : currentHp - dmg;
	pokemon_setattr(&party[party_i], REQUEST_CURRENT_HP, &newHp);
	play_sound(0x29);
	return;
}

void main() {
	u8 flagIsSet = flag_check(0x278);
	if(!flagIsSet){
		return;
	}
	if(*var_8000 < 5){
		*var_8000 += 1;
		return;
	}
	
	*var_8000 = 0;
	for(u8 i=0; i<5; i++){
		u32 currentHp 	= pokemon_getattr(&party[i], REQUEST_CURRENT_HP);
		u32 isEgg 		= pokemon_getattr(&party[i], REQUEST_IS_EGG);
		u32 species 	= pokemon_getattr(&party[i], REQUEST_SPECIES);
		u32 abilityBit 	= pokemon_getattr(&party[i], REQUEST_ABILITY_BIT);
		
		if(isEgg || species == 0 || currentHp <= 1){
			continue;
		}
		struct PokemonBaseStat pkmnBsStat = speciesTbl[species];
		enum PokemonAbility ablt = pkmnBsStat.ability[abilityBit]; 
		
		if(pkmnBsStat.type[0] == TYPE_GROUND || pkmnBsStat.type[0] == TYPE_ROCK || pkmnBsStat.type[0] == TYPE_STEEL || 
		   pkmnBsStat.type[1] == TYPE_GROUND || pkmnBsStat.type[1] == TYPE_ROCK || pkmnBsStat.type[1] == TYPE_STEEL || 
		   ablt == ABILITY_SAND_VEIL){
			continue;
		} else {
			do_dmg(i, currentHp);
		}
		
	}
	return;
}
