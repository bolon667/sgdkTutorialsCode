#include <genesis.h>

int main()
{
    VDP_drawText("Hello World", 1,1);
    while(1)
    {
        SYS_doVBlankProcess();
    }
    return (0);
}