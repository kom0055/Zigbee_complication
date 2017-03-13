#include <ioCC2530.h>

void Init_System(void)
{
  CLKCONCMD &= ~(0x40);//ѡ��ϵͳʱ��Դ32M
  while(CLKCONSTA&0x40);//�ȴ��ȶ�
  CLKCONCMD&=~0X07;//����ϵͳʱ��32M
}
void Init_Uart0(void)
{
  //��������
  PERCFG &=~0X01;
  P0SEL |=0x0c;//����I/O
  P2DIR &=~0xc0;//���ȼ�
  
  //���ڿ���������
  U0CSR|=0X80;//UART
  //U0UCRĬ��ֵ
  U0GCR = 11;
  U0BAUD = 216; //115200
  //ʹ�ܽ���
  //�ж�
  URX0IF = 0;//���жϱ�־
  URX0IE = 1;//ʹ���ж�
  EA = 1;
  //IEN0|=0X01;
  //ʹ�ܽ���
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