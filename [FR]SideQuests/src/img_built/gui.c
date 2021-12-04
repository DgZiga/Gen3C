
//{{BLOCK(gui)

//======================================================================
//
//	gui, 256x160@4, 
//	Transparent color : 00,00,00
//	+ palette 14 entries, lz77 compressed
//	+ 77 tiles (t|f|p reduced) lz77 compressed
//	+ regular map (flat), lz77 compressed, 32x20 
//	Total size: 28 + 796 + 324 = 1148
//
//	Time-stamp: 2021-01-18, 22:58:21
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.6
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

const unsigned char guiTiles[796] __attribute__((aligned(4)))=
{
	0x10,0xA0,0x09,0x00,0x30,0x00,0x00,0xF0,0x01,0x90,0x05,0x55,0x55,0x55,0x55,0x0A,
	0x35,0x33,0x33,0x33,0x80,0x03,0x03,0x00,0x0F,0x20,0xB8,0x40,0x03,0x02,0x10,0x1F,
	0x00,0x1E,0x60,0x02,0x00,0x32,0x03,0x04,0x32,0x22,0x20,0x23,0x32,0x10,0x13,0x20,
	0x33,0x38,0x03,0x32,0xD0,0x1F,0x10,0x15,0x50,0x03,0x03,0x00,0x20,0x65,0x03,0xF0,
	0x1F,0x90,0x4B,0x33,0x33,0xE0,0x1F,0x03,0x00,0x15,0x1E,0x20,0x22,0x20,0x00,0x5C,
	0x20,0x03,0xF0,0x3F,0x80,0x69,0x03,0x7C,0x32,0xF0,0x5F,0xA0,0xAB,0x30,0xDF,0xF0,
	0x38,0x30,0xA6,0x02,0x00,0x7D,0x20,0xF0,0x7F,0xC0,0x02,0xF0,0x1F,0x70,0xA8,0x01,
	0x2A,0x22,0xF0,0x1F,0x80,0x31,0x2D,0x02,0x00,0x02,0x32,0x02,0x22,0x02,0xC0,0xF1,

	0x1F,0x01,0x33,0x53,0x33,0x03,0x20,0x33,0x35,0xDC,0x20,0x03,0xE1,0x5F,0x03,0x01,
	0x59,0x11,0x17,0x11,0x1B,0x02,0x32,0x73,0x00,0xF0,0xFF,0x20,0x21,0x40,0x03,0x00,
	0x00,0xF0,0x5F,0x91,0xAB,0xFB,0x01,0x8A,0xF0,0x1F,0x81,0xA0,0x01,0xE7,0xB1,0xDF,
	0x53,0x11,0xEA,0xA2,0x0E,0xDF,0xE0,0x9F,0x01,0x33,0x03,0x00,0xD7,0x01,0x7A,0x10,
	0x03,0xE2,0x1F,0xA1,0x03,0x37,0x20,0x03,0xF1,0x7F,0x82,0x4C,0x32,0xF1,0xDF,0x12,
	0x61,0x01,0x57,0x2E,0x20,0x22,0x02,0x82,0x44,0x10,0x03,0xA2,0x7F,0x00,0x9E,0x42,
	0x7E,0x34,0x01,0x38,0x80,0x03,0xD2,0x9F,0x02,0x9E,0x12,0x17,0x20,0x03,0x02,0xF3,
	0x01,0x40,0x42,0xBF,0xF0,0x03,0x40,0x0B,0x66,0x66,0xF0,0x01,0x90,0x05,0xBF,0x03,

	0x1B,0x23,0x43,0x1F,0x23,0x0F,0x80,0x0F,0x23,0x33,0x11,0x09,0x50,0x70,0x2C,0x00,
	0x22,0x03,0x1B,0x32,0x33,0x1B,0x61,0x6C,0x22,0x20,0x64,0x20,0x02,0xCC,0x02,0x69,
	0x20,0x20,0x02,0x6F,0x02,0x23,0x1D,0x22,0x22,0x23,0x93,0x4F,0x02,0xE9,0x21,0xA7,
	0x22,0x11,0xF7,0xD9,0x40,0x07,0xC1,0xAD,0x20,0x01,0xC8,0x03,0x0F,0x02,0x20,0x12,
	0x54,0x36,0x33,0x23,0xB0,0x3F,0x03,0x03,0x20,0x10,0x7A,0x10,0x07,0x02,0x02,0x20,
	0x30,0x02,0x23,0x32,0x32,0xC0,0x5F,0x20,0x58,0x22,0x00,0x76,0x20,0x00,0x97,0x02,
	0xEE,0x00,0x00,0x22,0x3D,0x32,0x22,0x01,0x5B,0x90,0x7F,0x11,0x6A,0x21,0x8B,0x33,
	0x02,0x6E,0x79,0x33,0xC0,0x1E,0xF0,0x01,0xF3,0x07,0x03,0x07,0x23,0x02,0x40,0x07,

	0x78,0x22,0x32,0x42,0x74,0x33,0x53,0x07,0x03,0x0F,0x00,0x22,0x22,0xF0,0x30,0x7B,
	0xA4,0x53,0x03,0x03,0x03,0x0B,0x22,0x32,0x35,0x03,0x43,0x32,0x10,0x03,0x53,0x33,
	0x23,0x32,0x14,0x8F,0x63,0x47,0xCD,0x03,0x44,0x01,0xC7,0x03,0x03,0x10,0x03,0x00,
	0xC9,0x23,0xC0,0xBF,0xD3,0x40,0x1E,0x20,0x03,0x22,0x00,0xDE,0x33,0x22,0xB1,0x41,
	0x03,0x82,0xFD,0x13,0x26,0x00,0x16,0x12,0x59,0x30,0x07,0xF3,0x0F,0x64,0xB4,0x00,
	0x03,0x02,0xDC,0x02,0x7B,0x15,0x11,0x53,0x54,0xF7,0x65,0x1E,0x04,0x2E,0x35,0x22,
	0x58,0x22,0x13,0x23,0x35,0x60,0xE1,0x04,0xE3,0x02,0x03,0x22,0x3E,0x22,0x03,0x03,
	0xB7,0x20,0x03,0x05,0x19,0xB1,0x9F,0x01,0x60,0x22,0xFD,0x20,0x81,0x01,0x82,0x04,

	0x71,0x00,0x1E,0xA1,0x7F,0x12,0x1C,0x20,0x00,0xE4,0x83,0x03,0x4A,0x32,0x20,0x23,
	0x20,0x32,0x00,0xA9,0xF1,0x63,0xFC,0x15,0x16,0x05,0x56,0x10,0x03,0xB0,0x3D,0x63,
	0x2F,0x01,0x7F,0x20,0x24,0xDB,0x13,0x33,0x00,0xBE,0x44,0x40,0xBE,0x25,0xB7,0x22,
	0x03,0x2F,0x93,0x33,0x39,0x22,0x54,0x00,0x9F,0x05,0xF0,0x55,0xD4,0x22,0x00,0x00,
	0x7B,0xA6,0x01,0x9B,0x32,0x20,0x83,0x22,0x00,0x02,0xBE,0xC1,0x5F,0x20,0x7B,0x20,
	0x00,0x1C,0x00,0x14,0x00,0x07,0x14,0xD2,0x23,0xD2,0x5F,0x32,0x3F,0xFD,0x22,0x43,
	0xF2,0x3F,0x25,0x42,0xF0,0x03,0x70,0x07,0x16,0x7F,0x65,0x03,0x76,0x09,0x15,0x11,
	0x11,0x11,0xF0,0x07,0x66,0x66,0x16,0x9F,0xDD,0x13,0x95,0x00,0x1E,0x11,0xF0,0x07,

	0xF0,0x1F,0xB0,0x07,0x56,0x20,0x5F,0xFD,0xF0,0x17,0x30,0x0F,0x20,0x7C,0xF0,0x1F,
	0x70,0x1F,0x70,0x5F,0x55,0x50,0x0E,0xF8,0xD0,0x07,0xF0,0xB7,0xB0,0x07,0xF0,0x57,
	0xC0,0x07,0x51,0x35,0x33,0xAB,0x14,0x64,0x11,0x07,0x84,0x56,0x07,0x87,0x51,0x07,
	0x8B,0x90,0x07,0xF4,0xD0,0x02,0x11,0xD6,0x17,0xB2,0x50,0x03,0x33,0x00,0x99,0x33,
	0x33,0x05,0x65,0x66,0x33,0x33,0x15,0x00,0x07,0x53,0x00,0x07,0x7F,0x53,0xA0,0x07,
	0xF0,0xB7,0xB0,0x07,0xD0,0x6F,0x10,0x87,0x20,0x8F,0x10,0x97,0xFF,0x31,0x3F,0x20,
	0x6B,0x42,0x4E,0xF7,0x1B,0xC0,0x6F,0x30,0x87,0x00,0x8F,0x00,0x71,0xFF,0x15,0x5C,
	0xF0,0xF7,0xB1,0x9F,0xF0,0x17,0xB1,0x9F,0xF0,0x17,0xB1,0x9F,0xF1,0x77,0xFF,0x70,

	0x07,0x40,0x3F,0xF0,0xF7,0x40,0x0F,0xF8,0xFB,0xF0,0x03,0xF0,0x03,0x39,0x2B,0xFC,
	0x52,0x3B,0xF1,0xA2,0x78,0x37,0xF6,0x7B,0xB2,0xF7,0x10,0x7F,
};

