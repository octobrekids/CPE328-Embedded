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
    // ddrb = 0000 0000 | 0000 0001 = 0000 0001 (1) -> portb0 = output
    DDRB |= (1<<PORTB0);
    // port = 0000 0000 | 0000 0001 = 0000 0001 (1) -> portb0 = high
    PORTB |= (1<<PORTB0);
    _delay_ms(1000);
    // port b = 0000 0001 & 1111 1110 = 0000 0000 low -> portb0 = low
    PORTB &= ~(1<<PORTB0);
    _delay_ms(1000);
  }
  return 0;
}
