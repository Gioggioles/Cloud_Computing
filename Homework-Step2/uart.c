#include "main.h"

/**
 * Receive a character from the given uart, this is a non-blocking call.
 * Returns 0 if there are no character available.
 * Returns 1 if a character was read.
 */
int uart_receive(int uart, uint8_t *s) {
  unsigned short* uart_fr = (unsigned short*) (uart + UART_FR);
  unsigned short* uart_dr = (unsigned short*) (uart + UART_DR);
  if (*uart_fr & UART_RXFE)
    return 1;
  *s = (*uart_dr & 0xff);
  return 0;
}

/**
 * Sends a character through the given uart, this is a blocking call.
 * The code spins until there is room in the UART TX FIFO queue to send
 * the character.
 */
void uart_send(int uart, unsigned char s) {
  unsigned short* uart_fr = (unsigned short*) (uart + UART_FR);
  unsigned short* uart_dr = (unsigned short*) (uart + UART_DR);
  while (*uart_fr & UART_TXFF)
    ;
  *uart_dr = s;
}

/**
 * This is a wrapper function, provided for simplicity,
 * it sends a C string through the given uart.
 */
void uart_send_string(int uart, const unsigned char *s) {
  while (*s != '\0') {
    uart_send(uart, *s);
    s++;
  }
}

void uart_init(int uart){
  uint16_t lcr = *(uint16_t*) (uart + CUARTLCR_H);
  lcr |= CUARTLCR_H_FEN;
  *(uint16_t*) (uart + CUARTLCR_H) = lcr;
  }
  
void uart_rx_handler(struct cb *cb, void* cookie){
  uint8_t c;
  uart_receive(UART0, &c);
  while(c){
  	if (!cb_full(cb))
  	  cb_put(cb, c);
  	uart_receive(UART0, &c); 
  	  }
 return;
   }