const unsigned short guiMap[162] __attribute__((aligned(4)))=
{
	0x0010,0x0005,0x0100,0x0200,0x0300,0x0400,0x0000,0x0005,
	0x0006,0x0007,0x0008,0x0940,0x0120,0x000A,0x000B,0x000C,
	0x0D04,0x0E00,0x0F00,0x1100,0x0010,0x1101,0x1200,0x1300,
	0x1400,0x1D00,0x1504,0x1600,0x1700,0x2B00,0x0008,0x1810,
	0x1900,0x0100,0x001A,0x001B,0x1C00,0x1D00,0x1E00,0x1F00,
	0x0400,0x0020,0x0021,0x2022,0x2301,0x0000,0x0024,0x0025,
	0x0026,0x0027,0x2840,0x1100,0x0029,0x002A,0x002B,0x2C00,
	0x2D00,0x2E00,0x2F00,0x0000,0x0030,0x0031,0x0032,0x0033,

	0x3444,0x3F20,0x0035,0x4036,0x3701,0x7100,0xF038,0xF001,
	0x4001,0x390B,0x3A00,0x7F20,0x3B11,0x3C00,0x0140,0x003D,
	0x403E,0xC47D,0x01F0,0x01F0,0x003F,0xC040,0x413F,0x0E00,
	0x0042,0x0C09,0x01F0,0x01F0,0x0D10,0x8E43,0x3FE0,0x0044,
	0xF045,0xF001,0x4001,0x460B,0xE0FF,0xF07F,0xF0BF,0xF001,
	0xF0BF,0xF0BF,0xF001,0xF001,0xFFBF,0xBFF0,0x01F0,0xBFF0,
	0xBFF0,0x01F0,0x01F0,0xBFF0,0xBFF0,0xF0FF,0xF001,0xF0BF,
	0xF0BF,0xF001,0xF001,0xF0BF,0xF0BF,0xFB01,0xBFF0,0xBFF0,

	0xBFF0,0x01F0,0xBFD0,0xF047,0xF09B,0xD701,0x01F0,0x0F00,
	0x2348,0x497F,0x9BF0,0x01F0,0x01F0,0x03FF,0x33A7,0xF07F,
	0xF03F,0xF001,0xF001,0xF03F,0xF001,0xF801,0x3FF0,0x3FF0,
	0x01F0,0x01F0,0x3F90,0x004A,0xE44B,0x01F0,0x01F0,0x01F0,
	0x4C00,0xBF24,
};

const unsigned char guiPal[28] __attribute__((aligned(4)))=
{
	0x10,0x20,0x00,0x00,0x00,0x00,0x00,0xC8,0x52,0x5A,0x67,0xFF,0x7F,0x00,0xFF,0x7F,
	0xAD,0x35,0x2D,0x63,0xFF,0x7F,0x20,0x00,0x00,0xB0,0x01,0x00,
};

//}}BLOCK(gui)