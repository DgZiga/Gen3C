#ifndef WILD_ENC_CUST_TBL_H
#define WILD_ENC_CUST_TBL_H

struct Encounter{
	u16 species;
	u8 lvl;
	//Please note that after these 3 bytes there should be a 0xFF as padding to keep everything 4-aligned
};

struct Wild_enocunter_tbl{
	u16 person_id;
	struct Encounter encounters[4];
};
#endif