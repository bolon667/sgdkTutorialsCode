#include <genesis.h>
#include "resources.h"

Sprite* cup_obj;
s16 x = 0;
s16 y = 0;

s16 x_spd = 3;
s16 y_spd = 3;
u16 cup_width = 64;
u16 cup_height = 64;

int main()
{
    VDP_drawImage(BG_A, &img, 0, 0);
    SPR_init();
	PAL_setPalette(PAL3, spr_cup.palette->data, DMA);
    cup_obj = SPR_addSprite(&spr_cup, x,  y, TILE_ATTR(PAL3, 0, FALSE, FALSE));
    while(1)
    {
		x += x_spd;
		y += y_spd;
		if(x > 320-cup_width || x < 0)
		x_spd *= -1;
		if(y > 240-cup_height || y < 0)
		y_spd *= -1;
		SPR_setPosition(cup_obj, x, y);
		SPR_update();
        SYS_doVBlankProcess();
    }
    return (0);
}