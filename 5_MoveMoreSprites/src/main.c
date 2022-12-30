#include <genesis.h>
#include "resources.h"

#define CUP_COUNT 10

typedef struct
{
	Sprite *sprite;
	s16 posX;
	s16 posY;
	s16 x_spd;
	s16 y_spd;
	u16 cup_width;
	u16 cup_height;
} Cup;

Cup cups[CUP_COUNT];

int main()
{
	s16 i;
    VDP_drawImage(BG_A, &img, 0, 0);
	SPR_init();
	PAL_setPalette(PAL3, spr_cup.palette->data, DMA);
	
	for(i = 0; i<CUP_COUNT; i++) {
		
		s16 randSpdX = (random() % 5)+1;
		s16 randSpdY = (random() % 5)+1;
		Cup oneCup = {NULL, 0, 0, randSpdX, randSpdY, 64, 64};
		Sprite* spr = SPR_addSprite(&spr_cup, oneCup.posX,  oneCup.posY, TILE_ATTR(PAL3, 0, FALSE, FALSE));
		oneCup.sprite = spr;
		cups[i] = oneCup;
	}
    while(1)
    {
		SPR_update();
        SYS_doVBlankProcess();
		for(i = 0; i<CUP_COUNT; i++) {
			Cup oneCup = cups[i];
			oneCup.posX += oneCup.x_spd;
			oneCup.posY += oneCup.y_spd;
			
			if(oneCup.posX > 320-oneCup.cup_width || oneCup.posX < 0)
				oneCup.x_spd *= -1;
			if(oneCup.posY > 240-oneCup.cup_height || oneCup.posY < 0)
				oneCup.y_spd *= -1;
			SPR_setPosition(oneCup.sprite, oneCup.posX, oneCup.posY);
			cups[i] = oneCup;
		}
		
		
    }
    return (0);
}
