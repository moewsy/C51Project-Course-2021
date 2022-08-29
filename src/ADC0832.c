#include <ADC0832.h>

u8 Get_AD_Result(void)  //包含11个CLK下降沿      
{
    u8 i, dat;
    AD_CS = 1;  //ADC0832未工作时，CS端为高电平，此时芯片禁用
    _nop_;      //对于延时很短的，要求在us级的，采用“_nop_”函数      
    AD_CLK =1;                  
    AD_CS = 0;
    AD_DIDO = 1; AD_CLK = 0; _nop_; AD_CLK = 1; _nop_;  //SCLK第一个下降沿来到时，DI = 1启动ADC0832
    AD_DIDO = 1; AD_CLK = 0; _nop_; AD_CLK = 1; _nop_;  //SCLK第二个下降沿 
    AD_DIDO = 0; AD_CLK = 0; _nop_; AD_CLK = 1; _nop_;  //SCLK第三个下降沿，发送1,0选择通道cho
    AD_DIDO = 1;                                        //释放总线
    for(i = 0; i < 8; i++)        //第4个下降沿到第11个下降沿
    {
        AD_CLK = 0;               //clk处于下降沿，每一个下降沿DO端输入下一个
        _nop_;                    //对于延时很短的，要求在us级的，采用_nop_函数      
        if(AD_DIDO) dat |= 0x01;  // dat = dat | 0x01,dat和0x01做“或”的运算，意思是最低位置1，其它位保持不变。
        AD_CLK = 1; _nop_;        //clk处于上升沿
        dat <<= 1;                //数据左移
    }
    AD_CS = 1;                    //ADC0832停止工作
    return (dat);
}
