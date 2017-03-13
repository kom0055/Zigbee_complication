
#include "uart.h"

unsigned static char temp,string_temp[256];
unsigned static int i=0,flag=0,pr=0;

//send 1 char 
void Uart0_SendChar(unsigned char ch){
    U0DBUF=ch;
    while(UTX0IF==0);//wait for send progress end
    UTX0IF=0;
}

//send string 
void UART0_SendString(unsigned char* buf){
  while(*buf!='\0'){
    Uart0_SendChar(*buf);
    buf++;
  }
  return ;
}

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
    UTX0IF=0;
    
    //ENABLE INTERRUPT
    URX0IE=1;//IEN0 |=(1<<2) 
    EA=1;

    U0CSR|=(1<<6);//receIve enable
    
    //string_temp="pengkun's ioCC starts.";
    
    
   
    
}

void exe_command(unsigned char* p){
  
  //Uart0_SendChar(*p);
  if(*p++=='L')
    
    if(*p++=='E')
      if(*p=='D')
        P1_0=~P1_0;
 // Uart0_SendChar(*p);
  Uart0_SendChar('0'+P1_0);
}

#pragma vector=URX0_VECTOR
__interrupt void Uart0Rx_ISR(void){
  temp=U0DBUF;
  
  if(strlen(string_temp)>=50){
    
    UART0_SendString("error!! the size of string is more than ");
    Uart0_SendChar(strlen(string_temp));
    UART0_SendString("byte!!!\n");
                     
    
  }
  else{
    //char a=('0'+sizeof(string_temp));
  switch(temp){
    case '\r':
    case '\n':
      //Uart0_SendChar('q');
      Uart0_SendChar('\r');
      Uart0_SendChar('\n');
      exe_command(string_temp);
      //char a=('0'+strlen(string_temp));
     // Uart0_SendChar(a);
      //Uart0_SendChar('p');
     // UART0_SendString(string_temp);
      pr=0;

      break;
    
  case '\b':
      if(pr==0) break;
      
      string_temp[pr]='\0';
      Uart0_SendChar('\b');
      Uart0_SendChar(' ');
      Uart0_SendChar('\b');
      break;
  case '#':
    pr=0;
    break;
  default:
   Uart0_SendChar(temp);
   string_temp[pr]=temp;
   pr++;
    break;
      
  }
  
  }
   
  
  URX0IF=0;
  
}