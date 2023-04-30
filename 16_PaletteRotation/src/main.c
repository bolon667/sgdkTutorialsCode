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
	
	VDP_resetScreen();
	SPR_init();
	VDP_setPlaneSize(64,32,TRUE);
	VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);
	VDP_setVerticalScroll(BG_B, 0);
	VDP_setVerticalScroll(BG_A, 0);
	VDP_setHorizontalScroll(BG_B, 0);
	VDP_setHorizontalScroll(BG_A, 0);
	
	u16 my_pal0[16];
	PAL_setPalette(PAL0, img.palette->data, CPU);

	
	curTileInd = 16;

	s16 pal0_timer = 3;
	
	PAL_getPalette(PAL0, my_pal0);
	SYS_doVBlankProcess();
	VDP_drawImageEx(BG_B, &img, TILE_ATTR_FULL(PAL0, 0, FALSE, FALSE, curTileInd), 0, 0, FALSE, TRUE);
	curTileInd += img.tileset->numTile;
	while(1){
		pal0_timer--;
		leftRotatebyOne(my_pal0, 16);
		PAL_setPalette(PAL0, my_pal0, DMA);
		// if(pal0_timer < 0){
		// 	pal0_timer = 3;
		// 	PAL_fadeToPalette(PAL0, my_pal0, 3, TRUE);
		// }
		

		SPR_update();
		SYS_doVBlankProcess();
	}
}

int main()
{
    paletteRotationScene();
    return (0);
}