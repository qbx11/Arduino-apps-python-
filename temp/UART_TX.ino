#include <avr/io.h>
#include <stdlib.h>
#include <string.h>
#include <util/delay.h>
 
#ifndef _BV
#define _BV(bit)        (1<<(bit))
#endif
#ifndef sbi
#define sbi(reg,bit)    reg |= (_BV(bit))
#endif
 
#ifndef cbi
#define cbi(reg,bit)    reg &= ~(_BV(bit))
#endif

#ifndef tbi
#define tbi(reg,bit)    reg ^= (_BV(bit))
#endif

void UART_init(){
    uint16_t ubrr = 51; //USART Baud Rate Register (holds baud rate value) 51 -> 19200
    UBRR0H = 0; //UBRR is divided between two registers
    UBRR0L = 51;

    sbi(UCSR0C,UCSZ01);sbi(UCSR0C,UCSZ00); //8 bit data

    sbi(UCSR0B,TXEN0);//transmiterr enable 

}

void uart_char(char c){
  while(bit_is_clear(UCSR0A, UDRE0)){}//if buffer is empty
  UDR0 =c; //buffer equals c
  
}

void uart_string(const char* str) {
    while (*str) {
        uart_char(*str++);
    }
}

int main() {
  UART_init();
  uint16_t counter = 0;
  char buffer[32];

  uart_string("\r\nsiema\r\n");// \r carriage return, \n new line
  uart_string("Zaczynamy odliczanie!\r\n");
  
  _delay_ms(2000);
	while(1){
    //IntegerToString(number,array, decimal)
    itoa(counter,buffer,10);
    uart_string("Timer: ");
    uart_string(buffer);
    uart_string("\r\n");

    counter++;
    _delay_ms(1000);
   
  }
}