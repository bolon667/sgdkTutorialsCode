#include <genesis.h>
#include "resources.h"


u16 cur_line = 0; //текущая линия
f16 v_offset = 0; //смещение плейна
f16 v_scroll_step = FIX16(3); //шаг увеличения смещения v_offset

HINTERRUPT_CALLBACK HIntHandler()
{
    VDP_setVerticalScroll(BG_A, cur_line+fix16ToInt(v_offset));
    v_scroll_step += FIX16(0.02); //Меняем шаг, тем самым, скорость движения плейна - увеличивается
    v_offset -= v_scroll_step;
   
}

void VIntHandler()
{
    cur_line += 1; //двигаем текущую линию, каждый кадр
    v_scroll_step = FIX16(3.0); //Сбрасывам шаг, с которым двигается плейн.
    v_offset = 0; 
 }

int main()
{
	VDP_drawImage(BG_A, &img, 0, 0);

    VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);
    PAL_setColors(0, img.palette->data, 16, CPU);


    SYS_disableInts();
    {
        VDP_setHIntCounter(0);
        VDP_setHInterrupt(1);
        SYS_setHIntCallback(HIntHandler);
        SYS_setVIntCallback(VIntHandler);
    }
    SYS_enableInts();
    
    while (TRUE)
    {
        SYS_doVBlankProcess();
    }
}