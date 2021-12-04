#ifndef SCRIPT_STATE_H
#define SCRIPT_STATE_H

struct Script_state{
	u8  sub_scripts_count;
	u8  continue_exec;
	u16 if_flag;
	u32 thumb_routine;
	u32 next_offset;
	u32 return_offsets[20];
	u32 cmd_tbl_ptr;
	u32 last_cmd_ptr;
	u32 memory_banks[4];
};

#endif