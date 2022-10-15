/*
* RING.c
*
*  Created on: 7 cze 2020
*      Author: Admin
*/
#include "ring.h"
#include <string.h>

/*
* @brief Initialize ring buffer.
* @param ring - Buffer to be initialized.
*/
void ring_buffer_init(Ring_buffer_type *ring) 
{
  ring->tail = ring->head = 0;
  ring->status = RING_IS_EMPTY;
}


/*
* @brief Checks if the buffer is empty.
* @param ring - Buffer to be checked.
* @return True if is empty.
*/
uint8_t ring_buffer_is_empty(Ring_buffer_type *ring)
{
  return (RING_IS_EMPTY == ring->status);
}


/*
* @brief Checks if the buffer is full.
* @param ring - Buffer to be checked.
* @return True if is full.
*/
uint8_t ring_buffer_is_full(Ring_buffer_type *ring) 
{
  return (RING_IS_FULL == ring->status);
}


/*
* @brief 
* @param ring - Buffer 
* @return 
*/
uint8_t ring_buffer_fill(Ring_buffer_type *ring)
{
  if (ring->head > ring->tail)
  {
    return (ring->head - ring->tail);
  } 
  else
  {
    return (ring->head + UCAN_FRAME_RX_FIFO_SIZE - ring->tail);
  }
}


/*
* @brief Push data to buffer.
* @param ring - Buffer 
* @param data - Data to be sent.
* @param len - Data vector length.
*/
void ring_buffer_push(Ring_buffer_type *ring, uint8_t *data, uint32_t len) 
{
  if(ring_buffer_is_full(ring))
  {
    return;
  }

  if(len > MAX_CAN_FRAME_SIZE)
  {
    return;
  }

  memcpy(&(ring->data[ring->head][0]), data, len);

  if(len < MAX_CAN_FRAME_SIZE) 
  {
    memset(&(ring->data[ring->head][len]), 1, MAX_CAN_FRAME_SIZE - len);
  }

  ring->size[ring->head] = len;
  ring->head++;
  ring->status = RING_IS_NOT_FULL;

  if(ring->head >= UCAN_FRAME_RX_FIFO_SIZE)
  {
    ring->head = 0;
  }

  if((ring->head + 1) % UCAN_FRAME_RX_FIFO_SIZE == ring->tail) 
  {
    ring->status = RING_IS_FULL;
  }
}


/*
* @brief Get item from buffer.
* @param ring - Buffer 
* @param return - Returns first item or empty item if buffer is empty.
*/
Ring_item_type* ring_buffer_get(Ring_buffer_type *ring)
{
  static Ring_item_type retval = {NULL, 0};

  retval.len = 0;
  retval.data = NULL;

  if(ring_buffer_is_empty(ring))
  {
    return &retval;
  }

  retval.data = &(ring->data[ring->tail][0]);
  retval.len = (ring->size[ring->tail]);
  ring->tail++;

  if(ring->tail >= UCAN_FRAME_RX_FIFO_SIZE)
  {
    ring->tail = 0;
  }

  if(ring->tail == ring->head) 
  {
    ring->status = RING_IS_EMPTY;
  }

  return &retval;
}
