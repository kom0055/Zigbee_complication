#include <ioCC2530.h>
//Init LED
void init_Led(void){
//
  P1SEL&=~(1<<0);//general IO
 
    P1DIR |=(1<<0);// out
      P1|=(1<<0) ;//led put out
        
}

//Init Key
void init_Key(void){
//
  P0SEL&=~(1<<1);
  P0DIR |=~(1<<1);
  
  //CLEAR INTERRUPT STATE FLAG
  P0IFG &=0;//io
//  IRCON&=~(1<<5);cpu
  P0IF &=0;
  
  
  //IO interrupt setting
  PICTL|=(1<<0);// FALLING EDGE GIVES INTERRUPT
  P0IEN |=(1<<1);//INTERRUPT ENABLE P0.1
  
  
  //INTERRUPT CONTROLER ENBALE
  IEN1 |=(1<<5);//ENABLE P0 INTERRUPT
  EA = 1;//IEN0|=(1<<7); 
 
}
/**
interrupt service program
**/

void delay_16ms(void){
 int iCounter=0;
  while(1){
    if((T1STAT&(1<<5))!=0){
      T1STAT&=~(1<<5);
      iCounter++;
      
      
    }
    if(iCounter==4) return;
  }
  
  

}

void DelayMs(unsigned int msec){
  int i,j;
  for(i=0;i<msec;i++)
    for(j=0;j<535;j++);
}

#pragma vector = P0INT_VECTOR //6BH
__interrupt void P0_ISR(void){
  delay_16ms();
  //DelayMs(15);
  if(P0_1==1){
 
  //P1&=~(1<<0);//LIGHTING
  P1_0 = ~P1_0;// make led light or put out,but need timer to make delay
  //CLEAR INTERRUPT STATE FLAG
  P0IFG=0;
  P0IF=0;
  }
}
/**
fosc=16MHZ
TICKSP=16MHZ
15ms:
  16MHZ also 0.0625¦Ìs=62.5ns per period,
 and it has 16 bits,so the max period is 65536*62.5ns=65536/16M=1/256s=4ms
look for the CC2530-data-sheet,we found that there's no proper divider value 
we need,what we need is 4.So to get the same effect,we just need 4 period.
**/

void init_Timer1(void){
  T1CTL|=(0<<2)|(1<<0);
}

void main(void){
  
  init_Led();
  init_Key();
  init_Timer1();
  while(1){
  
  }
}