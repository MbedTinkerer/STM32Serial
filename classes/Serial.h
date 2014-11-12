#ifndef SERIAL_H
#define SERIAL_H

#include <inttypes.h>
#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_usart.h"

volatile char * buffer[16];//Buffer to hold converted integer values

/*
 * Initializes the USART peripheral and the corresponding GPIO pins connected to it
 * Edit information in Serial.c to suit your needs
 */
void SerialInit();

/*
 * Print a string to the UART
 */
void SerialPrint(volatile char *s);

/*
 * Print a string to the UART, with a newline at the end
 */
void SerialPrintLine(volatile char *s);

/*
 * Simple method to convert an integer to a string
 * will return pointer to character array which can be used in SerialPrint() for example
 */
char * IntegerToString(uint32_t val);

#endif
