#ifndef INTERFACE_DEFINITION_H
#define INTERFACE_DEFINITION_H
#include <pokeagb/pokeagb.h>

struct InterfaceDefinition{
    struct BgConfig* gui_bg_config;
    const u16* gui_text_pal;
    const u16* (*get_bg_map)();
    const u8* (*get_bg_tilesets)();
    const u8* (*get_bg_pal)();
    struct TextboxTemplate* textboxes; //larghezza salta di 8px in 8 px. Lunghezza sempre di 8px in 8 px ma è come se ci aggiungessi sempre 1 (parte da 8 px)
    void (*on_load)();
    void (*on_key_a)();
    void (*on_key_b)();
    void (*on_key_start)();
    void (*on_key_select)();
    void (*on_key_l)();
    void (*on_key_r)();
    void (*on_key_up)();
    void (*on_key_down)();
    void (*on_key_left)();
    void (*on_key_right)();
};

#endif