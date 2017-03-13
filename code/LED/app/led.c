#include <ioCC2530.h>

#define LED1 P1_1

void DelayMs(unsigned int msec){
  int i,j;
  for(i=0;i<msec;i++)
    for(j=0;j<535;j++);
}

void main(void){
  P1DIR |=0X2;
  while(1){
    LED1=0;
    DelayMs(1000);
    
    LED1=1;
    DelayMs(1000);
  }
}