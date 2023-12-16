#ifndef ENCOUNTERS_MENU_2_C
#define ENCOUNTERS_MENU_2_C
#include "encounters_menu.h"
struct BgConfig new_menu_bg_config[4];
struct TextboxTemplate test_boxes[];
const u16 test_text_pal[];
void do_nothing();
void exit();
void encounters_menu_on_load();
const u8*  encounters_menu_get_bg_pal();
const u16* encounters_menu_get_bg_map();
const u8*  encounters_menu_get_bg_tiles();

const struct InterfaceDefinition ENCOUNTERS_MENU_DEFINITION = {
    .gui_bg_config =new_menu_bg_config, 
    .gui_text_pal  =test_text_pal,
    .get_bg_map        =encounters_menu_get_bg_map, 
    .get_bg_tilesets   =encounters_menu_get_bg_tiles,
    .get_bg_pal        =encounters_menu_get_bg_pal, 
    .textboxes     =test_boxes,
    .on_load=      encounters_menu_on_load,
    .on_key_a=     do_nothing,
    .on_key_b=     exit,
    .on_key_start= do_nothing,
    .on_key_select=do_nothing,
    .on_key_l=     do_nothing,
    .on_key_r=     do_nothing,
    .on_key_up=    do_nothing,
    .on_key_down=  do_nothing,
    .on_key_left=  do_nothing,
    .on_key_right= do_nothing,
};

const u16* encounters_menu_get_bg_map(){
    return encounters_menu_guiMap;
}
const u8* encounters_menu_get_bg_tiles(){
    return encounters_menu_guiTiles;
}
const u8* encounters_menu_get_bg_pal(){
    return encounters_menu_guiPal;
}

void do_nothing(){
    return;
}

void exit(){
    audio_play(SOUND_GENERIC_CLINK);
    super.multi_purpose_state_tracker=0;
    set_callback1(gui_exit);
}

const u16 EMPTY_SPECIES = 0xFFFF;


bool species_array_contains(u16 *arr, u32 arr_size, u16 val){
        bool already_present = false;
        for(u8 j=0; j<arr_size && !already_present; j++){
            if(val == arr[j]){
                already_present = true;
            }
        }
        return already_present;
}
bool populate_species_array(u16 *arr, u32 arr_size, u16 val){
        for(u8 i=0; i<arr_size; i++){
            if(arr[i] == EMPTY_SPECIES){
                arr[i] = val;
                return true;
            }
        }
        return false;
}


#define GRASS_ENCOUNTERS 12
#define WATER_ENCOUNTERS 5
#define FISH_ENCOUNTERS 10
#define TREE_ENCOUNTERS 5
#define LEFT_MARGIN 41
#define ICON_W 24

