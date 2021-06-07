#include "STC8G.h"
#include "intrins.h"
#include "uart.h"

bit busy;
bit cmd_flag = 0;
char count;
char uart_buffer[11] = {0};

//串口中断服务函数
void UartIsr() interrupt 4																						
{
    if (TI)
    {
        TI = 0;
        busy = 0;
    }
    if (RI)
    {
        RI = 0;					
				uart_buffer[count] = SBUF;
				if((count >= 10) || (SBUF == '\r') || (SBUF == '\n'))	
				{
					count = 0;
					cmd_flag = 1;
				}
        else count++;        
    }
}

//串口初始化
void UartInit()
{
    SCON |= 0x50;
    TMOD |= 0x00;
    TL1 = BRT;
    TH1 = BRT >> 8;
    TR1 = 1;
    AUXR |= 0x40;
    count = 0x00;
    busy = 0;
}

//串口发送函数（字符）
void UartSendChar(char dat)
{
    while (busy);
    busy = 1;
    SBUF = dat;
}

//串口发送函数（字符串）
void UartSendStr(char *p)
{
    while (*p)
    {
        UartSendChar(*p++);
    }
}


