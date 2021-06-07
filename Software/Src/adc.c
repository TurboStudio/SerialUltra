#include "STC8G.h"
#include "intrins.h"
#include "adc.h"
/******************************************************************
ADC	->	P55
*******************************************************************/

void ADC_Init()
{
    P5M0 |= 0x00;                                //设置P55为ADC口
    P5M1 |= 0x20;
	
		P_SW2 |= 0x80;															//配置ADCTIM需将P_SW2最高位置位
		ADCTIM = 0x3f;
		P_SW2 &= 0x7f;
	
    ADCCFG = 0x2f;                              //设置ADC时钟为系统时钟/2/16
    ADC_CONTR = 0x85;                           //使能P55为ADC输入
}

int ADC_GetValue()
{
		int value = 0;
			
		ADC_CONTR |= 0x40;													//启动ADC转换
		_nop_();
		_nop_();
	
		while(!(ADC_CONTR & 0x20));									//查询ADC转换完成标志
		ADC_CONTR &= ~0x20;													//清除标志
		value |= (ADC_RES << 8);
		value	|= ADC_RESL;
		
		return value;
}

float Get_Threshold()														//获取超声波设置阈值,范围0-300，单位cm
{
		float	dist_threshold;
	
		dist_threshold = (float)(1024-ADC_GetValue())/1024*300;
	
		if(dist_threshold < 0)	dist_threshold = 0;
		if(dist_threshold > 300)dist_threshold = 300;
	
		return dist_threshold;
}