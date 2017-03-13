/**
once press,lights gradually like  breathing,press 5 times to be the brightest 
press one more time,puts out or fades away gradually like breathing
**/

#include <ioCC2530.h>
void init_Led(void){
//
  P1SEL&=~(1<<0);//general IO
 
    P1DIR |=(1<<0);// out
      P1|=(1<<0) ;//led put out
        
}
/**
fosc=16MHZ
TICKSP=16MHZ
1s:
  16MHZ/128=128KHZ also 8¦Ìs per period
 and it has 16 bits,so the max period is 65536*8¦Ìs=65536/128K=1/2=0.5s
so 1s takes 2 period
**/
void init_Timer1(void){
  T1CTL |=(3<<2)|(1<<0);//ONLY NEED TO SET t1ctl,DIVIDED IN 128 AND FREE-RUNNING
}
//led 1 flashes once

void main(void){
  int iCounter =0;//counts 
  init_Led();
  init_Timer1();
  while(1){
    if((T1STAT &(1<<5))!=0){//judge whether overflow exitst by T1STAT 
      //remember that  '&'operation  is lower than '!=' operation 
      T1STAT &=~(1<<5); 
      
      iCounter++;
      iCounter %=2;
      if(iCounter==0){
        P1_0=~P1_0;
      }
      
    }
  }
}