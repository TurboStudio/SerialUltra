#include "main.h"
#include "cmd.h"
#include "timer.h"
#include "uart.h"
#include "adc.h"
#include "stdio.h"
#include "ultrasonic.h"

//���Թ���Ƶ��Ϊ11.0592MHz

void main()
{
		unsigned lasttime = 0;
		
	
		ADC_Init();
	  UartInit();
		Timer_Init();
		Ultrasonic_Init();
	
    ES = 1;
    EA = 1;
		
		while(1)
		{
			
			ProcessMessage((pCMD) uart_buffer);															//�������
			
			if(Work_Mode == '1')																						//�����ϴ�ģʽ
				{
					if((millis - lasttime) >=10)
					{	
						feedback_dist = Get_Distance_cm();
						sprintf(DIST_feedback.buf,"%0.2f",feedback_dist);
						
						UartSendStr((char*)&DIST_feedback);
						UartSendStr("cm");
						UartSendStr("\r\n");
						
						lasttime = millis;
					}
				}
			else if((millis - lasttime) >=6)	
				{
					feedback_dist = Get_Distance_cm();	
					lasttime = millis;
				}
				
		}

}



