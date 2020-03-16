#ifndef UART_H_INCLUDED
#define UART_H_INCLUDED

#include "micro_config.h"
#include "common_macros.h"


/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/

/* UART Driver Baud Rate */
#define UART_BAUDRATE 9600

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void UART_init(void);

void UART_sendByte(const uint8_t data);

uint8_t UART_receiveByte(void);

void UART_sendString(const uint8_t *Str);

void UART_receiveString(uint8_t *Str); // Receive until #

#endif /* UART_H_ */


