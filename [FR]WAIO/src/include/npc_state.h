struct Coord {
	u16 x;
	u16 y;
};

struct Npc_state {
    u8 bitfield;
    u8 visual_ctrl; //don't mess with this
    u16 unknown;
    u8 oam_id;
    u8 type_id;
    u8 a_map_picture_no;
    u8 is_trainer;
    u8 local_id;
    u8 map_no;
    u8 map_bank;
    u8 height;
    struct Coord start_coord;	//Coord when entering map
    struct Coord to_coord;		//Coord of where you'll end up if moving, current Coord if static
    struct Coord from_coord;	//Coord of where you where if moving, current Coord if static
    u8 direction;				//0x11 = Down; 0x22 = Up; 0x33 = Left; 0x44 = Up;
    u8 movement_area;
	u8 objid_surfing;
	u8 objid_1B;
	u8 an_index__movement_behaviour;
	u8 sight_distance;
	u8 role_to;
	u8 role_from;
	u8 unknown1;
	u8 unknown_decrement_on_step;
	u8 field_22;
	u8 field_23;
};