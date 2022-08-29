#ifndef __YUI_KEYBOARD_H
#define __YUI_KEYBOARD_H

#include "main.h"

#define maxLen 3
#define TimeInt 32767

extern u8 nowInputLo;
extern u8 lockKey;
extern u8 passLED;
extern u8 rowKey;
extern u8 columnKey;
extern u8 showNum[4];
extern bit PV;

extern u8 screenPointX;
extern u8 screenPointY;

extern u8 UART_Direct_CMD[UART_TX_MAX_LEN];


void changeLock(void);
void inputNum(int __num);
void clearNum(void);
void moveLeft(void);
void moveRight(void);
void button1(void);
void button2(void);
u8 checkLo(u8 __data);
void setDAC(void);
void global_Switch_mode(void);
void sendUART(void);

extern void (*keyCode[4][4])(void);


#endif
