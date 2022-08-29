#include <keyboard.h>
#include <MAX5822.h>
#include <LCD.h>
#include <UART.h>


u8 nowInputLo = 0;

u8 lockKey = 0;
u8 passLED = 0x02;

u8 rowKey = 3;
u8 columnKey = 3;

u8 screenPointX = 4;
u8 screenPointY = 32;

u8 showNum[] = {10,10,10,10};
bit PV = 1;

u8 UART_Direct_CMD[UART_TX_MAX_LEN] = {0xff, 0x00, 0x00};


void inputNum(int __num)
{
	//if (lockKey) return ;
	showNum[nowInputLo] = __num;
	LCD_draw_num(screenPointX, screenPointY + 8 * nowInputLo, __num);
	LCD_draw_byte(0, 0, 0xff);
    LCD_draw_byte(0, 0, 0xff);
	moveRight();
}

void clearNum(void)
{
	u8 i;
	//if (lockKey) return ;
	for (i = 0; i <= maxLen; i++) showNum[i] = 10;
	nowInputLo = 0;
	passLED = 0x01;
	lockKey = 0;
	LCD_clear_area_2x32(screenPointX, screenPointY);
	//LCD_clear_area_2x64(screenPointX - 2, screenPointY);
	LCD_draw_Settings_description(screenPointX - 2, screenPointY, global_Function_mode);
	LCD_draw_byte(0, 0, 0xff);
    LCD_draw_byte(0, 0, 0xff);
}

void moveLeft(void)
{
	nowInputLo ? --nowInputLo : (nowInputLo = maxLen);
}

void moveRight(void)
{
	nowInputLo < maxLen ? ++nowInputLo : (nowInputLo = 0);
}

u8 checkLo(u8 __data)
{
	if (__data == 0x0e || __data == 0xe0) return 0;
	if (__data == 0x0d || __data == 0xd0) return 1;
	if (__data == 0x0b || __data == 0xb0) return 2;
	if (__data == 0x07 || __data == 0x70) return 3;
	return 0;
}

void sendUART(void)
{
	u8 i;
	u16 sendNum = 0;

	if (!global_Function_mode) return;

	if (nowInputLo == 0) {
		for (i=0;i<4;i++) {
			sendNum = sendNum * 10 + showNum[i];
		}
	} else {
		for (i=0;i<nowInputLo;i++) {
			sendNum = sendNum * 10 + showNum[i];
		}
	}
	UART_Direct_CMD[1] = 0xff & sendNum >> 8;
	UART_Direct_CMD[2] = 0xff & sendNum;
	uart_tx_string(UART_Direct_CMD);
}

void setDAC(void)
{
	u32 vol = 0;
	u8 i;

	if (global_Function_mode) return;

	if (nowInputLo == 0) {
		for (i=0;i<4;i++) {
			vol = vol * 10 + showNum[i];
		}
	} else {
		for (i=0;i<nowInputLo;i++) {
			vol = vol * 10 + showNum[i];
		}
	}


	vol = vol > 1000 ? 4095 : vol * 4095 / 1000;
	WriteByte_max5822(0x00, 0x04, 0x0fff & vol);
}

void global_Switch_mode(void) {
	global_Function_mode = 1 ^ global_Function_mode;
	if (global_Function_mode) {
		UART_Direct_CMD[1] = 0x00;
		UART_Direct_CMD[2] = 0x00;
		uart_tx_string(UART_Direct_CMD);
	} else {
		uart_tx_string(UART_DAAD_CMD);
	}
	clearNum();
}

void (*keyCode[4][4])(void) = {
	{7, 8, 9, clearNum},
	{4, 5, 6, sendUART},
	{1, 2, 3, setDAC},
	{moveLeft, 0, moveRight, global_Switch_mode}
};
