#include <genesis.h>
#include "resources.h"

u16 array_u16len(const u16 *arr)
{
    const u16 *src;

    src = arr;
    while (*src++);

    return (src - arr) - 1;
}

void VDP_drawTextOffset(VDPPlane plane, const u16 *vram_offsets, u16 len, u16 first_tile, u16 x, u16 y)
{
    u16 i, pw, ph, curX;
	
	//u16 encodingOffset = 208;
	u16 encodingOffset = 48;

    // get the horizontal plane size (in cell)
    pw = (plane == WINDOW)?windowWidth:planeWidth;
    ph = (plane == WINDOW)?32:planeHeight;

    // string outside plane --> exit
    if ((x >= pw) || (y >= ph))
        return;

    //len = array_u16len(vram_offsets); иногда работает иногда нет, забил на эту функцию теперь ввожу длину ручками.

    // if string don't fit in plane, we cut it
    if (len > (pw - x))
        len = pw - x;
    i = 0;
	curX = 1;
	u16 curTileInd = 0;
	PAL_setColor(16+1,RGB24_TO_VDPCOLOR(0xffffff));
    while(i < len) {
        curTileInd = first_tile-1 + vram_offsets[i]; 
		//KLog_S1("curTile: ", curTileInd);
		
		VDP_setTileMapXY(plane, TILE_ATTR_FULL(PAL1,0,FALSE,FALSE,curTileInd), curX, y);
		i++;
		curX++;
	}
}


void drawCharCode(const char ch){
	KLog_S1("fdsdf: ", (int)ch);
}

int main()
{
    VDP_drawImage(BG_A, &img, 0, 0);
	u16 ind = 1300;
	
    VDP_loadTileSet(&font_rus, ind, DMA);
	u16 textArr[15] = {49, 86, 79, 76, 88, 72, 74, 83, 103, 102, 1, 51, 37, 38, 44};
	u16 textArr2[28] = {52, 77, 87, 77, 88, 100, 13, 1, 90, 99, 1, 87, 86, 85, 80, 84, 72, 77, 96, 100, 1, 88, 91, 89, 89, 82, 80, 81};
    while(1)
    {
		VDP_drawTextOffset(BG_A, textArr, 15, ind, 1, 1);
		VDP_drawTextOffset(BG_A, textArr2, 28, ind, 1, 2);
		//drawCharCode('а');
        SYS_doVBlankProcess();
    }
    return (0);
}
