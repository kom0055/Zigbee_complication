
#include "led.h"

void init_Led(void){
P1SEL&=~(1<<0);
P1DIR|=(1<<0);
P1&=~(1<<0);
}