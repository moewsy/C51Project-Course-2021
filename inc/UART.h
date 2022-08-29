#ifndef __YUI_UART_H
#define __YUI_UART_H

#include <main.h>


void uart_init(void);
void uart_tx_byte(u8 byte);
void uart_tx_string(u8 *p);


#endif /* __YUI_UART_H */
