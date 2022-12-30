#include <genesis.h>
#include "resources.h"

#define ANIM_STAND          0
#define ANIM_WALK           2

Sprite* sonic_obj;
s16 x = 0;
s16 y = 180;

s16 max_x_spd = 3;
s16 cur_spd_x = 0;

u16 sonic_width = 48;

void updateAnim() {
	if(cur_spd_x == 0) {
		SPR_setAnim(sonic_obj, ANIM_STAND);
	} else {
		SPR_setAnim(sonic_obj, ANIM_WALK);
	}
	
	if (cur_spd_x > 0) SPR_setHFlip(sonic_obj, FALSE);
    else if (cur_spd_x < 0) SPR_setHFlip(sonic_obj, TRUE);
}

void handleInput(){
  u16 value = JOY_readJoypad(JOY_1);
  cur_spd_x = 0;

  if(value & BUTTON_LEFT) {
    cur_spd_x = -max_x_spd;
  } else if(value & BUTTON_RIGHT) {
    cur_spd_x = max_x_spd;
  }
}

int main()
{
    VDP_drawImage(BG_A, &img, 0, 0);
	SPR_init();
	PAL_setPalette(PAL3, sonic_sprite.palette->data, DMA);
	sonic_obj = SPR_addSprite(&sonic_sprite, x,  y, TILE_ATTR(PAL3, 0, FALSE, FALSE));
    while(1)
    {
		SPR_update();
        SYS_doVBlankProcess();
		
		handleInput();
		updateAnim();
		
		x += cur_spd_x;
		if(x > 320-sonic_width)
			x = 320-sonic_width;
		else if(x < 0)
			x = 0;
		SPR_setPosition(sonic_obj, x, y);
		
    }
    return (0);
}
