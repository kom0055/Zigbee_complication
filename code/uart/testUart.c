#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include <limits.h>


#define DEV_NAME0 "/dev/ttySP0"
#define DEV_NAME1 "/dev/ttySP1"

int main(int argc, char *argv[])
{
    int iFd0,iFd1, i;
    int len0,len1,datalen;
    char ucBuf[]="connect successfully";
    char data[30];
    struct termios opt0,opt1;
	//har path[30] = {0};
	

	//open uart0
	iFd0 = open(DEV_NAME0, O_RDWR | O_NOCTTY);
	if(iFd0 < 0) {
        perror(DEV_NAME0);
        return -1;
	}
    //open uart1
    
    iFd1 = open(DEV_NAME1, O_RDWR | O_NOCTTY);
    if(iFd1 < 0) {
        perror(DEV_NAME1);
        return -1;
    }
    
	/******uart0*******/
    //get attribute of uart0
    tcgetattr(iFd0, &opt0);
    if (tcgetattr(iFd0,   &opt0)<0) {
              return   -1;
    }
	//init the struct of opt
    opt0.c_lflag	&= ~(ECHO | ICANON | IEXTEN | ISIG);
    opt0.c_iflag	&= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    opt0.c_oflag 	&= ~(OPOST);
    opt0.c_cflag 	&= ~(CSIZE | PARENB);
    opt0.c_cflag 	|=  CS8;

    opt0.c_cc[VMIN] 	= 255;
    opt0.c_cc[VTIME]	= 1;
    //bd
	cfsetispeed(&opt0, B115200);
    cfsetospeed(&opt0, B115200);
	//set attribute of 0
    if (tcsetattr(iFd0,   TCSANOW,   &opt0)<0) {
        	return   -1;
    }
    tcflush(iFd0,TCIOFLUSH);
	/******uart1*******/
    //get attribute of uart1
    
    tcgetattr(iFd1, &opt1);
    if (tcgetattr(iFd1,   &opt1)<0) {
              return   -1;
    }
    
    opt1.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
    opt1.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    opt1.c_oflag     &= ~(OPOST);
    opt1.c_cflag     &= ~(CSIZE | PARENB);
    opt1.c_cflag     |=  CS8;

    opt1.c_cc[VMIN]  = 255;
    opt1.c_cc[VTIME] = 1;

    cfsetispeed(&opt1, B115200);
    cfsetospeed(&opt1, B115200);
    //set attribute of 1
    if (tcsetattr(iFd1,   TCSANOW,   &opt1)<0) {
            return   -1;
    }
    tcflush(iFd1,TCIOFLUSH);
    

    len0 = write(iFd0, ucBuf, sizeof(ucBuf));
    len1 = write(iFd1, ucBuf, sizeof(ucBuf));
    if(len0>0)
    {
        printf("write 0 successfully!\n");
    }
    
    if(len1>0)
    {
        printf("write 1 successfully!\n");
    }
    
    while(1)
    {
        //read from 0
        
        /*datalen = read(iFd0,data,20);
        tcflush(iFd0,TCIOFLUSH);
        printf("get data from uart0: %d \n", datalen);
        for (i = 0; i < datalen; i++){
            printf(" %x", data[i]);
        }
        printf("\n");
        //send from 1
        
        if(datalen>0)
        {
            write(iFd1, data, sizeof(data));
            tcflush(iFd1,TCIOFLUSH);
        }
        */
        while((datalen=read(iFd0,data,255))>0)
        {
            printf("get data from uart0:%d\n",datalen);
            if(datalen<10)
            {
                for (i = 0; i < datalen; ++i)
                {
                    if(i==datalen-1) printf("%c\n",data[i]);
                     else printf("%c",data[i]);
                }
            }
            else printf("%s\n",data);
            printf("write to uart1:-----------%d\n", datalen);
            write(iFd1, data, datalen);
        }
    

    
    }

    close(iFd0);
    close(iFd1);
    return 0;
}
