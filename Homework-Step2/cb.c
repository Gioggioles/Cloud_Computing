/*
 * cb.c
 *
 *  Created on: Oct 8, 2022
 *      Author: ogruber
 */
#include "main.h"

#define CAPACITY 80
struct cb {
  volatile int head;
  volatile uint8_t buffer[CAPACITY];
  volatile int tail;
};


int cb_full(struct cb *cb) {
  int next = (cb->head + 1) % CAPACITY;
  return (next==cb->tail);
}

int cb_empty(struct cb *cb) {
  return (cb->tail==cb->head);
}

int cb_put(struct cb *cb, uint8_t byte) {
  int next = (cb->head + 1) % CAPACITY;
  if (next==cb->tail)
    return -1;
  cb->buffer[cb->head] = byte;
  cb->head = next;
  return 0;
}

int cb_get(struct cb *cb, uint8_t *bytePt) {
  if (cb->tail==cb->head)
    return -1;
  *bytePt = cb->buffer[cb->tail];
  cb->tail = (cb->tail + 1) % CAPACITY;
  return 0;
}

void cb_init(struct cb *cb) {
  cb->head = cb->tail = 0;
}


