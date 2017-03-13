#include  <ioCC2530.h>
#define Key P0_1

void DelayMs(unsigned int msec){
  int i,j;
  for(i=0;i<msec;i++)
    for(j=0;j<535;j++);
}

void key_flag(void){
  if(!Key){
   DelayMs(10);
    if(!Key) {
      P1&=~0X13;
      DelayMs(1000);
      P1|=0xff;
      DelayMs(1000);
      P1&=~0X13;
      DelayMs(1000);
      P1&=0xff ;
    }
  }
}

void LedInit(void){
  P1SEL&=(~(1<<0))&(~(1<<4))&(~(1<<1));
  P1DIR|=(1<<0)|(1<<4)|(1<<1);
  P1&=0XFF;
}

void Led_Run(void){
  int i;
  for(i=0;i<3;i++){
    key_flag();
    if(i==2) P1=(~(1<<4));
    else P1=~(1<<i);
    DelayMs(1000);
  }

}

void main(void){
  LedInit();
  while(1){
    //DelayMs(1000);
    //P1=~0X02;
    //DelayMs(1000);
    //P1=0xff;
   Led_Run();;
  //P1=~0X10;
    
  }
}