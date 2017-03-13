
/*
P1:数据口
P1SEL:通用IO
P1DIR:输入输出方向
*/

/*
__sfr:告诉编译器保存在特殊功能寄存器里
__no_init:告诉编译器保存在非初始寄存器里
*/

/*
栈区
堆区
bss段
静态数据区
代码段
*/
__sfr __no_init volatile unsigned char P1 @ 0x90;
__sfr __no_init volatile unsigned char P1SEL @ 0xF4;
__sfr __no_init volatile unsigned char P1DIR @ 0xFE;
//读-改-写

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
  //设置为通用io
 
  P1SEL &= ~0x10;
  //P1DIR=P1DIR|0x11;
  //设置为输出
  P1DIR |= 0x10;
}
/*
功能：延时程序
参数：smec：延时时间(ms)
返回值：无
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
//实现流水灯 正常情况流水灯，按下S1所有闪烁两次，之后继续流水灯。