#include "genesis.h"

typedef struct {
	u16 value;
	u16 prevValue;
} joyInput;

joyInput joy1;
joyInput joy2;

void window1(){
  VDP_drawText("Window1",1,3);
  while(1){
    joy1.prevValue = joy1.value;
    joy1.value = JOY_readJoypad(JOY_1);
    
    if((joy1.value & BUTTON_START) && !(joy1.prevValue & BUTTON_START)) {
      break;
    }
    SYS_doVBlankProcess();
  }
}

void window2(){
  VDP_drawText("Window2",1,3);
  while(1){
    joy1.prevValue = joy1.value;
    joy1.value = JOY_readJoypad(JOY_1);
    
    if((joy1.value & BUTTON_START) && !(joy1.prevValue & BUTTON_START)) {
      break;
    }
    SYS_doVBlankProcess();
  }
}


int main()
{
    while(1)
    {
      window1();
      window2();  
    }
    return (0);
}
