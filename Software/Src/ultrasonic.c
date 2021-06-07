#include "STC8G.h"
#include "intrins.h"
#include "ultrasonic.h"
#include "adc.h"
/******************************************************************
Trig -> P33
Echo -> P32
*******************************************************************/

//����Ƶ��Ϊ11.0592MHz

unsigned char cnt;                              //�洢PCA��ʱ�������
unsigned long count0;                           //��¼��һ�εĲ���ֵ
unsigned long count1;                           //��¼���εĲ���ֵ
unsigned long length;                           //�洢�źŵ�ʱ�䳤��

float cm = 0.0;
float time = 0.0;

void Delay15us();

//PCA�жϷ�����
void PCA_Isr() interrupt 7
{
    if (CF)
    {
        CF = 0;
        cnt++;                                  //PCA��ʱ�������+1
    }
    if (CCF0)
    {
        CCF0 = 0;
        count0 = count1;                        //������һ�εĲ���ֵ
        ((unsigned char *)&count1)[3] = CCAP0L;
        ((unsigned char *)&count1)[2] = CCAP0H;
        ((unsigned char *)&count1)[1] = cnt;
        ((unsigned char *)&count1)[0] = 0;
        length = count1 - count0;              	//length����ļ�Ϊ�����������
			
				time = length*0.0904;										//���㳬��������	
				cm = time/58.0;
    }
}

//������ģ���ʼ��
void Ultrasonic_Init()
{
	
		P3M0 = 0x00;
		P3M1 = 0x04;
	
		P5M0 = 0x00;
		P5M1 = 0x00;
	
    cnt = 0;                                    //�û�������ʼ��
    count0 = 0;
    count1 = 0;
    length = 0;
    CCON = 0x00;
    CMOD = 0x09;                                //PCAʱ��Ϊϵͳʱ��,ʹ��PCA��ʱ�ж�

		CL= 0x00;
		CH = 0x00;
	
    CCAPM0 = 0x31;                              //PCAģ��0Ϊ16λ����ģʽ�����ز���
		CCAP0L = 0x00;
		CCAP0H = 0x00;

		CR = 1;                                     //����PCA��ʱ��
	
		P54 = 0;
		P33 = 0;
		
}

//��ȡ��������������
float Get_Distance_cm()
{	
		CR = 1;
		P33 = 1;
		Delay15us();
		P33 = 0;
	
		if(cm > Get_Threshold())										//��ֵ�жϣ��������볬����ֵ��S�˿�����ߵ�ƽ
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

