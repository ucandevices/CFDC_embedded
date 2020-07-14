/*
 * RING.h
 *
 *  Created on: 7 cze 2020
 *      Author: Admin
 */

#ifndef STM32G4XX_HAL_DRIVER_INC_RING_H_
#define STM32G4XX_HAL_DRIVER_INC_RING_H_

#include "ucan_fd_protocol_stm32g431.h"

typedef enum{
    RING_IS_EMPTY,
    RING_IS_NOT_FULL,
    RING_IS_FULL
} Ring_status_type;

typedef struct {
#warning "use defined values"
    uint8_t data[32][MAX_CAN_FRAME_SIZE];
    uint8_t tail;
    uint8_t head;
    Ring_status_type status;
} Ring_type;

void RING_init(Ring_type *ring);
uint8_t RING_is_empty(Ring_type *ring);
uint8_t RING_is_full(Ring_type *ring);
void RING_put(Ring_type *ring, uint8_t *data, uint32_t len);
uint8_t* RING_get(Ring_type *ring);

#endif /* STM32G4XX_HAL_DRIVER_INC_RING_H_ */
