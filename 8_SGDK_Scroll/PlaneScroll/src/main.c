#include <genesis.h>
#include "resources.h"

int main()
{
	s16 x_offset = 0;
	VDP_setPlaneSize(32,32, TRUE);

    VDP_drawImage(BG_A, &img, -1, -3);
	VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);
    while(1)
    {
		x_offset += 10;
		if(x_offset > 256) {
			x_offset -= 256;
		}
		VDP_setHorizontalScroll(BG_A, x_offset);
        VDP_waitVSync();
    }
    return (0);
}
