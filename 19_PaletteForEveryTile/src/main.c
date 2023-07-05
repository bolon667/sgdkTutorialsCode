#include <genesis.h>
#include "resources.h"


Map *bga;


int main()
{
	u16 vramIndex = TILE_USER_INDEX;
	PAL_setColors(0, pal_img.data, 64, CPU);


	
	VDP_loadTileSet(&tileset_img, vramIndex, DMA);
	bga = MAP_create(&map_img, BG_A, TILE_USER_INDEX);
    vramIndex += tileset_img.numTile;
	MAP_scrollTo(bga, 0, 0);

	while(1){
		SYS_doVBlankProcess();
	}
    return (0);
}
