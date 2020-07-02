struct Trainer {
    u8 	flags;
    u8 	t_class;
    u8 	music;
    u8 	sprite;
    u8 	name[0xC];
    u16 items[4];
    u8 	double_battle_flag;
    u32 ai_flags;
    u8 	party_size;
    u32 party_ptr;
};
