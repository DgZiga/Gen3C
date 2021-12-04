#ifndef NPC_SHOW_CTDWN_H
#define NPC_SHOW_CTDWN_H


struct Npc_show_countdown{
	u16 person_id;
	u16 steps_no; //I doubt anybody will ever use more than 255 steps for this, but this all had to be 4-aligned, so...
};

#endif