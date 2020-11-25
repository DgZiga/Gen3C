struct Coord {
	u16 x;
	u16 y;
};

//sizeof: 0x24
struct Npc_state {
    /*OFF: 0x0  */u8 bitfield;
    /*OFF: 0x1  */u8 visual_ctrl; 
    /*OFF: 0x2  */u16 unknown;
    /*OFF: 0x4  */u8 oam_id;
    /*OFF: 0x5  */u8 type_id;
    /*OFF: 0x6  */u8 a_map_picture_no;
    /*OFF: 0x7  */u8 is_trainer;
    /*OFF: 0x8  */u8 local_id;
    /*OFF: 0x9  */u8 map_no;
    /*OFF: 0xA  */u8 map_bank;
    /*OFF: 0xB  */u8 height;
    /*OFF: 0xC  */struct Coord start_coord;	//Coord when entering map
    /*OFF: 0x10 */struct Coord to_coord;		//Coord of where you'll end up if moving, current Coord if static
    /*OFF: 0x14 */struct Coord from_coord;	//Coord of where you where if moving, current Coord if static
    /*OFF: 0x18 */u8 direction;				//0x11 = Down; 0x22 = Up; 0x33 = Left; 0x44 = Up;
    /*OFF: 0x19 */u8 movement_area;
	/*OFF: 0x1a */u8 objid_surfing;
	/*OFF: 0x1b */u8 objid_1B;
	/*OFF: 0x1c */u8 an_index__movement_behaviour;
	/*OFF: 0x1d */u8 sight_distance;
	/*OFF: 0x1e */u8 role_to;
	/*OFF: 0x1f */u8 role_from;
	/*OFF: 0x20 */u8 unknown1;
	/*OFF: 0x21 */u8 unknown_decrement_on_step;
	/*OFF: 0x22 */u8 field_22;
	/*OFF: 0x23 */u8 field_23;
};