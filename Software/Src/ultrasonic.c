#include "STC8G.h"
#include "intrins.h"
#include "ultrasonic.h"
#include "adc.h"
/******************************************************************
Trig -> P33
Echo -> P32
*******************************************************************/

//工作频率为11.0592MHz

unsigned char cnt;                              //存储PCA计时溢出次数
unsigned long count0;                           //记录上一次的捕获值
unsigned long count1;                           //记录本次的捕获值
unsigned long length;                           //存储信号的时间长度

float cm = 0.0;
float time = 0.0;

void Delay15us();

//PCA中断服务函数
void PCA_Isr() interrupt 7
{
    if (CF)
    {
        CF = 0;
        cnt++;                                  //PCA计时溢出次数+1
    }
    if (CCF0)
    {
        CCF0 = 0;
        count0 = count1;                        //备份上一次的捕获值
        ((unsigned char *)&count1)[3] = CCAP0L;
        ((unsigned char *)&count1)[2] = CCAP0H;
        ((unsigned char *)&count1)[1] = cnt;
        ((unsigned char *)&count1)[0] = 0;
        length = count1 - count0;              	//length保存的即为捕获的脉冲宽度
			
				time = length*0.0904;										//计算超声波距离	
				cm = time/58.0;
    }
}

//超声波模块初始化
void Ultrasonic_Init()
{
	
		P3M0 = 0x00;
		P3M1 = 0x04;
	
		P5M0 = 0x00;
		P5M1 = 0x00;
	
    cnt = 0;                                    //用户变量初始化
    count0 = 0;
    count1 = 0;
    length = 0;
    CCON = 0x00;
    CMOD = 0x09;                                //PCA时钟为系统时钟,使能PCA计时中断

		CL= 0x00;
		CH = 0x00;
	
    CCAPM0 = 0x31;                              //PCA模块0为16位捕获模式（边沿捕获）
		CCAP0L = 0x00;
		CCAP0H = 0x00;

		CR = 1;                                     //启动PCA计时器
	
		P54 = 0;
		P33 = 0;
		
}

//获取超声波测量距离
float Get_Distance_cm()
{	
		CR = 1;
		P33 = 1;
		Delay15us();
		P33 = 0;
	
		if(cm > Get_Threshold())										//阈值判断，测量距离超过阈值，S端口输出高电平
		{
			P54 = 0;
		}
		else
			P54 = 1;
		return cm;
}

void Delay15us()		//@11.0592MHz
{
	unsigned char i;

	i = 39;
	while (--i);
}

