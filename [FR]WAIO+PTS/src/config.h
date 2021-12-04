#ifndef CONFIG_H
#define CONFIG_H
#include "types.h"

//WAIO DEFS
#define NPC_CTDWN_ADDR    0xAAAAAAAA //0x28 free bytes in RAM
#define PREC_SCRIPT_SLOT  0xAAAAAAAA //0xE  free bytes in RAM
#define PREC_SCRIPT_SLOT2 0xAAAAAAAA //0x4  free bytes in RAM
#define ENC_TBL_ADDR      0xAAAAAAAA //Table of struct Wild_enocunter_tbl

//PTS DEFS
#define MAX_PTS_TASKS     0x5        //Number of maximum permanent tasks registrable
#define PTS_FREE_SPACE    0xAAAAAAAA //0x24 free bytes for each of the registrable tasks (MAX_PTS_TASKS)

#endif