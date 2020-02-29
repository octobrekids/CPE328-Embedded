#define LCD_DATA_DDR DDRB
#define LCD_DATA_PORT PORTB

#define LCD_RS_DDR DDRD
#define LCD_RS_PORT PORTD
#define LCD_RS_PIN PORTD0

#define LCD_RW_DDR DDRD
#define LCD_RW_PORT PORTD
#define LCD_RW_PIN PORTD1

#define LCD_E_DDR DDRD
#define LCD_E_PORT PORTD
#define LCD_E_PIN PORTD2

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>


void sendLCDCommand(uint8_t command){
  // rs=0 (command register), rw=0 (write mode)
  LCD_RS_PORT &= ~(1 << LCD_RS_PIN);
  LCD_RW_PORT &= ~(1 << LCD_RW_PIN);
  // put command to data bus
  LCD_DATA_PORT = command;
  // send pulse to E
  LCD_E_PORT |= (1 << LCD_E_PIN);
  _delay_us(100);
  LCD_E_PORT &= ~ (1 << LCD_E_PIN);
  // down 1 s and delay 1 s
  _delay_us(200);

}

void sendLCDData(uint8_t data){
  // rs=0 (command register), rw=0 (write mode)
  LCD_RS_PORT |= (1 << LCD_RS_PIN);
  LCD_RW_PORT &= ~(1 << LCD_RW_PIN);
  // put command to data bus
  LCD_DATA_PORT = data;
  // send pulse to E
  LCD_E_PORT |= (1 << LCD_E_PIN);
  _delay_us(500);
  LCD_E_PORT &= ~ (1 << LCD_E_PIN);
  // down 1 s and delay 1 s
  _delay_us(1000);

}

int main()
{
  //initialize lcd port to output
  LCD_DATA_DDR = 0xFF;
  LCD_E_DDR |= (1 << LCD_E_PIN);
  LCD_E_PORT &= ~(1 << LCD_E_PIN);
  LCD_RW_DDR |= (1 << LCD_RW_PIN);
  LCD_RW_PORT &= ~(1 << LCD_RW_PIN);
  LCD_RS_DDR |= (1 << LCD_RS_PIN);
  LCD_RS_PORT &= ~(1 << LCD_RS_PIN);

  //initialize lcd
  sendLCDCommand(0x38); // 2 line, 5x7
  sendLCDCommand(0x0E); // display on, cursor off
  sendLCDCommand(0x01); // clear display
  sendLCDCommand(0x00);
  _delay_ms(1);

  const char* word = "Hello";

  int i = 0;
  while (word[i] != '\0')
  {
    sendLCDData(word[i]);
    i += 1;
  }
  return 0;
}