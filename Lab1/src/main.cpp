#include <avr/io.h>
#include <util/delay.h>

int main(){
  DDRD |= (1 << PORTD2);
  PORTD &= ~(1 << PORTD2);

  while (true)
  {
    PORTD |= (1 << PORTD2);
    _delay_ms(1000);
    PORTD |= ~(1 << PORTD2);
    _delay_ms(1000);
  }

  return 0;
}