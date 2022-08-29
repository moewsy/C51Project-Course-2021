#include <MAX5822.h>

void Delay_ms_max5822(u16 t) {
   u16 i;
   while (t--) {
       for (i=0; i<1100; i++);
   } 
}

void Start1(void) {
    DA_SCL = 1;
    DA_SDA = 1;
    DA_SDA = 0;
    DA_SCL = 0;
}

void Stop1(void) {
    DA_SDA = 0;
    DA_SCL = 1;
    DA_SDA = 1;
}

bit CxxACK(void) {
    bit c;
    DA_SDA = 1;
    DA_SCL = 1;
    c = DA_SDA;
    DA_SCL = 0;
    return c;
}

void SendChar(u8 dat) {
    u8 i = 8;
    do {
        DA_SDA = (dat & 0x80);
        DA_SCL = 1;
        DA_SCL = 0;
        dat <<= 1;
    } while (--i!=0);
}

void WriteByte_max5822(u8 ab, u8 xuan, u16 vol) {
    u8 da_h = vol >> 8;
    u8 da_l = vol & 0xff;
    Start1();
    SendChar(0x70);
    CxxACK();
    SendChar(0xf0);
    CxxACK();
    SendChar(xuan);
    CxxACK();
    Stop1();
    Start1();
    SendChar(0x70);
    CxxACK();
    SendChar(ab|da_h);
    CxxACK();
    SendChar(da_l);
    CxxACK();
    Stop1();
    Delay_ms_max5822(1);
}
