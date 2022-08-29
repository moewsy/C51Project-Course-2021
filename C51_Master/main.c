#include <main.h>
#include <keyboard.h>
#include <MAX5822.h>
#include <LCD.h>
#include <UART.h>


u8 global_Function_mode = 0;

u8 UART_DAAD_CMD[UART_TX_MAX_LEN] = {0x00, 0x11, 0x22};

void delay_ms(u16 __time)
{
	u8 i;
	while (__time--) for (i=120;i;i--);
}


void time0_int(void) interrupt 1
{
	u8 a = 0;

    CHIP1_LED_LO_L = nowInputLo & 1;
    CHIP1_LED_LO_H = nowInputLo & 2;
    CHIP1_MODE = 1 & global_Function_mode;

    P2 = 0x0f;
    TH0 = 0xff & TimeInt >> 4;
    TL0 = 0xff & TimeInt;
	if (P2 ^ 0x0f) {
		delay_ms(2);
		if (PV && P2 ^ 0x0f) {
			rowKey = checkLo(P2);
		}
    } else {
        PV = 1;
        return;
    }
	
    P2 = 0xf0;
    if (P2 ^ 0xf0) {
		delay_ms(2);
		if (P2 ^ 0xf0) {
			columnKey = checkLo(P2);
		}
	}
	
	if (PV) {
		PV = 0;
		if (keyCode[rowKey][columnKey] < 10) inputNum(keyCode[rowKey][columnKey]);
		else (*keyCode[rowKey][columnKey])();
	}
	
	while (a < 5 && P2 != 0xf0) {
		delay_ms(1);
		a++;
	}
}

void main(void)
{
    TMOD = 0x01;
    TH0 = 0xff & TimeInt >> 4;
    TL0 = 0xff & TimeInt;
    TR0 = 1;
    EA = 1;
    ET0 = 1;


    P2 = 0x0f;
    uart_init();
    LCD_init_YUI();

    delay_ms(500);
    clearNum();

    LCD_draw_Settings_description(screenPointX - 2, screenPointY, global_Function_mode);
	LCD_draw_byte(0, 0, 0xff);
    LCD_draw_byte(0, 0, 0xff);

    while (1) {}
}
