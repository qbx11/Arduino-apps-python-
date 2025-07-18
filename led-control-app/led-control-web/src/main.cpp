#include <Arduino.h>
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
    sbi(UCSR0B,RXEN0);//receiver enable 


}

void flush_UART_RX() {
    while (bit_is_set(UCSR0A, RXC0)) {
        volatile char dummy = UDR0;
    }
}

char uart_getchar(){
  while(bit_is_clear(UCSR0A,RXC0)){}
  return UDR0;
}

uint8_t bufsize = 32;
void uart_get_string(char *buf, uint8_t bufsize) {
    flush_UART_RX();
    uint8_t i = 0;
    char c;

    while (1) {
        c = uart_getchar();

        // Obsługa końca linii (Enter = \r lub \n)
        if (c == '\r' || c == '\n') {
            break;
        }

        // Tylko jeśli nie przekroczono rozmiaru bufora
        if (i < bufsize - 1) {
            buf[i++] = c;
        }
    }

    buf[i] = '\0';  // Zakończ string znakiem null
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
  sbi(DDRB,PB0);

  
  char c;
	while(1){
    do { //to ignore \r and \n from clicking enter on keyboar
             c = uart_getchar();
        } while (c == '\r' || c == '\n');
    if(c == '1'){
      sbi(PORTB,PB0);
    }
    else if (c == '0'){
      cbi(PORTB,PB0);
    }

  }
}