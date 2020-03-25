#include <avr/io.h>
#define F_CPU 1000000UL

// use waveform generator to toggle 'automatically'
// cons : cant use every ports just some ports
int main()
{
  // output at pb1
  DDRB |= (1 << PORTB1);
  // toggle when compare match
  TCCR1A |= (1 << COM1A0);
  // using ctc mode & use clock source = 8 
  TCCR1B |= (1 << WGM12) | (1 << CS11);
  // set ocr
  OCR1A = 62499;



  while(1)
  {
   
  }
  return 0;
}