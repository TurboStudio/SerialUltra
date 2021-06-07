#ifndef __CMD_H
#define __CMD_H

#pragma pack(push)
#pragma pack(1)

typedef	struct{
	
	unsigned char HEAD[3];
	unsigned char CMD[5];
	unsigned char DATA;
	char tail;
		
}CMD,*pCMD;

typedef	struct{
	
	unsigned char DIST[5];
	char buf[20];		
}DIST_CMD;

#pragma pack()


extern	CMD uart_cmd;
extern float feedback_dist;
extern char buf[20];
extern char Work_Mode;
extern DIST_CMD DIST_feedback;

void ProcessMessage(pCMD msg);

#endif