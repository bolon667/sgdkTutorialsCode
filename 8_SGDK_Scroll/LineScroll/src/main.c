#include <genesis.h>
#include "resources.h"

int main()
{
	s16 offsetMaskLine[224]; 
	VDP_setPlaneSize(32,32, TRUE);
	for(int i=0; i< 224; i++)
		offsetMaskLine[i] = 0;
    VDP_drawImage(BG_A, &img, 0, 0);
	VDP_setScrollingMode(HSCROLL_LINE, VSCROLL_PLANE);
    while(1)
    {
		VDP_setHorizontalScrollLine(BG_A, 0, offsetMaskLine, 224, CPU);
		
		/*
		for(int i=0; i< 224; i++)
			offsetMaskLine[i] += random() % 10;
        */
		
		for(int i=0; i <= 224; i+=2) {
			offsetMaskLine[i] += 1;
			offsetMaskLine[i-1] -= 1;
		}
		
		VDP_waitVSync();
    }
    return (0);
}