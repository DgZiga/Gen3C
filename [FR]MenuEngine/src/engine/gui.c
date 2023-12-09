#ifndef GUI_C
#define GUI_C

#include "gui.h"
	
void c2_gui(){
    obj_sync_superstate();
    objc_exec();
    process_palfade();
    task_exec();
    tilemaps_sync();
    // merge textbox and text tile maps
    remoboxes_upload_tilesets();
}

void vblank_cb_spq(){
	gpu_sprites_upload();
	copy_queue_process();
	gpu_pal_upload();
}


void gui_exit() {
    switch (super.multi_purpose_state_tracker) {
        case 0:
			fade_screen(0xFFFFFFFF, 0, 0, 16, 0x0000);
			gpu_sync_bg_hide(1);
			gpu_sync_bg_hide(0);	
			super.multi_purpose_state_tracker++;
            break;
        case 1:
            m4aMPlayVolumeControl(&mplay_BGM, 0xFFFF, 256);
            set_callback1(c1_overworld);
            set_callback2(c2_overworld_switch_start_menu);
			super.multi_purpose_state_tracker++;
            break;
		case 2:
            fade_screen(0xFFFFFFFF, 0, 16, 0, 0x0000);
			gpu_sync_bg_show(0);
			gpu_sync_bg_show(1);
			super.multi_purpose_state_tracker++;
		break;
	}
}


#endif