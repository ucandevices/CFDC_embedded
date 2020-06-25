/*
 * RING.c
 *
 *  Created on: 7 cze 2020
 *      Author: Admin
 */
#include "RING.h"

void RING_init(Ring_type *ring) {
    ring->tail = ring->head = 0;
    ring->status = RING_IS_EMPTY;
}

uint8_t RING_is_empty(Ring_type *ring){
    return (RING_IS_EMPTY == ring->status);
}

uint8_t RING_is_full(Ring_type *ring) {
    return (RING_IS_FULL == ring->status);
}

void RING_put(Ring_type *ring, uint8_t *data, uint32_t len) {
    if(RING_is_full(ring))
    	return;

    if(len > MAX_CAN_FRAME_SIZE)
    	return;

    memcpy(&ring->data[ring->head][0], data, len);
    if(len < MAX_CAN_FRAME_SIZE) {
        memset(&ring->data[ring->head][len], 1, MAX_CAN_FRAME_SIZE - len);
    }
    ring->head++;
    ring->status = RING_IS_NOT_FULL;
    if(ring->head >= UCAN_FRAME_RX_FIFO_SIZE){
        ring->head = 0;
    }
    
    if((ring->head + 1) % UCAN_FRAME_RX_FIFO_SIZE == ring->tail) {
        ring->status = RING_IS_FULL;
    }
}
uint8_t* RING_get(Ring_type *ring){
    uint8_t* retval = NULL;
    if(RING_is_empty(ring)) 
        return retval;

    retval = &ring->data[ring->tail][0];
    ring->tail++;
    if(ring->tail >= UCAN_FRAME_RX_FIFO_SIZE){
        ring->tail = 0;
    }
    if(ring->tail == ring->head) {
        ring->status = RING_IS_EMPTY;
    }

    return retval;
}
