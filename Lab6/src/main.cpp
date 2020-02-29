#include <avr/io.h>

void USART_Transmit( unsigned char data )
{
  // wait for empty transmit buffer
  while (!(UCSR0A & (1 << UDRE0)))
  // put data into buffer, sends the data **1-8 databits**
  UDR0 = data;
}

unsigned char USART_Receive ( void )
{
  //wait for data to be received
  while(!(UCSR0A & (1 << RXC0)));
  return UDR0;
}

int main()
{
  // baud rate 9600bps in high speed mode
  UBRR0 = 12;
  // enable high speed mode
  UCSR0A = (1 << U2X0);
  // enable receiver and transmitter
  UCSR0B = (1 << RXEN0) | (1 << TXEN0);
  // 8 data bit
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);

  char* buffer = "hello";
  uint8_t i = 0;

  // send
  //while(buffer[i]!='\0')
  //{
  //  USART_Transmit(buffer[i]);
  //  i++;
  //}

  // receive
  while(1)
  {
    unsigned c = USART_Receive();
    USART_Transmit(c+1);
  }

  return 0;
}