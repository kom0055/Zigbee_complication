#ifndef _uart_H
#define _uart_H
#include <ioCC2530.h>

void init_Uart0(void);
void Uart0_SendChar(unsigned char ch);
void UART0_SendString(unsigned char* buf);
#endif