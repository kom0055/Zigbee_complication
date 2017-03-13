#include <ioCC2530.h>

void init_Uart0(void){
    //UART PIN setting
    PERCFG &=~(1<<0);//ALT 1
    P0SEL |=((1<<2)|(1<<3));//P0.2,P0.3 peripheral 
    P2DIR &=~((1<<7)|(1<<6));//UART0 HAS 1ST priority



    //uart0 controllor setting
    U0CSR|=(1<<7);//uart mode
    //U0UCR uses default

    U0GCR=11;
    U0BAUD=216;//baud rate =115200 when System Clock is 32MHZ
    
    //CLEAR INTERRUPT FLAG
    URX0IF=0;
    
    //ENABLE INTERRUPT
    URX0IE=1;//IEN0 |=(1<<2) 
    EA=1;

    U0CSR|=(1<<6);//receIve enable
}


void init_SystemClock(void){
    CLKCONCMD &=~(1<<6);//set SystemClock Source to 32MHZ
    while(CLKCONSTA&(1<<6)); //waiting for SystemClock to be stable
    CLKCONCMD&=~0x07;   //set SystemClock to 32MHZ

}

//send 1 char 
void Uart0_SendChar(unsigned char ch){
    U0DBUF=ch;
    while(UTX0IF==0);//wait for send progress end
    UTX0IF=0;
}

#pragma vector=URX0_VECTOR
__interrupt void Uart0Rx_ISR(void){
  Uart0_SendChar(U0DBUF);
  URX0IF=0;
}


//send string 
void UART0_SendString(unsigned char* buf,unsigned int len){
    int i=0;
    for(;i<len;i++){
        Uart0_SendChar(*buf++);
    }
}

void main(void){
    init_SystemClock();
    init_Uart0();
    UART0_SendString("pengkun",8);
    while(1){


    }
}