#ifndef __YUI_LCD_H
#define __YUI_LCD_H


#include "main.h"

#define LcdPort P0

#define LCD_CLEAR          0X01        //lcd清屏
#define LCD_SHOW_MODE(x)   (0x02|(x))  //选择显示模式 0允许输入IRAM地址 1允许输入垂直卷动地址
#define LCD_SHOW_OFF       0X3E        //lcd显示关
#define LCD_SHOW_ON        0X3F        //lcd显示开
#define LCD_PAGE(x)        (0xb8|(x))  //设置页数
#define LCD_HANG(x)        (0xc0|(x))  //设置起始行
#define LCD_LIE(x)         (0x40|(x))  //设置起始列


void delay_us(u16);
void LCD_check_busy(void);     //检测LCD标志位
void LCD_write_cmd(u8);        //向LCD发送一个无参数命令
void LCD_write_show_data(u8);  //向lcd写一个一字节的数据
void LCD_setX(u8);             //初始化LCD页地址
void LCD_setY(u8);             //初始化LCD列地址
void LCD_init(void);
void LCD_init_YUI(void);
void LCD_draw_byte(u8 x, u8 y, u8 LcdShowData);
void LCD_write_screen(void);   //将二维数组写入LCD12864当中 LcdData_1为LcdData_1[8][128]
void LCD_draw_line(u8 x);
void LCD_draw_num(u8 x, u8 y, u8 num);
void LCD_draw_chinese(u8 x, u8 y, u8 chr_lib, u8 lo);
void LCD_clear_area_2x32(u8 x, u8 y);
void LCD_clear_area_2x64(u8 x, u8 y);
void LCD_draw_Settings_description(u8 x, u8 y, u8 __set_mode);


#endif
