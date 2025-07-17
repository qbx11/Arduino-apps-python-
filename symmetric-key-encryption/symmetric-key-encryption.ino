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

void decrypt(const char* input, char* output, const char* chars, const char* key){
  size_t len = strlen(input);
  size_t k=0;
  for (size_t i=0; i < len; i++){
    
    char c = input[i];
    const char* found = strchr(chars,c);
    if(found){
      size_t index = found - chars;
      output[k++]= key[index];
    }
    else{
      output[k++] = '?';
    }

  }
  output[k] = '\0';
}


int main() {
  UART_init();
  char chars[] = " 0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
  char key[]   = "5L0Po6s4f1tvIaFl KrjbGCepZB9zNXTVOWgdJnh3RmAkEwHQcu2iUM8qS7YyxD";
  
  char encoded[64];
  char original[64];
  

	while(1){
    uart_get_string(encoded,sizeof(encoded));
    decrypt(encoded,original,key,chars);
    uart_string("Received encrypted message: ");
    uart_string(encoded);
    uart_string("\r\n");
    uart_string("Decrypted message: ");
    uart_string(original);
    

    
	
  }
}