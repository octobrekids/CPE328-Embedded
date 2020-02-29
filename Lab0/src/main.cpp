// #include <Arduino.h>

// void setup() {
//   // put your setup code here, to run once:
// }

// void loop() {
//   // put your main code here, to run repeatedly:
// }

#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
int main(){
  while(true){
    DDRB |= (1<<PORTB0);
    PORTB |= (1<<PORTB0);
    _delay_ms(1000);
    PORTB &= ~(1<<PORTB0);
    _delay_ms(1000);
  }
  return 0;
}
