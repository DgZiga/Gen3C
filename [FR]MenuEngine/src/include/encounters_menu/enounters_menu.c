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

/*
debugger> d 0x0881295C 100
0881295c  b5f0 push {r4-r7,lr}
0881295e  46de mov lr, r11
08812960  4657 mov r7, r10
08812962  464e mov r6, r9
08812964  4645 mov r5, r8
08812966  b5e0 push {r5-r7,lr}
08812968  4b89 ldr r3, [$08812b90] (=$08082935) ;get_wild_data_index_for_map
0881296a  b097 add sp, -#0x5c
0881296c  f000 bl $08812ba4
08812970  0083 lsl r3, r0, #0x02
08812972  181b add r3, r3, r0
08812974  4887 ldr r0, [$08812b94] (=$083c9cb8)
08812976  009b lsl r3, r3, #0x02
08812978  18c0 add r0, r0, r3
0881297a  6883 ldr r3, [r0, #0x8]
0881297c  9303 str r3, [sp, #0xc]
0881297e  68c3 ldr r3, [r0, #0xc]
08812980  9302 str r3, [sp, #0x8]
08812982  6903 ldr r3, [r0, #0x10]
08812984  9301 str r3, [sp, #0x4]
08812986  6843 ldr r3, [r0, #0x4]
08812988  685e ldr r6, [r3, #0x4]
0881298a  4b83 ldr r3, [$08812b98] (=$088139d8)
0881298c  4698 mov r8, r3
0881298e  af10 add r7, sp, #0x40
08812990  003b lsl r3, r7, #0x00
08812992  4642 mov r2, r8
08812994  ca13 ldmia r2!, {r0,r1,r4}
08812996  c313 stmia r3!, {r0,r1,r4}
08812998  ca13 ldmia r2!, {r0,r1,r4}
0881299a  c313 stmia r3!, {r0,r1,r4}
0881299c  1cb4 add r4, r6, #0x2
0881299e  3632 add r6, #0x32
088129a0  e002 b $088129a8
088129a2  3404 add r4, #0x4
088129a4  42b4 cmp r4, r6
088129a6  d00f beq $088129c8
088129a8  8825 ldrh r5, [r4, #0x0]
088129aa  210c mov r1, #0xc
088129ac  002a lsl r2, r5, #0x00
088129ae  0038 lsl r0, r7, #0x00
088129b0  f7ff bl $08812900      ;r2 here is species
088129b4  2800 cmp r0, #0x0
088129b6  d1f4 bne $088129a2
088129b8  002a lsl r2, r5, #0x00
088129ba  210c mov r1, #0xc
088129bc  0038 lsl r0, r7, #0x00
088129be  3404 add r4, #0x4
088129c0  f7ff bl $08812928
088129c4  42b4 cmp r4, r6
088129c6  d1ef bne $088129a8
088129c8  ab16 add r3, sp, #0x58
088129ca  469a mov r10, r3
088129cc  4b73 ldr r3, [$08812b9c] (=$0000ffff)
088129ce  4699 mov r9, r3
088129d0  4b73 ldr r3, [$08812ba0] (=$08812251)
088129d2  003d lsl r5, r7, #0x00
088129d4  2610 mov r6, #0x10
088129d6  2429 mov r4, #0x29
088129d8  469b mov r11, r3
088129da  e005 b $088129e8
088129dc  3601 add r6, #0x1
088129de  0636 lsl r6, r6, #0x18
088129e0  0e36 lsr r6, r6, #0x18
088129e2  3502 add r5, #0x2
088129e4  4555 cmp r5, r10
088129e6  d014 beq $08812a12
088129e8  8828 ldrh r0, [r5, #0x0]
088129ea  4548 cmp r0, r9
088129ec  d0f9 beq $088129e2
088129ee  0421 lsl r1, r4, #0x10
088129f0  0432 lsl r2, r6, #0x10
088129f2  3418 add r4, #0x18
088129f4  1412 asr r2, r2, #0x10
088129f6  1409 asr r1, r1, #0x10
088129f8  0624 lsl r4, r4, #0x18
088129fa  f000 bl $08812bac
088129fe  0e24 lsr r4, r4, #0x18
08812a00  2cb8 cmp r4, #0xb8
08812a02  d9eb bls $088129dc
08812a04  3619 add r6, #0x19
08812a06  0636 lsl r6, r6, #0x18
08812a08  3502 add r5, #0x2
08812a0a  2429 mov r4, #0x29
08812a0c  0e36 lsr r6, r6, #0x18
08812a0e  4555 cmp r5, r10
08812a10  d1ea bne $088129e8
08812a12  9b03 ldr r3, [sp, #0xc]
08812a14  ac05 add r4, sp, #0x14
08812a16  685a ldr r2, [r3, #0x4]
08812a18  4643 mov r3, r8
08812a1a  0021 lsl r1, r4, #0x00
08812a1c  3318 add r3, #0x18
08812a1e  cb21 ldmia r3!, {r0,r5}
08812a20  c121 stmia r1!, {r0,r5}
08812a22  881b ldrh r3, [r3, #0x0]
*/

extern const struct Template bulbtemp;
void breakpoint(u16 different_species[]);
/*
 * get_wild_data_index_for_map is wrong in pokeagb: return is u16 not u8
 * @address{BPRE,08082934}
 */
extern u16 get_wild_data_index_for_map_working(void);

void encounters_menu_on_load(){
    u16 wild_encounter_id = get_wild_data_index_for_map_working();

    if(wild_encounter_id == 0xFFFF){ //area with no encounters
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