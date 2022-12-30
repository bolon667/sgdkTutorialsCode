#include <genesis.h>
#include "resources.h"

int main()
{
    VDP_drawImage(BG_A, &img, 0, 0);
    while(1)
    {
        VDP_waitVSync();
    }
    return (0);
}
