#include <ioCC2530.h>

#include "timer.h"
#include "led.h"
#include "uart.h"


extern unsigned char temp,string_temp[256];




void main(void){
   init_Led();
  
     
      init_Uart0();
      init_SystemClock();
    UART0_SendString("pengkun's ioCC2530 starts");
    while(1){
     // if(RXTXflag);

    }
}