#include "STC8G.h"
#include "intrins.h"
#include "timer.h"
//测试工作频率为11.0592MHz
volatile unsigned int millis;

void TM0_Isr() interrupt 1
{
    millis++;                                 
}

void Timer_Init()																//配置10ms定时器中断	
{
		millis = 0;
	
    TMOD |= 0x00;                               //模式0
    TL0 = 0x00;                                 //（65536-0xdc00）*（1/11059200*12）
    TH0 = 0xdc;
    TR0 = 1;                                    //启动定时器
    ET0 = 1;                                    //使能定时器中断

}

