
/*
P1:���ݿ�
P1SEL:ͨ��IO
P1DIR:�����������
*/

/*
__sfr:���߱��������������⹦�ܼĴ�����
__no_init:���߱����������ڷǳ�ʼ�Ĵ�����
*/

/*
ջ��
����
bss��
��̬������
�����
*/
__sfr __no_init volatile unsigned char P1 @ 0x90;
__sfr __no_init volatile unsigned char P1SEL @ 0xF4;
__sfr __no_init volatile unsigned char P1DIR @ 0xFE;
//��-��-д

//#define SFR(name,addr) __sfr __no_init volatile unsigned char name @ addr;
//SFR(P1,0X90)
//SFR(P1SEL,0XF4)
//SFR(P1DIR,0XFE)
//#define SETB(name,bit) name |=(1<<bit)
//#define CLRB(name,bit) name &= (~(1<<bit))

//#define p1 (*const )0x90;

typedef unsigned int uint;
//typedef unsigned char uchar;

void InitLed(void){
  
  //P1SEL=P1SEL&0xee;
  //����Ϊͨ��io
 
  P1SEL &= ~0x10;
  //P1DIR=P1DIR|0x11;
  //����Ϊ���
  P1DIR |= 0x10;
}
/*
���ܣ���ʱ����
������smec����ʱʱ��(ms)
����ֵ����
*/
void DelayMs(uint msec){
  int i,j;
  for(i=0;i<msec;i++)
    for(j=0;j<535;j++);
}

void main(void){

  InitLed();
  //P1 = P1&0xee;
  while(1){
    DelayMs(1000);
    P1 &= ~0x10;
    //CLRB(P1,0);
    //CLRB(P1,4);
    DelayMs(1000);
    P1 |= 0xff;
    
  }
}
//ʵ����ˮ�� ���������ˮ�ƣ�����S1������˸���Σ�֮�������ˮ�ơ