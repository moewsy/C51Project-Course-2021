#ifndef __YUI_MAIN_H
#define __YUI_MAIN_H

typedef unsigned char u8;
typedef unsigned int u16;
typedef unsigned long u32;


#define UART_RX_MAX_LEN 3


#define _nop_ do{}while(0)

#include <reg51.h>
//#include <intrins.h>

sbit LED_SW_L = P1^0;
sbit LED_SW_H = P1^1;
sbit LED_EN = P1^2;


sbit AD_CS = P1^3;
sbit AD_CLK = P1^4;
sbit AD_DIDO = P1^5;


sbit CHIP2_MODE = P3 ^ 7;


extern u8 global_Function_mode;


void delay_ms(u16 __time);

#endif /* __YUI_MAIN_H */
