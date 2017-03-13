#include "key.h"
static int flag=1,count=0;
static unsigned int pwm_rate[6]={0x00,0x32,0x64,0x96,0xC8,0xFA};
void init_Key(void){
  P0SEL&=~(1<<1);
  P0DIR|=~(1<<1);

  P0IFG &=0;
  P0IF&=0;
  PICTL|=(1<<0);
  P0IEN|=(1<<1);

  IEN1|=(1<<5);
  EA=1;
}


#pragma vector=P0INT_VECTOR
__interrupt void P0_ISR(void){
  DelayMs(15);
  //halMcuWaitMs(15);
  if(P0_1==0) return;
  DelayMs(15);
  if(flag)
  { T1CC2H=0X00;
  T1CC2L=pwm_rate[count++];}
  else {
     T1CC2H=0X00;
     T1CC2L=pwm_rate[count--];}
  
  if(count==6||count==0) flag=-flag;
  

 
  P0IFG=0;
  P0IF=0;
 
}

