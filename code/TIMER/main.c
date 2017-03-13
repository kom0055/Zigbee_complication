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

#pragma vector = P0INT_VECTOR //6BH
__interrupt void P0_ISR(void){
  //P1&=~(1<<0);//LIGHTING
  P1_0 = ~P1_0;// make led light or put out,but need timer to make delay
  //CLEAR INTERRUPT STATE FLAG
  P0IFG=0;
  P0IF=0;
}

void main(void){
  init_Led();
  init_Key();
  while(1){
  
  }
}