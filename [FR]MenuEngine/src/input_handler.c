#ifndef INPUT_HANDLER_C
#define INPUT_HANDLER_C
#include "input_handler.h"
//Returns 1 if the input has been handled, 0 otherwise.
u8 hijack(){
    bool is_tmp_menu_open = *free_space == -1;
    u16 key_pressed = super.buttons_new_remapped;
    switch (key_pressed & (KEY_B | KEY_START | KEY_A | KEY_SELECT)) {
        case KEY_A:
            if (is_tmp_menu_open){     //If not in tmp, do nothing
                if(hijack_A_pressed()){//Press A in the temporary menu
                    *free_space = 0;
                }
                return 1;
            }
            return 0;
        case KEY_START:
        case KEY_B:
            if (is_tmp_menu_open){ //If not in tmp, let normal code handle it
                return hijack_close_tmp_menu();//Close tmp menu
            }
            return 0;
        case KEY_SELECT:
            if (is_tmp_menu_open){
                return hijack_close_tmp_menu();//Close tmp menu. TODO: Switch back to original menu
            } else {
                sm_poketools(); //already does close_startmenu();
                *free_space = -1;
                return 1;
            }
    };
    return 0;
}

bool hijack_A_pressed(){ //true=action happended, false=id is not mapped, nothing happened
    u8 choice = *curr_choice_id_addr;
    return make_choice(choice);
}

u8 hijack_close_tmp_menu(){
    clear_tmp_menu();  //clear rboxes
    *free_space = 0;   //setflag
    super.buttons_new_remapped = KEY_B; //Set cucrent key pressed to B and let normal code hanlde menu closure
    return 0; //let normal code hanlde B input
}

#endif