/*
 * ucan_fd_protocol_stm32g431.c
 *
 *  Created on: Jun 3, 2020
 *      Author: Admin
 */


#include "ucan_fd_protocol_stm32g431.h"
#include "jump_to_boot.h"
Ring_type usb_rx;
Ring_type usb_tx;

uint8_t UCAN_execute_USB_to_CAN_frame(uint8_t *data){
    FDCAN_InitTypeDef init_values;

    if (data == NULL)
    	return 1;

	switch(data[0]) {
	case UCAN_FD_INIT:
        memcpy(data[1], &init_values, sizeof(FDCAN_InitTypeDef));
        //UCAN_Init(init_values);
        //add ACK to fifo.
	break;
    case UCAN_FD_DEINIT: 
        //UCAN_Deinit();
        //add ACK to fifo
    break;
    case UCAN_FD_TX:
    //todo: prepare frame and put it to fifo, send in main loop
    //add ACK to fifo
    break;
    case UCAN_FD_SAVE_CONFIG: 
    break;
    case UCAN_FD_GO_TO_BOOTLOADER: 
    //todo: send ack,

    	jump_to_boot();

    break;
    case UCAN_FD_GET_CAN_STATUS: 

    break;
    case UCAN_FD_RX: 
    //todo: read CAN, send ACK.
    break;
    case UCAN_FD_ACK: 

    break;
    
		default: break;
	}

    return 0;
}

uint8_t UCAN_execute_CAN_to_USB_frame(uint8_t *data, uint32_t len) {

	return 0;
}


