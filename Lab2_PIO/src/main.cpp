#include<avr/io.h>
#include<util/delay.h>

int main()
{
  // REFS[1:0] = 01 (use Avcc as reference voltage for ADC)
  // ADLAR = 1 (left adjust ADC result so we can just read 
  // the upper 8 bits and discard the last 2 LSB bits)
  // ADMUX[3:0] = 0000 (use ADC0 which is the default value) 
  //ADMUX |= (1 << REFS0) | (1 << ADLAR); <-- old
  ADMUX |= (1 << REFS0) | (1 << ADLAR);
  // ADEN = 1 (enable the ADC)
  // ADPS[2:0] = 011 (set prescaler to 8 to generate 125khz clock)
  // assume Fcpe = 8Mhz for ADC
  ADCSRA |= (1 << ADEN) | (1 << ADPS1) | (1 << ADPS0);

  // set every port of ddrd to output 
  DDRD = 0xFF;


  while(1)
  {
    // start conversion (single conversion mode)
    ADCSRA |= (1 << ADSC);
    // wait until the ADSC bit is clear by the device which indicated
    // end of conversion
    while(ADCSRA & (1 << ADSC));
    // read the result and display on PORTD0-7
    //PORTD = ADCH; <-- old
    PORTD = (ADC/1023.0) * 5 * 100-50;
  }
  return 0;
}