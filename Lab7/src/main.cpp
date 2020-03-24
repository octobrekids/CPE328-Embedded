#define F_CPU 1000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// use volatile variable because it's use in main and ISR
volatile int blink = 0;

ISR(PCINT2_vect)
{
  // pin-change interupt cant select source as external interrupt
  // pin-change see rising edge(1) and falling edge(2) both as interrupt 
  // then we need to detect when button released
  // no double interrupt again !
  while(!(PIND & (1 << PORTD2)));
  _delay_ms(10);
  blink = !blink;
}

int main()
{
  // led
  DDRD |= (1 << PORTD0);
  PORTD &= ~(1 << PORTD0);

  // button
  DDRD &= ~(1 << PORTD2);
  PORTD |= (1 << PORTD2);

  
  // PCINT18 in PCIE2
  PCICR |= (1 << PCIE2);
  // enable pinchange interrupt at pcint18
  PCMSK2 |= (1 << PCINT18);
  sei();

  while(1)
  {
    // not blink to blink 
    if (blink == 1)
    {
      PORTD |= (1 << PORTD0);
      _delay_ms(1000);
      // if interrupt the led will stop after 1sec
      PORTD &= ~ (1 << PORTD0);
      _delay_ms(1000);
    }
    // blink to not blink 
    else
    {
      PORTD &= ~(1 << PORTD0);
    }
  }
  return 0;
}