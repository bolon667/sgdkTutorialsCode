#include <genesis.h>
#include "resources.h"

int main()
{
	
	s16 offset_mask[6] = {0,5,10,15,20,25};
	s16 i = 0;
	VDP_setPlaneSize(32,32, TRUE);
	
    VDP_drawImage(BG_A, &img, 0, 0);
	VDP_setScrollingMode(HSCROLL_TILE , VSCROLL_2TILE);
    while(1)
    {
		VDP_setHorizontalScrollTile(BG_A, 3, offset_mask, 6, CPU);
		for(i = 0; i < 6; i++) offset_mask[i] = offset_mask[i]+i;
        VDP_waitVSync();
    }
    return (0);
}
