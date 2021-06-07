#include "cmd.h"
#include "uart.h"
#include "string.h"
#include "stdio.h"

const char Head[3] = {'A','T','+'};
const char Mode[5] = {'M','O','D','E','='};
const char Dist[5] = {'D','I','S','T','='};
	
char Work_Mode = '0';																								//模块工作模式存储变量  0:被动		1:主动
float feedback_dist = 0.0;																					//上传距离变量

CMD MODE_feedback = {
	
	{'A','T','+'},
	{'M','O','D','E','='},
	'0',
	'\0'
};

DIST_CMD DIST_feedback = {
	
	{'D','i','s','t','='},
	{0}
};

//命令解析函数
void ProcessMessage(pCMD msg)																			 
{
	
	if(cmd_flag && ((uart_buffer[9] == '\r') || (uart_buffer[9] == '\n')))
	{	
		if(memcmp((msg->HEAD),Head,3) == 0)
		{
			if(memcmp((msg->CMD),Mode,5) == 0)													//模块工作模式设置或读取
			{
				if(msg->DATA == '?')
				{
					MODE_feedback.DATA = Work_Mode;
					UartSendStr((char*)&MODE_feedback);	
					UartSendStr("\r\n");					
				}
				else if((msg->DATA == '0') || (msg->DATA == '1'))
				{				
					Work_Mode = msg->DATA;
					UartSendStr("OK");
					UartSendStr("\r\n");
				}
				else
				{
					UartSendStr("command error!");
					UartSendStr("\r\n");
				}
			}
			else if(memcmp((msg->CMD),Dist,5) == 0)											//被动模式下距离数据上传
			{
				if(msg->DATA == '?')
				{
					if(Work_Mode == '0')
					{
						sprintf(DIST_feedback.buf,"%0.2f",feedback_dist);
						UartSendStr((char*)&DIST_feedback);
						UartSendStr("cm");
						UartSendStr("\r\n");
					}
				}
				else
				{
					UartSendStr("command error!");
					UartSendStr("\r\n");
				}			
			}else return;			
		}else return;
		
		cmd_flag = 0;	
		count = 0;
	}
			
}