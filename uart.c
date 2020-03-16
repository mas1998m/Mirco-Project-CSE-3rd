#include "uart.h"

void UART_init(void){

float Baudrate_Fraction;
uint16_t Baudrate;
	
	
    SET_BIT(SYSCTL_RCGCUART_R,0); //enable UART0 Clock and Registers Access
    SET_BIT(SYSCTL_RCGCGPIO_R,0); // Enable PORT A Clock and Registers Access
    CLEAR_BIT(UART0_CTL_R,0); //Disable UART0 before Configuration
    SET_BIT(UART0_CTL_R,5); // Set The High Speed option on

    Baudrate= ((CLOCK)/(8*UART_BAUDRATE)); //Calculate The Baud Rate integer value
    UART0_IBRD_R |= Baudrate; // Set The Integer Baud rate value into the Register
     Baudrate_Fraction =  (CLOCK) / (8.0 * UART_BAUDRATE)      -   (int)(   (CLOCK) / (8 * UART_BAUDRATE)   )  ; // Calculate the fraction of the Baudrate
    UART0_FBRD_R =  ( Baudrate_Fraction *64)+0.5; //Set The Fraction Baud rate value into the Register
    UART0_LCRH_R |= (UART_LCRH_WLEN_8|UART_LCRH_FEN); // Set the word Length to 8 bit and Enable FIFOS , 1 Stop Bit , Parity Disabled


    SET_BIT(UART0_CTL_R,0); // Enable UART0 After Configuration
    GPIO_PORTA_AFSEL_R |= 0x03;  // Enable PA0 & PA1 Alternative Function
    GPIO_PORTA_PCTL_R =  ( (GPIO_PORTA_PCTL_R & 0xFFFFFF00) | 0x00000011 ); // Set PA0 & PA1 Alternative Function to UART0
    GPIO_PORTA_DEN_R |= 0x03; // Enable Digital Use for PA0 & PA1
    GPIO_PORTA_AMSEL_R &= ~0x03; // Disable Analog Function for PA0 & PA1

}

void UART_sendByte(const uint8_t data){ 
    while((UART0_FR_R&UART_FR_TXFF) != 0); // booling until the sending FIFO is not EMPTY
    UART0_DR_R = data;
}





uint8_t UART_receiveByte(void){
    while((UART0_FR_R&UART_FR_RXFE)!= 0); // booling until the receiving FIFO is not EMPTY
    return((unsigned char)(UART0_DR_R&0xFF));
}
void UART_sendString(const uint8_t *Str){
	uint8_t i = 0;
	while(Str[i] != '\0')
	{
		UART_sendByte(Str[i]);
		i++;
	}
}

void UART_receiveString(uint8_t *Str){
    uint8_t i = 0;
	Str[i] = UART_receiveByte();
	while(Str[i] != '#')
	{
		i++;
		Str[i] = UART_receiveByte();
	}
	Str[i] = '\0';
}
