
/*#include <pokeagb/pokeagb.h>
#include "include/built_graphics/gui.h"
#include "include/agb_debug/debug.c"
#include "include/setup.h"
#include "include/gui.h"
#include "config.h"


#define CURSOR_TILES_TAG 0x6F
#define CURSOR_PALS_TAG 0x08

void close_startmenu() {
	safari_stepscount_close();
	sm_close_description();
	sm_close_menu();
}

int main() {
    close_startmenu();
    fade_screen(0xFFFFFFFF, 0, 0, 16, 0x0000);
    void gui_handler(void);
    set_callback1(gui_handler);
    super.multi_purpose_state_tracker = 0;
	return 1;
}


void gui_handler(){
	struct FadeControl pal_fade_control = *((struct FadeControl *)0x02037ab8);

	switch(super.multi_purpose_state_tracker){
		case 0:
            if (!pal_fade_control.active) {
				setup(); 					//clear all graphics
				rboxes_free(); 				//clear rboxes
				bgid_mod_x_offset(0, 0, 0);	//config bgs independently of their previous state
				bgid_mod_y_offset(0, 0, 0);
				bgid_mod_x_offset(1, 0, 0);
				bgid_mod_y_offset(1, 0, 0);
				gpu_tile_bg_drop_all_sets(0);
				bg_vram_setup(0, (struct BgConfig *)&bg_config_gui, 4);
				//Clear VRAM
				u32 set = 0;
				CpuFastSet((void*)&set, (void*)ADDR_VRAM, CPUModeFS(0x10000, CPUFSSET));
				//Hide BGs
				gpu_sync_bg_hide(1);
				gpu_sync_bg_hide(0);	
				//Set callbacks
				set_callback2(c2_gui);
				vblank_handler_set(vblank_cb_spq);
				set_callback1(gui_handler);
				
				super.multi_purpose_state_tracker++;;
			}
			break;
		case 1: { //Load backgground image, init rboxes and quest list
			//Load bg image
			void *quest_gbackbuffer = malloc(0x800);
			//(*DNavState)->backbuffer = dexnav_gbackbuffer;
			gpu_pal_apply((void *)(&gui_text_pal), 15 * 16, 32);
			gpu_pal_apply_compressed((void *)guiPal, 0, 32);
			LZ77UnCompWram((void *)guiMap, (void *)quest_gbackbuffer);
			lz77UnCompVram((void *)guiTiles, (void *)0x06000000);
			bgid_set_tilemap(1, quest_gbackbuffer);
			bgid_mark_for_sync(1);
			bgid_mark_for_sync(0);
			//init rboxes
			rbox_init_from_templates(quest_boxes_base);
			
			super.multi_purpose_state_tracker++;
		}
			break;
		case 2: //fill rboxes
            if (!pal_fade_control.active) { //Wait for fadescreen to stop
				// clean boxes
				for (u32 i = 0; i < 5; ++i) {
					rboxid_clear_pixels(i, 0);
				}
				
				super.multi_purpose_state_tracker++;
			}
		case 3: {//Display OWs 

			super.multi_purpose_state_tracker++;
		}
		case 4: // Show screen
            fade_screen(0xFFFFFFFF, 0, 16, 0, 0x0000);
			gpu_sync_bg_show(0);
			gpu_sync_bg_show(1);
            super.multi_purpose_state_tracker++;
			break;
		case 5: //Input control NOTE: L and R ARE INVERTED IN POKEAGB
			if (!pal_fade_control.active) { //Wait for fadescreen to end
                switch (super.buttons_new_remapped & (KEY_B | KEY_DOWN | KEY_UP | KEY_L | KEY_R | KEY_SELECT)) {
					case KEY_SELECT:
						break;
                    case KEY_R:
                        break;
                    case KEY_L: 
                        break;
                    case KEY_B:
                        return;
                    case KEY_DOWN:
                        break;
                    case KEY_UP:
                        break;
                };
            }
            break;
			
	}
	
	
}
*/