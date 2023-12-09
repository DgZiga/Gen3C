#ifndef GUI_H
#define GUI_H

#include <pokeagb/pokeagb.h>
#include "../config.h"
#define rgb5(r, g, b) (u16)((r >> 3) | ((g >> 3) << 5) | ((b >> 3) << 10))

extern void c2_gui();
extern void vblank_cb_spq();
extern void gui_exit();

#endif