#include <genesis.h>
#include "resources.h"

int main()
{
	
	u16 palette_full[64]; //Создали массив в котором будем хранить палитру
	memcpy(&palette_full[0],  img.palette->data, 16 * 2); //Скопировали палитру в массив palette_full хранящий все 4 палитры.
	PAL_setColors(0, palette_black, 64, DMA); //Заменили все цвета в палитре на черный.
	
    VDP_drawImage(BG_A, &img, 0, 0); //Нарисовали изображение
	
	PAL_fadeIn(0, 63, palette_full, 100, FALSE); //Проиграли fade-in(осветление) переход, переход занимает 100 кадров.
	waitMs(3000); //Ждем 3 секунды
	PAL_fadeOut(0, 63, 100, FALSE); // Проигрываем fade-out(затемнение) переход, переход занимает 100 кадров.
	
    while(1)
    {
        VDP_waitVSync();
    }
    return (0);
}
