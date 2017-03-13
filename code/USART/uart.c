#include <ioCC2530.h>

void Init_System(void)
{
  CLKCONCMD &= ~(0x40);//选择系统时钟源32M
  while(CLKCONSTA&0x40);//等待稳定
  CLKCONCMD&=~0X07;//设置系统时钟32M
}
void Init_Uart0(void)
{
  //引脚配置
  PERCFG &=~0X01;
  P0SEL |=0x0c;//外设I/O
  P2DIR &=~0xc0;//优先级
  
  //串口控制器配置
  U0CSR|=0X80;//UART
  //U0UCR默认值
  U0GCR = 11;
  U0BAUD = 216; //115200
  //使能接收
  //中断
  URX0IF = 0;//清中断标志
  URX0IE = 1;//使能中断
  EA = 1;
  //IEN0|=0X01;
  //使能接收
  U0CSR |=0X40;
}
void Uart0_SendByte(unsigned char c)
{
  U0DBUF = c;
  while(UTX0IF == 0);
  UTX0IF = 0;
}

void Uart0_SendString(unsigned char* buf,unsigned int len)
{
   unsigned int i = 0;
   for(;i<len;i++)
   {
     Uart0_SendByte(*buf++);
   }
}
#pragma vector = URX0_VECTOR
__interrupt void Uart0RX_ISR(void)
{
  Uart0_SendByte(U0DBUF);
  URX0IF = 0;
}
void main(void)
{
  Init_System();
  Init_Uart0();
  Uart0_SendString("hello",6);
  while(1)
  {
  }
}