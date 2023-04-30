#include <genesis.h>
#include "resources.h"

void leftRotatebyOne(u16 arr[], u16 n)
{
    u16 temp = arr[0], i;
    for (i = 0; i < n - 1; i++)
        arr[i] = arr[i + 1];
    arr[n-1] = temp;
}

void leftRotate(u16 arr[], u16 d, u16 n)
{
    u16 i;
    for (i = 0; i < d; i++)
        leftRotatebyOne(arr, n);
}

void paletteRotationScene(){
	
	u16 my_pal0[16];
	PAL_setPalette(PAL0, img.palette->data, CPU);

	curTileInd = 16;
	PAL_getPalette(PAL0, my_pal0);
	SYS_doVBlankProcess();
	VDP_drawImageEx(BG_B, &img, TILE_ATTR_FULL(PAL0, 0, FALSE, FALSE, curTileInd), 0, 0, FALSE, TRUE);
	curTileInd += img.tileset->numTile;
	while(1){
		leftRotatebyOne(my_pal0, 16);
		PAL_setPalette(PAL0, my_pal0, DMA);
		SYS_doVBlankProcess();
	}
}

int main()
{
    paletteRotationScene();
    return (0);
}