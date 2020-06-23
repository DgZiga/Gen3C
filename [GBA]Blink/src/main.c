#include "types.h"
/*
The function uses 3 variables (in the example 8000 to 80002) with the following purposes:
1st: contains how much of the screen is being hidden
2nd: counts how many times the "blink" happened, which is the same as to count how many times the mosaicBgByte has changed
3rd: controls in which direction the scroll is going
*/

enum direction{
	UP = 0,
	DOWN,
};

void main() {
	
	u16 *scrollIndex = (u16 *)0x20370B8; 	//Var8000
	u16 *mosaicIndex = scrollIndex+1; 		//var8001
	u16 *scrollDirection = scrollIndex+2; 	//Var8002 0=UP, 1=DOWN
	
	//Reference: GBATek
	u16 *bgCtrlHWs = (u16 *)0x04000008;
	u8 *mosaicBgByte = (u8 *)0x0400004C;
	u8 *bottomMostWindowCoordinate = (u8 *)0x04000045;
	
	
	if(*mosaicIndex > 3 && *scrollDirection == DOWN){
		//Reset variables and addresses values
		*scrollIndex = 0;
		*mosaicIndex = 0;
		*scrollDirection = 0;
		*bottomMostWindowCoordinate = 0;
		*mosaicBgByte = 0;
		
		//Reset VBlank callback
		u32 *backupAddr = (u32 *)0xFFFFFFFF;
		u32 *vBlank_callback = (u32 *)0x30030F0;
		*vBlank_callback = *backupAddr;
		return;
	}
	
	//Settings:
	u8 maxCoord = 0xA0; 	//Values >A0 are discarded, as the GBA only has 160 horizontal lines
	u8 step = maxCoord/40;	//Change this to control the speed of the "blinking".
	u8 minCoord = step; 	//Should really be 0, but to be on the safe side just set it to "step"

	if(*scrollIndex == 0xFFFF){
		for(u8 i=0; i <4; i++){
			*bgCtrlHWs = *bgCtrlHWs | 0x40; //set "Mosaic" bit for every BG
			bgCtrlHWs += 2;
		}
		*mosaicBgByte = 0xFF; //Set Mosaic Byte to max
		*bottomMostWindowCoordinate = maxCoord;	
		*scrollIndex = maxCoord; //Black screen
		*mosaicIndex = 0;
		*scrollDirection = UP;
		return;
	}
	
	
	//Increase/decrease scrollIndex based on Direction
	if(*scrollDirection == UP){
		*scrollIndex = *scrollIndex - step;
	} else {
		*scrollIndex = *scrollIndex + step;
	}
	
	
	//Sync bottomMostWindowCoordinate with scrollIndex
	*bottomMostWindowCoordinate = *scrollIndex;
	
	
	if(*scrollIndex <= minCoord){ //If scrollIndex has reached its minimum (i.e. all the window is visible), then start scrolling down
		*scrollDirection = DOWN;
		
	}else if(*scrollIndex >= maxCoord){ //If scrollIndex has reached its maximum (i.e. no part of the window is visible), then start scrolling up AND update the mosaic byte
		*scrollDirection = UP;
		
		if(*mosaicIndex == 0){
			*mosaicBgByte = 0x77; //0111 0111
		} else if(*mosaicIndex == 1){
			*mosaicBgByte = 0x33; //0011 0011
		} else if(*mosaicIndex == 2){
			*mosaicBgByte = 0x11; //0001 0001
		} else if(*mosaicIndex == 3){
			*mosaicBgByte = 0x00; //0000 0000
		}
		*mosaicIndex += 1;
	}

}
