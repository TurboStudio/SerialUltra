#include "STC8G.h"
#include "intrins.h"
#include "timer.h"
//���Թ���Ƶ��Ϊ11.0592MHz
volatile unsigned int millis;

void TM0_Isr() interrupt 1
{
    millis++;                                 
}

void Timer_Init()																//����10ms��ʱ���ж�	
{
		millis = 0;
	
    TMOD |= 0x00;                               //ģʽ0
    TL0 = 0x00;                                 //��65536-0xdc00��*��1/11059200*12��
    TH0 = 0xdc;
    TR0 = 1;                                    //������ʱ��
    ET0 = 1;                                    //ʹ�ܶ�ʱ���ж�

}

