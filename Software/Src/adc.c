#include "STC8G.h"
#include "intrins.h"
#include "adc.h"
/******************************************************************
ADC	->	P55
*******************************************************************/

void ADC_Init()
{
    P5M0 |= 0x00;                                //����P55ΪADC��
    P5M1 |= 0x20;
	
		P_SW2 |= 0x80;															//����ADCTIM�轫P_SW2���λ��λ
		ADCTIM = 0x3f;
		P_SW2 &= 0x7f;
	
    ADCCFG = 0x2f;                              //����ADCʱ��Ϊϵͳʱ��/2/16
    ADC_CONTR = 0x85;                           //ʹ��P55ΪADC����
}

int ADC_GetValue()
{
		int value = 0;
			
		ADC_CONTR |= 0x40;													//����ADCת��
		_nop_();
		_nop_();
	
		while(!(ADC_CONTR & 0x20));									//��ѯADCת����ɱ�־
		ADC_CONTR &= ~0x20;													//�����־
		value |= (ADC_RES << 8);
		value	|= ADC_RESL;
		
		return value;
}

float Get_Threshold()														//��ȡ������������ֵ,��Χ0-300����λcm
{
		float	dist_threshold;
	
		dist_threshold = (float)(1024-ADC_GetValue())/1024*300;
	
		if(dist_threshold < 0)	dist_threshold = 0;
		if(dist_threshold > 300)dist_threshold = 300;
	
		return dist_threshold;
}