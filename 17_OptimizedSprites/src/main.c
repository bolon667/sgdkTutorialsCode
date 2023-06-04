#include <genesis.h>
#include "resources.h"


#define NUM_ENEMY       100

u16** sprTileIndexes[NUM_ENEMY];
Sprite* enemies[NUM_ENEMY];

// forward
static void frameChanged(Sprite* sprite);

int main()
{
	u16 vramIndex = TILE_USER_INDEX;
	u16 numTile;
	//spriteVramSize = 600;
	SPR_init();
	PAL_setPalette(PAL0, img.palette->data, CPU);
	VDP_drawImageEx(BG_A, &img, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, vramIndex), 0, 0, FALSE, FALSE);
	vramIndex += img.tileset->numTile;
	PAL_setPalette(PAL3, spr_sonic.palette->data, CPU);


	// enemies[0] = SPR_addSprite(&spr_sonic, 0, 0, TILE_ATTR(PAL3, 0, FALSE, FALSE));
	// SPR_setAnim(enemies[0], 2);
	// enemies[1] = SPR_addSprite(&spr_enemy02, 50, 0, TILE_ATTR(PAL3, 0, FALSE, FALSE));
	// enemies[0]->data = 0;
    // enemies[1]->data = 1;
	// // SPR_setAnim(enemies[1], 7);
	// sprTileIndexes[0] = SPR_loadAllFrames(&spr_sonic, vramIndex, &numTile);
	// vramIndex += numTile;
	// sprTileIndexes[1] = SPR_loadAllFrames(&spr_enemy02, vramIndex, &numTile);
	// vramIndex += numTile;

	// SPR_setFrameChangeCallback(enemies[0], &frameChanged);
	// SPR_setFrameChangeCallback(enemies[1], &frameChanged);
	// SPR_setAutoTileUpload(enemies[0], FALSE);
	// SPR_setAutoTileUpload(enemies[1], FALSE);

////////////////

	// sprTileIndexes[0] = SPR_loadAllFrames(&spr_sonic, vramIndex, &numTile);
	// for(u16 i=0;i<5;i++){
	// 	for(u16 j=0;j<6;j++){
	// 		const u16 enemyIndex = i+(i*j);
	// 		enemies[enemyIndex] = SPR_addSprite(&spr_sonic, i*30, j*30, TILE_ATTR(PAL3, 0, FALSE, FALSE));
	// 		if(enemies[enemyIndex] == NULL){
	// 			break;
	// 		}
	// 		SPR_setAutoTileUpload(enemies[enemyIndex], FALSE);
	// 		enemies[enemyIndex]->data = 0;
			
	// 		SPR_setFrameChangeCallback(enemies[enemyIndex], &frameChanged);
	// 		SPR_setAnim(enemies[enemyIndex], 2);
	// 		SPR_update();
	// 		SYS_doVBlankProcess();
	// 	}
	// }

/////////////////
	u16 curSpriteIndex = 1;
	enemies[0] = SPR_addSpriteEx(&spr_sonic, 100, 100, TILE_ATTR_FULL(PAL3, 0, FALSE, FALSE, vramIndex), curSpriteIndex, SPR_FLAG_AUTO_TILE_UPLOAD | SPR_FLAG_AUTO_SPRITE_ALLOC );
	curSpriteIndex++;
	SPR_setAnim(enemies[0], 2);

	//SPR_FLAG_AUTO_TILE_UPLOAD
	
	for(u16 i=0;i<5;i++){
		for(u16 j=0;j<6;j++){
			const u16 enemyIndex = i+(i*j);
			enemies[enemyIndex] = SPR_addSpriteEx(&spr_sonic, i*30, j*30, TILE_ATTR_FULL(PAL3, 0, FALSE, FALSE, vramIndex), curSpriteIndex, SPR_FLAG_AUTO_SPRITE_ALLOC);
			if(enemies[enemyIndex] == NULL){
				break;
			}
			SPR_setAnim(enemies[enemyIndex], 2);
			curSpriteIndex++;
		}
	}



/////////////////////////////////

	// SPR_update();
	// 	SYS_doVBlankProcess();
	
	// for(u16 i=0;i<5;i++){
	// 	for(u16 j=0;j<6;j++){
			
	// 		const u16 enemyIndex = i+(i*j);
	// 		enemies[enemyIndex] = SPR_addSpriteEx(&spr_sonic, i*30, j*30, TILE_ATTR(PAL3, 0, FALSE, FALSE), curSpriteIndex, SPR_FLAG_AUTO_TILE_UPLOAD);
	// 		if(enemies[enemyIndex] == NULL){
	// 			break;
	// 		}
	// 		//SPR_setVRAMTileIndex(enemies[enemyIndex], vramIndex);
	// 		//vramIndex = -1;
	// 		SPR_setAnim(enemies[enemyIndex], 2);
	// 		SPR_update();
	// 		SYS_doVBlankProcess();
	// 		curSpriteIndex++;
	// 	}
	// }


	// for(u16 i=5;i<8;i++){
	// 	for(u16 j=3;j<5;j++){
	// 		const u16 enemyIndex = i+(i*j);
	// 		enemies[enemyIndex] = SPR_addSprite(&spr_sonic, i*30, j*30, TILE_ATTR(PAL3, 0, FALSE, FALSE));
	// 		SPR_setAnim(enemies[enemyIndex], 2);
	// 	}
	// }
	
	



    
	while(1){
		VDP_showFPS(FALSE);  
		//KLog_S1("FPS:", getFPS());
		SPR_update();
		SYS_doVBlankProcess();
	}
    return (0);
}

static void frameChanged(Sprite* sprite)
{
    // get enemy index (stored in data field)
    u16 enemyIndex = sprite->data;
    // get VRAM tile index for this animation of this sprite
    u16 tileIndex = sprTileIndexes[enemyIndex][sprite->animInd][sprite->frameInd];
    // manually set tile index for the current frame (preloaded in VRAM)
    SPR_setVRAMTileIndex(sprite, tileIndex);
}