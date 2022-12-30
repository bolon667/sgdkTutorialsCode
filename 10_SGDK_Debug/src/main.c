#include <genesis.h>
#include "resources.h"
#include "KDebug.h"

Map *bga;

s16 camPosX = -1;
s16 camPosY = -1;

fix32 posX = 0;
fix32 posY = 0;

bool paused = FALSE;

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

    if (!paused)
    {
        if (value & BUTTON_RIGHT)
        {
            posX += FIX32(5);
			setCameraPosition(fix32ToInt(posX),fix32ToInt(posY)-140);
        }
        else if (value & BUTTON_LEFT)
        {
            posX -= FIX32(5);
			setCameraPosition(fix32ToInt(posX),fix32ToInt(posY)-140);
        }

        if (value & BUTTON_UP)
        {
            posY -= FIX32(5);
			setCameraPosition(fix32ToInt(posX),fix32ToInt(posY)-140);
        }
        else if (value & BUTTON_DOWN)
        {
            posY += FIX32(5);
			setCameraPosition(fix32ToInt(posX),fix32ToInt(posY)-140);
        }
		
    }
}

int main()
{
	u16 ind;
	ind = TILE_USER_INDEX;
	
    VDP_loadTileSet(&bga_tileset, ind, DMA);
	bga = MAP_create(&bga_map, BG_B, TILE_ATTR_FULL(0, FALSE, FALSE, FALSE, TILE_USER_INDEX));
	
	setCameraPosition(fix32ToInt(posX),fix32ToInt(posY)-140);
	SYS_doVBlankProcess();
	
	PAL_setPalette(0, palette_all.data, DMA);
	
    while(1)
    {
		VDP_showFPS(FALSE);  
		handleInput();
        SYS_doVBlankProcess();
    }
	
    return (0);
}
