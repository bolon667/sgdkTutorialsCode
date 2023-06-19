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

void clearTilesSprite(Sprite* spr){
	const u32 cleanTileset[8] =
	{
	// tile 0
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000
	};

	for(u16 i=0;i<8;i++){
		VDP_loadTileData(cleanTileset, (spr->attribut & TILE_INDEX_MASK)+i, 1, CPU);
	}
	
}

void drawProgressBarSprite(Sprite* spr, u16 value){
	const u32 tileSet0[8] =
	{
	// tile 0
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000
	};
	const u32 tileSet1[8] =
	{
	// tile 0
	0xb0000000,
	0xb0000000,
	0xb0000000,
	0xb0000000,
	0xb0000000,
	0xb0000000,
	0xb0000000,
	0xb0000000
	};
	const u32 tileSet2[8] =
	{
	// tile 0
	0xbb000000,
	0xbb000000,
	0xbb000000,
	0xbb000000,
	0xbb000000,
	0xbb000000,
	0xbb000000,
	0xbb000000
	};
	const u32 tileSet3[8] =
	{
	// tile 0
	0xbbb00000,
	0xbbb00000,
	0xbbb00000,
	0xbbb00000,
	0xbbb00000,
	0xbbb00000,
	0xbbb00000,
	0xbbb00000
	};
	const u32 tileSet4[8] =
	{
	// tile 0
	0xbbbb0000,
	0xbbbb0000,
	0xbbbb0000,
	0xbbbb0000,
	0xbbbb0000,
	0xbbbb0000,
	0xbbbb0000,
	0xbbbb0000
	};
	const u32 tileSet5[8] =
	{
	// tile 0
	0xbbbbb000,
	0xbbbbb000,
	0xbbbbb000,
	0xbbbbb000,
	0xbbbbb000,
	0xbbbbb000,
	0xbbbbb000,
	0xbbbbb000
	};
	const u32 tileSet6[8] =
	{
	// tile 0
	0xbbbbbb00,
	0xbbbbbb00,
	0xbbbbbb00,
	0xbbbbbb00,
	0xbbbbbb00,
	0xbbbbbb00,
	0xbbbbbb00,
	0xbbbbbb00
	};
	const u32 tileSet7[8] =
	{
	// tile 0
	0xbbbbbbb0,
	0xbbbbbbb0,
	0xbbbbbbb0,
	0xbbbbbbb0,
	0xbbbbbbb0,
	0xbbbbbbb0,
	0xbbbbbbb0,
	0xbbbbbbb0
	};
	const u32 tileSet8[8] =
	{
	// tile 0
	0xbbbbbbbb,
	0xbbbbbbbb,
	0xbbbbbbbb,
	0xbbbbbbbb,
	0xbbbbbbbb,
	0xbbbbbbbb,
	0xbbbbbbbb,
	0xbbbbbbbb
	};

	const progressTilesets[] = {tileSet0,tileSet1,tileSet2,tileSet3,tileSet4,tileSet5,tileSet6,tileSet7,tileSet8};

	s16 remain = value;
	u16 curTileX = 0;
	while(1) {
		if(remain >= 8){
			VDP_loadTileData(progressTilesets[8], (spr->attribut & TILE_INDEX_MASK)+curTileX, 1, CPU);
			
		} else {
			VDP_loadTileData(progressTilesets[remain], (spr->attribut & TILE_INDEX_MASK)+curTileX, 1, CPU);
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
	

	SPR_init();
	Sprite* progressSpr = SPR_addSprite(&spr_progressBar, 0, 16, TILE_ATTR(PAL0, 11, FALSE, FALSE));




	//Super test
	u16 curHp = 0;
	u16 curHpSpr = 0;
	while(1){
		drawProgressBar(BG_A, progressBarIndex, PAL0, 0,0, curHp);
		drawProgressBarSprite(progressSpr, curHpSpr);
		curHp++;
		curHpSpr++;
		if(curHpSpr > 50){
			clearTilesSprite(progressSpr);
			curHpSpr = 0;
		}
		if(curHp > 200){
		 	curHp = 0;
		 	VDP_clearTextBG(BG_A, 0,0,25);
		}
		SPR_update();
		SYS_doVBlankProcess();
		
	}
    return (0);
}
