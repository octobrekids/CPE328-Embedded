#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// use fast pwm
// set top clear ocr0 1 / 0
int main()
{
  DDRD |= (1 << PORTD5);
  OCR0A = 156;
  OCR0B = 0; // 0 - 156
  TCCR0A |= (1 << COM0B1) | (1 << WGM01) | (1 << WGM00);
  TCCR0B |= (1 << WGM02) | (1 << CS02) | (1 << CS00); 
  sei();

  while(1)
  {
    int i;
    for(i=5; i<=10; i+=1)
    {
      OCR0B = (i/100.0) * 156.0;
      _delay_ms(1000);
    }

  }
}