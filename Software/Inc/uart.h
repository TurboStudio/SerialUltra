#ifndef __UART_H_
#define __UART_H_

#define FOSC            11059200UL
#define BRT             (65536 - FOSC / 115200 / 4)

extern bit cmd_flag;
extern char uart_buffer[11];
extern char count;

void UartInit();
void UartSendChar(char dat);
void UartSendStr(char *p);

#endif