extern const struct Template bulbtemp;
void breakpoint(u16 different_species[]);
void encounters_menu_on_load(){
    u8 wild_encounter_id = get_wild_data_index_for_map();

    if(wild_encounter_id == 0xFFFF){ //TODO rethink
        return;
    }
    struct map_wild_pokemon_data curr_data = wild_pokemon_data[wild_encounter_id];
    //Handle grass
    struct wild_pokemon *grass_encounters = curr_data.grass_encounter->wild_encounters->wild_grass;
    u16 grass_different_species[GRASS_ENCOUNTERS] = {EMPTY_SPECIES, EMPTY_SPECIES, EMPTY_SPECIES, EMPTY_SPECIES, EMPTY_SPECIES, EMPTY_SPECIES, EMPTY_SPECIES, EMPTY_SPECIES, EMPTY_SPECIES, EMPTY_SPECIES, EMPTY_SPECIES, EMPTY_SPECIES};
    for(u8 i=0; i<GRASS_ENCOUNTERS; i++){
        if(!species_array_contains(grass_different_species, GRASS_ENCOUNTERS, grass_encounters[i].species)){
            populate_species_array(grass_different_species, GRASS_ENCOUNTERS, grass_encounters[i].species);
        }
    }
    u8 x_off = LEFT_MARGIN;
    u8 y_off = 16;
    for(u8 i=0; i<sizeof(grass_different_species)/sizeof(grass_different_species[0]); i++){
        if(grass_different_species[i] != EMPTY_SPECIES){
            display_pokemon_icon(grass_different_species[i], x_off, y_off++);
            x_off+=ICON_W;
            if(x_off >= LEFT_MARGIN+ICON_W*GRASS_ENCOUNTERS/2){
                x_off = LEFT_MARGIN;
                y_off += 24;
            }
        }
    }
    
    //Handle water
    struct wild_pokemon *water_encounters = curr_data.water_encounter->wild_encounters->wild_water;
    u16 water_different_species[WATER_ENCOUNTERS] = {EMPTY_SPECIES, EMPTY_SPECIES, EMPTY_SPECIES, EMPTY_SPECIES, EMPTY_SPECIES};
    for(u8 i=0; i<WATER_ENCOUNTERS; i++){
        if(!species_array_contains(water_different_species, WATER_ENCOUNTERS, water_encounters[i].species)){
            populate_species_array(water_different_species, WATER_ENCOUNTERS, water_encounters[i].species);
        }
    }
    x_off = LEFT_MARGIN;
    y_off = 70;
    for(u8 i=0; i<sizeof(water_different_species)/sizeof(water_different_species[0]); i++){
        if(water_different_species[i] != EMPTY_SPECIES){
            display_pokemon_icon(water_different_species[i], x_off, y_off++);
            x_off+=ICON_W;

        }
    }    
    
    //Handle fish
    struct wild_pokemon *fish_encounters = curr_data.fishing_encounter->wild_encounters->wild_fishing;
    u16 fish_different_species[FISH_ENCOUNTERS] = {EMPTY_SPECIES, EMPTY_SPECIES, EMPTY_SPECIES, EMPTY_SPECIES, EMPTY_SPECIES, EMPTY_SPECIES, EMPTY_SPECIES, EMPTY_SPECIES, EMPTY_SPECIES, EMPTY_SPECIES};
    for(u8 i=0; i<FISH_ENCOUNTERS; i++){
        if(!species_array_contains(fish_different_species, FISH_ENCOUNTERS, fish_encounters[i].species)){
            populate_species_array(fish_different_species, FISH_ENCOUNTERS, fish_encounters[i].species);
        }
    }
    x_off = LEFT_MARGIN;
    y_off = 96;
    for(u8 i=0; i<sizeof(fish_different_species)/sizeof(fish_different_species[0]); i++){
        if(fish_different_species[i] != EMPTY_SPECIES){
            display_pokemon_icon(fish_different_species[i], x_off, y_off);
            x_off+=ICON_W;
            if(x_off >= LEFT_MARGIN+ICON_W*FISH_ENCOUNTERS/2){
                x_off = LEFT_MARGIN;
                y_off += 24;
            }
        }
    }

    //Handle tree
    struct wild_pokemon *tree_encounters = curr_data.tree_encounter->wild_encounters->wild_tree;
    u16 tree_different_species[TREE_ENCOUNTERS] = {EMPTY_SPECIES, EMPTY_SPECIES, EMPTY_SPECIES, EMPTY_SPECIES, EMPTY_SPECIES};
    for(u8 i=0; i<TREE_ENCOUNTERS; i++){
        if(!species_array_contains(tree_different_species, TREE_ENCOUNTERS, tree_encounters[i].species)){
            populate_species_array(tree_different_species, TREE_ENCOUNTERS, tree_encounters[i].species);
        }
    }
    x_off = LEFT_MARGIN;
    y_off = 96;
    for(u8 i=0; i<sizeof(tree_different_species)/sizeof(tree_different_species[0]); i++){
        if(tree_different_species[i] != EMPTY_SPECIES){
            display_pokemon_icon(tree_different_species[i], x_off, y_off);
            x_off+=ICON_W;
            if(x_off >= LEFT_MARGIN+ICON_W*TREE_ENCOUNTERS/2){
                x_off = LEFT_MARGIN;
                y_off += 24;
            }
        }
    }
}

struct BgConfig new_menu_bg_config[4] = {
    {.padding=0, .b_padding=0, .priority=2, .palette=0, .size=0, .map_base=29, .character_base=2, .bgid=0, }, 
    {.padding=0, .b_padding=0, .priority=3, .palette=0, .size=0, .map_base=28, .character_base=0, .bgid=1, }, 
    {.padding=0, .b_padding=0, .priority=3, .palette=0, .size=0, .map_base=30, .character_base=2, .bgid=2, }, 
    {.padding=0, .b_padding=0, .priority=3, .palette=0, .size=1, .map_base=31, .character_base=3, .bgid=3, } };

//larghezza salta di 8px in 8 px
// lunghezza sempre di 8px in 8 px ma è come se ci aggiungessi sempre 1 (parte da 8 px)
struct TextboxTemplate test_boxes[] = {
    {
        /*q1Title */
        .bg_id = 0,
        .x = 8,
        .y = 3,
        .width = 20,
        .height = 2,
        .pal_id = 15,
        .charbase = 1,
    },
    {
        //q2Title 
        .bg_id = 0,
        .x = 8,
        .y = 6,
        .width = 20,
        .height = 2,
        .pal_id = 15,
        .charbase = 71,
    },
    {
        //q3Title 
        .bg_id = 0,
        .x = 8,
        .y = 9,
        .width = 20,
        .height = 2,
        .pal_id = 15,
        .charbase = 141,
    },
    {
        //q4Title 
        .bg_id = 0,
        .x = 8,
        .y = 12,
        .width = 20,
        .height = 2,
        .pal_id = 15,
        .charbase = 211,
    },
    {
        // desc 
        .bg_id = 0,
        .x = 2,
        .y = 15,
        .width = 20,
        .height = 5,
        .pal_id = 15,
        .charbase = 281,
    },
    {
        .bg_id = 0xFF, // marks the end of the tb array 
    },

};

const u16 test_text_pal[] = {
	rgb5(255, 0, 255), rgb5(248, 248, 248), rgb5(112, 112, 112),
	rgb5(0, 0, 0), rgb5(208, 208, 208), rgb5(76, 154, 38),
	rgb5(102, 194, 66), rgb5(168, 75, 76), rgb5(224, 114, 75),
	rgb5(180, 124, 41), rgb5(241, 188, 60), rgb5(255, 0, 255),
    rgb5(255, 0, 255), rgb5(255, 0, 255), rgb5(255, 133, 200), rgb5(64, 200, 248)};

#endif