#ifndef __YUI_MAX5822_H
#define __YUI_MAX5822_H

#include <main.h>

void Delay_ms_max5822(u16 t);
void Start1(void);
void Stop1(void);
bit CxxACK(void);
void SendChar(u8 dat);
void WriteByte_max5822(u8 ab, u8 xuan, u16 vol);

#endif
