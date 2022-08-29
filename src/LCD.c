#include <LCD.h>
#include <char_lib.h>

//void _nop_(void) {}

void delay_us(u16 __time)
{
	while (__time--);
}

#ifdef __CHECK_BUSY

/*
void LCD_check_busy(void)
{
	LcdPort = 0xff;
	LED0 = 1;
	LCD_RW = 1;
	LCD_RS = 0;
	LCD_E = 1;
	while (LcdPort & 0x80);
	LCD_E = 0;
	LED0 = 0;
}
*/

void LCD_check_busy(void)
{
	delay_us(1);
}
#endif

void LCD_write_cmd(u8 cmd)
{
    #ifdef __CHECK_BUSY
	    LCD_check_busy();
    #endif
	LCD_RS = 0;
	LCD_RW = 0;
	LCD_E = 1;
	LcdPort = cmd;
	//delay_us(1);
	LCD_E = 0;
}

void LCD_write_show_data(u8 showData)
{
	#ifdef __CHECK_BUSY
	    LCD_check_busy();
    #endif
	LCD_RS = 1;
	LCD_RW = 0;
	LCD_E = 1;
	LcdPort = showData;
	//delay_us(1);
	LCD_E = 0;
}

void LCD_setX(u8 x)
{
	//LCD_write_cmd(0xb8|x); // Page
	LCD_write_cmd(LCD_PAGE(x));
	LCD_write_cmd(LCD_HANG(x*8));
}

void LCD_setY(u8 y)
{
	//LCD_write_cmd(0x40|y);
	if (y >= 64)
	{
		LCD_CS1 = 1;
		LCD_CS2 = 0;
		y -= 64;
	}
	else
	{
		LCD_CS1 = 0;
		LCD_CS2 = 1;
	}
	LCD_write_cmd(LCD_LIE(y));
}

#ifdef __UNCALLED_FUNC
void LCD_init(void)
{
	LCD_CS1 = 0;
	LCD_CS2 = 0;
	LCD_write_cmd(LCD_SHOW_OFF);
	LCD_write_cmd(LCD_PAGE(0));
	LCD_write_cmd(LCD_HANG(0));
	LCD_write_cmd(LCD_LIE(0));
	LCD_write_cmd(LCD_SHOW_ON);
}
#endif

void LCD_init_YUI(void)
{
	LCD_write_cmd(0x30);
	delay_us(4);
	LCD_write_cmd(0x0c);
	delay_us(10);
	LCD_write_cmd(LCD_CLEAR);
	delay_us(1000);
	LCD_write_cmd(0x06);
	delay_us(10);
	LCD_write_cmd(LCD_SHOW_ON);
}

void LCD_draw_byte(u8 x, u8 y, u8 LcdShowData)
{
	LCD_setX(x);
	//delay_us(1);
	LCD_setY(y);
	LCD_write_show_data(LcdShowData);
}

#ifdef __UNCALLED_FUNC
void LCD_write_screen(void)
{
	u8 i,j;
	for(i=0;i<8;i++)
	{
		for(j=0;j<128;j++)
		{
			LCD_draw_byte(i, j, 0x00);
			//delay_us(35535);
			//LCD_draw_byte(i, j, 0xff);
		}
	}
}
#endif

#ifdef __UNCALLED_FUNC
void LCD_draw_line(u8 x)
{
	u8 j;
	//LCD_setX(x);
	for (j=0;j<128;j++)
	{
		if (j == 0 || j == 64)
		{
			LCD_setY(j);
		}
		//LCD_setX(x);
		//LCD_write_show_data(0x00);
		LCD_draw_byte(x, j, 0x00);
	}
}
#endif

#ifdef __DRAW_NUM

#ifdef __NUM_16

void LCD_draw_num(u8 x, u8 y, u8 num)
{
	u8 i, j;
	for (i=0;i<2;i++)
	{
		for (j=0;j<8;j++)
		{
			LCD_draw_byte(x+i, y+j, Num_lib[num][i*8+j]);
		}
	}
}

#else /* __NUM_16 */

void LCD_draw_num(u8 x, u8 y, u8 num)
{
	u8 j;
	for (j=0;j<8;j++)
	{
		LCD_draw_byte(x, y+j, Num_lib[num][j]);
	}
}

#endif /* __NUM_16 */

#endif /* __DRAW_NUM */



#ifdef __DRAW_CHINESE

#ifdef __OLD_CHINESE_LIB

void LCD_draw_chinese(u8 x, u8 y, u8 chr_lib, u8 lo)
{
	// Hidden by yui
}

#else /* __OLD_CHINESE_LIB */

void LCD_draw_Settings_description(u8 x, u8 y, u8 __set_mode)
{
	u8 i, j, lo, offset;
	offset = __set_mode ? 4 : 0;
	for (lo=0;lo<4;lo++) {
		for (i=0;i<2;i++) {
			for (j=0;j<16;j++) {
				LCD_draw_byte(x + i, y + j + 16*lo, Settings_description[lo + offset][i*16 + j]);
			}
		}
	}
	
}

#endif /* __OLD_CHINESE_LIB */

void LCD_clear_area_2x32(u8 x, u8 y)
{
	u8 i, j;
	for (i=0;i<2;i++)
	{
		for (j=0;j<32;j++)
		{
			LCD_draw_byte(x+i, y+j, 0xff);
		}
	}
}

void LCD_clear_area_2x64(u8 x, u8 y)
{
	u8 i, j;
	for (i=0;i<2;i++)
	{
		for (j=0;j<64;j++)
		{
			LCD_draw_byte(x+i, y+j, 0xff);
		}
	}
}


#endif /* __DRAW_CHINESE */
