#include <ioCC2530.h>
#define uint  unsigned int  
#define uchar unsigned char
//定义控制灯的端口
#define RLED P1_0    //定义LED1为P1.0口控制
#define GLED P1_1    //定义LED2为P1.1口控制
#define YLED P1_4    //定义LED3为P1.4口控制
#define BLED P0_1       //定义LED4为P0.1口控制
//函数声明
void Delay(uint);        //延时函数
void InitIO(void);        //初始化LED控制IO口函数

void Delay(uint n)   //延时函数
{
    uint i;                 //定义一个变量i；     
    for(i = 0;i<n;i++);
        for(i = 0;i<n;i++);
        for(i = 0;i<n;i++);
        for(i = 0;i<n;i++);
        for(i = 0;i<n;i++);
}

void InitIO(void) //初始化IO口程序
{
    P1DIR |= 0x13;  //P1_0、P1_1、P1_4定义为输出
    P0DIR |= 0x02;  //P0_1定义为输出
    RLED = 1;
    GLED = 1;
    YLED = 1;       
    BLED = 1;       //将4盏LED灯都打开
}


void main(void)
{
    InitIO();        //初始化   
    while(1)       //死循环让循环内的代码不断执行        
    {  
           RLED = !RLED;           // LED1灯若亮着，则关闭LED1灯，否则打开LED1灯
           Delay(10000);             //延时
           GLED = !GLED;           
           Delay(10000);            
           YLED = !YLED;           
           Delay(10000);
           BLED = !BLED;
           Delay(10000);
           
    }
}