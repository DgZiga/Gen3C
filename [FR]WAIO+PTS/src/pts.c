/* PERMANENT TASK SYSTEM */
#include "types.h"
#include "config.h"
#include "include/task.h"

u8 add_permanent_task(u32 routine_ptr) {
	struct Task *permanent_task_tbl = (struct Task *)(PTS_FREE_SPACE);
	
	for(u8 i=0; i<MAX_PTS_TASKS; i++){
		if((permanent_task_tbl +i)->routine_ptr == 0){
			(permanent_task_tbl +i)->routine_ptr = routine_ptr;
			return 1;
		}
	}
	return 0;
}

u8 remove_permanent_task_by_idx(u8 i){
	struct Task *permanent_task_tbl = (struct Task *)(PTS_FREE_SPACE);
	
	if(i >= MAX_PTS_TASKS){
		return 0;
	}
	
	(permanent_task_tbl +i)->routine_ptr = 0;
	for(u8 j=0; j< sizeof((permanent_task_tbl +i)->local_data); j++){
		(permanent_task_tbl +i)->local_data[j] = 0;
	}
	
	return 1;
}

u8 remove_permanent_task_by_routine_ptr(u32 ptr){
	struct Task *permanent_task_tbl = (struct Task *)(PTS_FREE_SPACE);
	
	for(u8 i=0; i<MAX_PTS_TASKS; i++){
		if((permanent_task_tbl +i)->routine_ptr == ptr){
			(permanent_task_tbl +i)->routine_ptr = 0;
			for(u8 j=0; j< sizeof((permanent_task_tbl +i)->local_data); j++){
				(permanent_task_tbl +i)->local_data[j] = 0;
			}
			return 1;
		}
	}
	return 0;
}

void exec_tasks_at_free_space(){
	struct Task *permanent_task_tbl = (struct Task *)(PTS_FREE_SPACE);
    for(u8 i=0; i<MAX_PTS_TASKS; i++){
        if((permanent_task_tbl +i)->routine_ptr != 0){
            void (*funptr)() = (permanent_task_tbl +i)->routine_ptr;
            funptr();
        } 
	}
}