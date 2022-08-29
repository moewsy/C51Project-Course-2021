#ifndef __YUI_MAIN_H
#define __YUI_MAIN_H

//typedef bool sbit;

/* BEGIN： LCD 宏开关 */

#define __DRAW_NUM

    #define __NUM_16

        #define __LIB_PRO
    
#define __DRAW_CHINESE

    //#define __OLD_CHINESE_LIB

/*  END： LCD 宏开关  */


typedef unsigned char u8;
typedef unsigned int u16;
typedef unsigned long u32;


#define UART_TX_MAX_LEN 3


#include <reg51.h>


/* BEGIN： Chip 1 引脚定义 */

sbit CHIP1_LED_LO_L = P1 ^ 6;
sbit CHIP1_LED_LO_H = P1 ^ 7;

sbit LCD_RST = P1 ^ 0;
sbit LCD_E = P1 ^ 1;
sbit LCD_RW = P1 ^ 2;
sbit LCD_RS = P1 ^ 3;
sbit LCD_CS1 = P1 ^ 4;
sbit LCD_CS2 = P1 ^ 5;

sbit CHIP1_MODE = P3 ^ 5;

sbit DA_SCL = P3 ^ 6;
sbit DA_SDA = P3 ^ 7;

/*  END： Chip 1 引脚定义  */


extern u8 global_Function_mode;
extern u8 UART_DAAD_CMD[UART_TX_MAX_LEN];

void delay_ms(u16 __time);

#endif /* __YUI_MAIN_H */
