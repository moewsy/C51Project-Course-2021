#include <UART.h>

void uart_init(void)
{
    TMOD |= 0x20;  // 定时器1工作于8位自动重载模式, 用于产生波特率
    TH1 = 0xfd;
    TL1 = TH1;     // 定时器0赋初值
    SCON = 0x50;
    //PCON |= 0x80;
    TR1 = 1;
    //IE = 0x00;   // 禁止任何中断
}

void uart_tx_byte(u8 byte)
{
    SBUF = byte;
    while(TI == 0);
    TI = 0;
}

void uart_tx_string(u8 p[])
{
    u8 i;

    for (i=0;i<UART_TX_MAX_LEN;i++) {
        uart_tx_byte(p[i]);
        delay_ms(10);
    }
}