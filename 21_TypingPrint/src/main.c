#include <genesis.h>
#include "resources.h"


u16 VDPTilesFilled = 16;

void printMessageBase(char* str, Image* img_msg_sign, u8 msg_sign_pal) {
	
	VDP_setWindowVPos(FALSE, 10);
	VDP_drawImageEx(WINDOW, img_msg_sign, TILE_ATTR_FULL(msg_sign_pal, 255, FALSE, FALSE, VDPTilesFilled), 0, 0, FALSE, FALSE);
	
	u32 str_len = strlen(str);
	char str_char[1];

	
	char str_line[35];
	u8 start_pos_x = 10;
	u8 start_pos_y = 2;
	
	bool skip = FALSE;
	
	u8 cur_y = 0;
	u8 max_y = 6;
	u8 cur_x = 0;
	u8 max_x = 27;
	u8 max_x_line = max_x;
	
	u8 joy_value = 0;
	joy_value = JOY_readJoypad(JOY_1);
	SYS_doVBlankProcess();
	
	bool can_skip = TRUE;
	bool prev_joy_pressed = FALSE;
	bool joy_pressed = FALSE;

	if (joy_value & BUTTON_A || joy_value & BUTTON_B || joy_value & BUTTON_C || joy_value & BUTTON_START) {
		can_skip = FALSE;
	}
	
	strncpy(&str_line, 0, max_x);
	
	for(u32 i=0;i<str_len;i++) {
		strncpy(&str_char, str+i, 1);
		
		
		joy_value = JOY_readJoypad(JOY_1);
		if (joy_value & BUTTON_A || joy_value & BUTTON_B || joy_value & BUTTON_C || joy_value & BUTTON_START)  {
			joy_pressed = TRUE;
			if(joy_pressed && !prev_joy_pressed && can_skip) {
				skip = TRUE;
			} else {
				joy_pressed = FALSE;
			}
		} else {
			can_skip = TRUE;
		}

		if(i != 0 && (cur_x > max_x_line)) {
			cur_x = 0;
			cur_y += 2;
			
			if(cur_y >= max_y) { //if text doesn't fit in the rectangle, then
				while(1) {
					joy_value = JOY_readJoypad(JOY_1);
					SYS_doVBlankProcess();
					//waiting for just_pressed action from player
					if (joy_value & BUTTON_A || joy_value & BUTTON_B || joy_value & BUTTON_C || joy_value & BUTTON_START) 
					{
						
						joy_pressed = TRUE;
						if(joy_pressed && !prev_joy_pressed) {
							cur_x = 0;
							cur_y = 0;
							skip = FALSE;
							can_skip = FALSE;
							VDP_drawImageEx(WINDOW, &img_message_sign, TILE_ATTR_FULL(msg_sign_pal, 255, FALSE, FALSE, VDPTilesFilled), 0, 0, FALSE, FALSE);
							break;
						}
					} else {
						joy_pressed = FALSE;
					}
					prev_joy_pressed = joy_pressed;
				}
			}
		}
		VDP_drawTextBG(WINDOW, str_char, start_pos_x+cur_x, start_pos_y+cur_y);
		if(cur_x == 0) {
			strncpy(&str_line, str+i, max_x);
			u8 str_line_len = strlen(str_line);
			//if((str_line_len < max_x-1) && FALSE) {
			if(str_line_len < max_x) {
				max_x_line = max_x;
			}
			else {
				for(u8 j=0; j<max_x; j++)
				{
					////KLog_U1_U1("dasdsa1: ", *str_char_line);
					////KLog_U1_U1("dasdsa2: ", ' ');
					if(str_line[j] == ' '){
						//max_x_line = j+1;
						max_x_line = j;
						//break;
					}	
				}
			}
			
			strncpy(&str_line, str+i, max_x_line);
			KDebug_Alert(str_line);
			// //KLog_U1_U1("max_x_line: ", max_x_line);
			// //KLog_U1_U1("str_line_len: ", str_line_len);
			// //KLog_U1_U1("i: ", i);
		}
		
		

		//if skip, then disabling text appear animation
		if (!skip) {	
			waitMs(20);
			SYS_doVBlankProcess();
		}
		prev_joy_pressed = joy_pressed;
		cur_x++;
		
	}
	prev_joy_pressed = TRUE;
	skip = FALSE;
	//waiting for last press
	while(1) {
		joy_value = JOY_readJoypad(JOY_1);
		if (joy_value & BUTTON_A || joy_value & BUTTON_B || joy_value & BUTTON_C || joy_value & BUTTON_START)  {
			joy_pressed = TRUE;
			if(joy_pressed && !prev_joy_pressed) {
				break;
			}
		} else {
			joy_pressed = FALSE;
		}
		prev_joy_pressed = joy_pressed;
		SYS_doVBlankProcess();	
	}
    
	VDP_setWindowVPos(FALSE, 0);
}

int main()
{
    PAL_setPalette(PAL0, img_message_sign.palette->data, CPU);
    printMessageBase("Please wait, i'm typing....", &img_message_sign, PAL0);
    while(1)
    {
        SYS_doVBlankProcess();
    }
    return (0);
}
