#include <main.h>
#include <ADC0832.h>

u8 global_Function_mode = 0;


u8 numData[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f, 0x00, 0xff};
u8 showNum[] = {10,10,10,10};
u16 showNum_r = 0;
u8 pickLED = 0;

u8 UARTrx_Buffer[UART_RX_MAX_LEN] = {0};
u8 UARTrx_count = 0;
u8 UARTrx_Buffer_Ready = 0;

void delay_ms(u16 __time)
{
	u8 i;
	while (__time--) for (i=120;i;i--);
}

void ET0_init()   
{
    //TMOD &= 0x0f;			 
    //TMOD = 0x01;
    TH0 = 0xff & 32769 >> 4;
    TL0 = 0xff & 32769;
}

void UART_rx_Buffer_Handeler(void)
{
    if (!UARTrx_Buffer_Ready) return;

    global_Function_mode = 0xff == UARTrx_Buffer[0] ? 1 : 0;
    showNum_r = 0xffff & UARTrx_Buffer[1] << 8 | UARTrx_Buffer[2];

    UARTrx_Buffer_Ready = 0;
}

void ET0_INT() interrupt 1
{
    //u16 vt;
    u8 AD;
    //u8 i;
    //u16 temptime;
    u8 highnum_check = 0;

    TH0 = 0xff & 32769 >> 4;
    TL0 = 0xff & 32769;
    CHIP2_MODE = 1 & global_Function_mode;

    if (!global_Function_mode) {
        AD = Get_AD_Result();
        //vt = (500.0/256.0)*AD; //测量电压值
        showNum_r = (1000/254.5)*AD;
    }
    

    #if 1

        if ((showNum[0] = showNum_r / 1000 % 10) || highnum_check) {
            highnum_check = 1;
        } else {
            showNum[0] = 10;
        }

        if ((showNum[1] = showNum_r / 100 % 10) || highnum_check) {
            highnum_check = 1;
        } else {
            showNum[1] = 10;
        }

        if ((showNum[2] = showNum_r / 10 % 10) || highnum_check) {
            highnum_check = 1;
        } else {
            showNum[2] = 10;
        }

        showNum[3] = showNum_r % 10;

    #else
        showNum[0] = showNum_r / 1000 % 10;
        showNum[1] = showNum_r / 100 % 10;
        showNum[2] = showNum_r / 10 % 10;
        showNum[3] = showNum_r % 10;
    #endif

    UART_rx_Buffer_Handeler();
}

void UART_Init(void) {
    SCON = 0x50;
    TMOD |= 0x20;
    TH1 = 0xfd;
    TL1 = TH1;
    TR1 = 1;
    ES = 1;
}

void UART_tx_byte(u8 byte)
{
    SBUF = byte;
    while(TI == 0);
    TI = 0;
}

void UART_rx_IT_Handeler(void) interrupt 4
{   
    u8 ch;
    //ES = 0;
    //global_Function_mode = 1;
    if (RI) {
        
        ch = SBUF;
        //global_Function_mode = 1 - global_Function_mode;
        UARTrx_Buffer[UARTrx_count++] = ch;
        if (UARTrx_count == UART_RX_MAX_LEN) {
            UARTrx_count = 0;
            UARTrx_Buffer_Ready = 1;
        }
        //global_Function_mode = 1;
        /*
        switch (UARTrx_count) {
            default: {
                UART_tx_byte(ch);
            }
        }*/
    }
    RI = 0;
    //ES = 1;
}

void main(void) {

    ET0_init();    //定时器 0 初始化
    UART_Init();
    //RT1_init();    //定时器 1 初始化
    ET0 = 1;
    //ET1 = 1;
    EA = 1;     //打开总中断
    TR0 = 1;
    //TR1 = 1;
    AD_CLK = 0;      //ADC0832初始化
    AD_CS = 1;


    while (1) {
        pickLED == 3 ? pickLED = 0 : ++ pickLED;
        //P1 = 0xfc & P1 | pickLED;
        LED_EN = 0;
        LED_SW_L = pickLED & 1;
        LED_SW_H = pickLED & 2;
        P0 = numData[showNum[pickLED]];
        LED_EN = 1;
        delay_ms(10);
    }
}
