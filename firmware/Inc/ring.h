/*
* RING.h
*
*  Created on: 7 cze 2020
*      Author: Admin
*/

#ifndef STM32G4XX_HAL_DRIVER_INC_RING_H_
#define STM32G4XX_HAL_DRIVER_INC_RING_H_

#include "ucan_fd_protocol_stm32g431.h"

typedef enum
{
  RING_IS_EMPTY,
  RING_IS_NOT_FULL,
  RING_IS_FULL
} Ring_status_type;


typedef struct 
{
  uint8_t *data;
  size_t len;
} Ring_item_type;


typedef struct 
{
  uint8_t data[UCAN_FRAME_RX_FIFO_SIZE][MAX_CAN_FRAME_SIZE];
  uint8_t size[UCAN_FRAME_RX_FIFO_SIZE];
  uint8_t tail;
  uint8_t head;
  Ring_status_type status;
} Ring_buffer_type;


void ring_buffer_init(Ring_buffer_type *ring);
uint8_t ring_buffer_is_empty(Ring_buffer_type *ring);
uint8_t ring_buffer_is_full(Ring_buffer_type *ring);
void ring_buffer_push(Ring_buffer_type *ring, uint8_t *data, uint32_t len);
Ring_item_type* ring_buffer_get(Ring_buffer_type *ring);
uint8_t ring_buffer_fill(Ring_buffer_type *ring);

#endif /* STM32G4XX_HAL_DRIVER_INC_RING_H_ */