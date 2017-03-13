#include "timer.h"



void init_SystemClock(void){
    CLKCONCMD &=~(1<<6);//set SystemClock Source to 32MHZ
    while(CLKCONSTA&(1<<6)); //waiting for SystemClock to be stable
    CLKCONCMD&=~0x07;   //set SystemClock to 32MHZ

}