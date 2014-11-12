#include "Serial.h"


/*
 * Initializes the USART peripheral and the corresponding GPIO pins connected to it
 * Edit information to suit your needs
 */
void SerialInit()
{
	//Start USART6 clock
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE);

	//Start USART2 GPIO clock
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

	//Init TX pin as output
	GPIO_InitTypeDef gpioInit;

	gpioInit.GPIO_Mode = GPIO_Mode_AF;
	gpioInit.GPIO_OType = GPIO_OType_PP;
	gpioInit.GPIO_PuPd = GPIO_PuPd_NOPULL;
	gpioInit.GPIO_Speed = GPIO_Speed_2MHz;
	gpioInit.GPIO_Pin = GPIO_Pin_6;

	GPIO_Init(GPIOC, &gpioInit);

	//Alternate function configuration
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_USART6);

	//Initialize UART
	USART_InitTypeDef UART_INIT;

	UART_INIT.USART_BaudRate = 9600;
	UART_INIT.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	UART_INIT.USART_Mode = USART_Mode_Tx;
	UART_INIT.USART_Parity = USART_Parity_No;
	UART_INIT.USART_StopBits = USART_StopBits_1;
	UART_INIT.USART_WordLength = USART_WordLength_8b;

	USART_Init(USART6, &UART_INIT);

	USART_Cmd(USART6, ENABLE);
}


/*
 * Print a string to the UART
 */
void SerialPrint(volatile char *s)
{
	while(*s)
	{
		// wait until data register is empty
		while( !(USART6->SR & 0x00000040) );
		USART_SendData(USART6, *s);
		*s++;
	}
}


/*
 * Print a string to the UART, with a newline at the end
 */
void SerialPrintLine(volatile char *s)
{
	SerialPrint(s);
	SerialPrint("\n\r");
}


/*
 * Simple method to convert an integer to a string
 * will return pointer to character array which can be used in SerialPrint() for example
 */
char * IntegerToString(uint32_t val)
{
	sprintf(buffer, "%d", val);
	return &buffer;
}
