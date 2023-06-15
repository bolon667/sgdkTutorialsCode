#include <genesis.h>
#include "resources.h"


Map *bga;


void drawProgressBar(u8 plane, u16 progressBarRootIndex, u8 pal, s16 x, s16 y, u16 value){
	s16 remain = value;
	u16 curTileX = 0;
	while(1) {
		if(remain >= 8){
			VDP_setTileMapXY(plane, TILE_ATTR_FULL(pal, 15, 0, 0, progressBarRootIndex+8), x+curTileX, y);
			
		} else {
			VDP_setTileMapXY(plane, TILE_ATTR_FULL(pal, 15, 0, 0, progressBarRootIndex+remain), x+curTileX, y);
			return;
		}
		remain -= 8;
		curTileX++;
	}
	
}

int main()
{
	u16 vramIndex = TILE_USER_INDEX;
	PAL_setPalette(PAL0, pal_img.data, CPU);


	
	VDP_loadTileSet(&tileset_img, vramIndex, DMA_QUEUE);
	bga = MAP_create(&map_img, BG_A, TILE_USER_INDEX);
    vramIndex += tileset_img.numTile;
	MAP_scrollTo(bga, 0, 0);

	u16 progressBarIndex = vramIndex;
	VDP_loadTileSet(&ts_progressTile, progressBarIndex, DMA_QUEUE);


	//Super test
	u16 curHp = 0;
	while(1){
		drawProgressBar(BG_A, progressBarIndex, PAL0, 0,0, curHp);
		curHp++;
		if(curHp > 200){
			curHp = 0;
			VDP_clearTextBG(BG_A, 0,0,25);
		}
		
		SYS_doVBlankProcess();
	}
    return (0);
}
