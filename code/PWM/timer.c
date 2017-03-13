#include "timer.h"

#define NOP()asm("NOP")

#define TIME_A OW_HW_WaitUs(3);//6uS
#define TIME_B OW_HW_WaitUs(47);//64uS
#define TIME_C OW_HW_WaitUs(44);//60uS
#define TIME_D OW_HW_WaitUs(6);//10uS
#define TIME_E OW_HW_WaitUs(5);//9uS
#define TIME_F OW_HW_WaitUs(40);//55uS
#define TIME_G {;}//0uS
#define TIME_H OW_HW_WaitUs(364);//480uS
#define TIME_I OW_HW_WaitUs(52);//70uS
#define TIME_J OW_HW_WaitUs(310);//410uS



void init_Timer(void){

CLKCONCMD&=~0X40;
while(CLKCONSTA&0X40);
CLKCONCMD&=~0X07;
CLKCONCMD|=0X38;

  //T1CTL|=(3<<2)|(3<<0);
   
    P1SEL|=0X01;
     PERCFG|=0X40;
    P2SEL&=~0X10;
    P2DIR|=0XC0;
    P1DIR|=0X01;

    T1CTL=0X02;
    T1CCTL2=0X1C;
    T1CC0H=0X00;
    T1CC0L=0XFA;
    T1CC2H=0X00;
    T1CC2L=0X00;
    
    T3CTL |=(1<<0);
}

void DelayMs(unsigned int msec){
   while(msec--)
    {
        NOP();
        NOP();
        NOP();
    }
}
