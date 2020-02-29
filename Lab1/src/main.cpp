#include <avr/io.h>
#include <util/delay.h>

int main(){
  // ddrd = 0000 0000 | 0000 0100 = 0000 0100 -> portd2 = output
  DDRD |= (1 << PORTD2);
  // portd = 0000 0000 | 1111 1011 = 0000 0000 -> portd2 = low
  PORTD &= ~(1 << PORTD2);

  while (true)
  {
    // portd2 high
    PORTD |= (1 << PORTD2);
    _delay_ms(1000);
    // portd2 low
    PORTD |= ~(1 << PORTD2);
    _delay_ms(1000);
  }

  return 0;
}