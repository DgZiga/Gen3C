#ifndef NEW_MENU_C
#define NEW_MENU_C
#include "new_menu.h"
struct BgConfig new_menu_bg_config[4];
struct TextboxTemplate test_boxes[];
const u16 test_text_pal[];
void do_nothing();
void exit();

const struct InterfaceDefinition NEW_MENU_DEFINITION = {
    .gui_bg_config =new_menu_bg_config, 
    .gui_text_pal  =test_text_pal,
    .bg_map        =new_menu_guiMap, 
    .bg_tilesets   =new_menu_guiTiles,
    .bg_pal        =new_menu_guiPal, 
    .textboxes     =test_boxes,
    .on_load=      do_nothing,
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


void do_nothing(){
    return;
}

void exit(){
    audio_play(SOUND_GENERIC_CLINK);
    super.multi_purpose_state_tracker=0;
    set_callback1(gui_exit);
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