#include "types.h"
#include "include/task.h"

u8 add_permanent_task(u32 routine_ptr) {
	struct Task *permanent_task_tbl = (struct Task *)(0x02029314 /*Start_of_box*/ + 0x5DE0 /*Box #11*/);
	u8 max_task_no = 5;
	
	for(u8 i=0; i<max_task_no; i++){
		if((permanent_task_tbl +i)->routine_ptr == 0){
			(permanent_task_tbl +i)->routine_ptr = routine_ptr;
			return 1;
		}
	}
	return 0;
}

u8 remove_permanent_task_by_idx(u8 i){
	struct Task *permanent_task_tbl = (struct Task *)(0x02029314 /*Start_of_box*/ + 0x5DE0 /*Box #11*/);
	u8 max_task_no = 5;
	
	if(i >= max_task_no){
		return 0;
	}
	
	(permanent_task_tbl +i)->routine_ptr = 0;
	for(u8 j=0; j< sizeof((permanent_task_tbl +i)->local_data); j++){
		(permanent_task_tbl +i)->local_data[j] = 0;
	}
	
	return 1;
}

u8 remove_permanent_task_by_routine_ptr(u32 ptr){
	struct Task *permanent_task_tbl = (struct Task *)(0x02029314 /*Start_of_box*/ + 0x5DE0 /*Box #11*/);
	u8 max_task_no = 5;
	
	for(u8 i=0; i<max_task_no; i++){
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