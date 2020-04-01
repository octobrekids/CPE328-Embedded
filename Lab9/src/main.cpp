#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>


int main() {  
  // use pd to display set all to output
  DDRD = 0xFF;

  // trigger pin 
 	DDRB |= (1 << PORTB1);
  PORTB &= ~(1 << PORTB1);

  // setup timer1 with no scalar
  // cs10 -> no prescalar / ICNC -> noise cancel
  TCCR1B = (1 << CS10) | (1 << ICNC1);

  while(1){
  	// send 10us pulse to trigger pin
	  PORTB |= (1 << PORTB1);
  	_delay_us(10);
  	PORTB &= ~(1 << PORTB1);
  
  	// set timer1 to detect rising edge
 	  TCCR1B |= (1 << ICES1);
  
  	// wait for rising edge to be detected
  	while (!(TIFR1 & (1 << ICF1)));
  	TIFR1 |= (1 << ICF1);
  	TCNT1 = 0; // นับเวลาตั้งแต่ rising edge 
  
  	// set timer1 to detect falling edge
  	TCCR1B &= ~(1 << ICES1);
  
  	// wait for falling edge to be detected
  	while (!(TIFR1 & (1 << ICF1)));
  	TIFR1 |= (1 << ICF1);
  	

    float pulseCount = ICR1;
    uint8_t distance = (pulseCount / 1000000 * 340) / 2 * 100;
    // 1 pulse/1,000,000 clk
    // sound speed 340 m/s 
    // divided 2 because it count send -> back (we want only 1 travel)
    // divided 100 convert to centimeter
    PORTD = distance;
    _delay_ms(1000);

}
}

// 0-8m แก้เป้น 8 ให้หมดเพราะนับไปกลับ 
// 340 m/s
// (8/340) sec = 23.529 ms เสียงใช้ 23.529 สำหรับ 8 เมตร 
// 1/1000000 = 1usนับ 1 ครั้ง 1 us แล้วนับกี่ครั้งถึงจะได้ 23.529 
// 23.529 / 1 us = xxxxxxxx
// xxxxxx < 65535 ใช้ได้ เพราะน้อยกว่า maximum ถ้ามากกว่าต้องเพิ่ม scalar
