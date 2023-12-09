#include "poketools.h"

#ifndef POKETOOLS_C
#define POKETOOLS_C

struct TextColor menu_text_black = {0, 2, 3};
struct Textbox tbox = {0, 19, 1, 10, TOOL_COUNT << 1, 0xF, 0x130};

void close_startmenu() {
	safari_stepscount_close();
	sm_close_description();
	sm_close_menu();
}

void tool_selection(u8 task_id) {
    #define priv0 tasks[task_id].priv[0]
    switch (priv0) {
        case 0:
            if (script_env_2_is_enabled())
                return;
            priv0++;
        break;
        case 1:
            script_env_enable();
            u8 boxid = rboxid_init(&tbox);
            rboxid_clear_pixels(boxid, 0x11);
            outline_box(boxid, 1, 0x214, 0xE);
            rboxid_print(boxid, 1, 8, 2, &menu_text_black, 0, menu_text);
            choice_setup_simple(boxid, 2, 0, 0, 15, TOOL_COUNT, 0);
            rboxid_update(boxid, 3);
            rboxid_tilemap_update(boxid);
            *boxid_addr = boxid;
            priv0++;
            task_del(task_id);
            break;
    };

}

bool make_choice(u32 choice_id) {//true=action happended, false=id is not mapped, nothing happened
    if (choice_id > sizeof(IMPLEMENTED_INTERFACES) / sizeof(IMPLEMENTED_INTERFACES[0])) {// OutOfBounds
        return false;
    } 
    close_startmenu();
    new_gui_main(IMPLEMENTED_INTERFACES[choice_id]);
    return true;
}

void clear_tmp_menu(){
    rboxid_clean(*boxid_addr, 1);
    rboxid_free(*boxid_addr);
    /*script_env_disable();
    close_startmenu();*/
}

void sm_poketools() {
    close_startmenu();
    task_add(tool_selection, 0);
}


#endif