#include <genesis.h>
#include "resources.h"


Map *bga;

s16 camPosX = 1;
s16 camPosY = 1;

fix32 posX = 0;
fix32 posY = 0;

void setCameraPosition(s16 x, s16 y)
{
    if ((x != camPosX) || (y != camPosY))
    {
        camPosX = x;
        camPosY = y;
        MAP_scrollTo(bga, x, y);
    }
}

void handleInput()
{
    u16 value = JOY_readJoypad(JOY_1);

        if (value & BUTTON_RIGHT)
        {
            posX += FIX32(5);
	    setCameraPosition(fix32ToInt(posX),fix32ToInt(posY));
        }
        else if (value & BUTTON_LEFT)
        {
            posX -= FIX32(5);
	    setCameraPosition(fix32ToInt(posX),fix32ToInt(posY));
        }

        if (value & BUTTON_UP)
        {
            posY -= FIX32(5);
	    setCameraPosition(fix32ToInt(posX),fix32ToInt(posY));
        }
        else if (value & BUTTON_DOWN)
        {
            posY += FIX32(5);
	    setCameraPosition(fix32ToInt(posX),fix32ToInt(posY));
        }
}

int main()
{
	u16 vramIndex = TILE_USER_INDEX;
	PAL_setPalette(PAL0, pal_img.data, CPU);


	
	VDP_loadTileSet(&tileset_img, vramIndex, DMA);
	bga = MAP_create(&map_img, BG_A, TILE_ATTR_FULL(0, FALSE, FALSE, FALSE, vramIndex));
    vramIndex += tileset_img.numTile;
	MAP_scrollTo(bga, 0, 0);
	s16 timer = 120;
	s16 cur_frame = 0;
	u16 baseTileIndex = bga->baseTile;
	//MAP_getTile(bga, 0,0) >> 4; Can't use it when scrolling
	TileSet** tile_anim[] = {&tileset_clock_anim1, &tileset_clock_anim2, &tileset_clock_anim3, &tileset_clock_anim4};
	while(1){
		handleInput();
		timer--;
		if(timer <= 0){
			VDP_loadTileSet(tile_anim[cur_frame], baseTileIndex, DMA);
			timer = 60;
			cur_frame++;
			if(cur_frame > 3){
				cur_frame = 0;
			}
		}
		SYS_doVBlankProcess();
	}
    return (0);
}
