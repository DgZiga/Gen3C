#ifndef TASK_H
#define TASK_H

#include "../types.h"

struct Task {
    u32 routine_ptr;
	u16 local_data[16];
};
#endif