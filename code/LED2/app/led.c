#include <ioCC2530.h>
#define uint  unsigned int  
#define uchar unsigned char
//������ƵƵĶ˿�
#define RLED P1_0    //����LED1ΪP1.0�ڿ���
#define GLED P1_1    //����LED2ΪP1.1�ڿ���
#define YLED P1_4    //����LED3ΪP1.4�ڿ���
#define BLED P0_1       //����LED4ΪP0.1�ڿ���
//��������
void Delay(uint);        //��ʱ����
void InitIO(void);        //��ʼ��LED����IO�ں���

void Delay(uint n)   //��ʱ����
{
    uint i;                 //����һ������i��     
    for(i = 0;i<n;i++);
        for(i = 0;i<n;i++);
        for(i = 0;i<n;i++);
        for(i = 0;i<n;i++);
        for(i = 0;i<n;i++);
}

void InitIO(void) //��ʼ��IO�ڳ���
{
    P1DIR |= 0x13;  //P1_0��P1_1��P1_4����Ϊ���
    P0DIR |= 0x02;  //P0_1����Ϊ���
    RLED = 1;
    GLED = 1;
    YLED = 1;       
    BLED = 1;       //��4յLED�ƶ���
}


void main(void)
{
    InitIO();        //��ʼ��   
    while(1)       //��ѭ����ѭ���ڵĴ��벻��ִ��        
    {  
           RLED = !RLED;           // LED1�������ţ���ر�LED1�ƣ������LED1��
           Delay(10000);             //��ʱ
           GLED = !GLED;           
           Delay(10000);            
           YLED = !YLED;           
           Delay(10000);
           BLED = !BLED;
           Delay(10000);
           
    }
}