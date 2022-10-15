/**
  ******************************************************************************
  * @file    ucan_fd_protocol.h
  * @author  uCAN_Devices
  * @brief   uCAN_FD protocol definition for stm32g431
  ******************************************************************************
  */

#ifndef SRC_UCAN_FD_PROTOCOL_STM32G431_H_
#define SRC_UCAN_FD_PROTOCOL_STM32G431_H_

#include "main.h"
#include "stm32g4xx_hal_fdcan.h"
//#include "RING.h"


#define MAX_CAN_FRAME_SIZE (170u)
#define UCAN_SERIAL_NO_SIZE (8u)
#define UCAN_FRAME_RX_FIFO_SIZE (16u)
#define UCAN_FRAME_TX_FIFO_SIZE UCAN_FRAME_RX_FIFO_SIZE


/**
  * @brief List all Frames on CAN <-> USB protocol
  */

typedef enum {
	UCAN_FD_INIT, /*!< init CAN with all parameters, open in mode specified in init data. Frame direction USB->CAN*/
	UCAN_FD_DEINIT, /*!< deinit CAN, close CAN connection. Frame direction USB->CAN*/
	UCAN_FD_TX, /*!< send new frame on CAN network. Frame direction USB->CAN  */
	UCAN_FD_SAVE_CONFIG, /*!< saves CAN config to NVM USB->CAN*/
	UCAN_FD_GO_TO_BOOTLOADER, /*!< go to USB bootloader USB->CAN*/
	UCAN_FD_GET_CAN_STATUS, /*!< request status USB->CAN*/
	UCAN_FD_RX, /*!< new CAN frame received on network. Frame direction CAN->USB*/
	UCAN_FD_ACK, /*!< gets CAN status from CONVERTER. Also ACK resposne for all frames form USB. Frame direction CAN->USB */
	UCAN_FD_LAST, /*iterator should be last*/

	FT_ENUM_SIZE_GUARD = 0xFFFFFFFF
} UCAN_FRAME_TYPE;


typedef enum {
	UCAN_FD_COMMAND_OK, /*!< command was executed successfully USB->CAN*/
	UCAN_FD_COMMAND_ERROR, /*!< command was not executed see error code*/
	UCAN_FD_COMMAND_WRONG_PARAM, /*!< wrong param */
	CS_ENUM_SIZE_GUARD = 0xFFFFFFFF
} UCAN_FRAME_CMD_STATUS;

typedef enum {
	UCAN_CAN_FD,
	UCAN_CAN_HS,
	UCAN_LIN,
	DT_ENUM_SIZE_GUARD = 0xFFFFFFFF
} UCAN_DEV_TYPE;



/**
  * @brief Device version and serial number
  */
typedef struct{
	uint8_t sw_version; /*!< software version*/
	uint8_t hw_version; /*!< hardware version */
	UCAN_DEV_TYPE dev_type; /*!< device type */
	uint8_t serial_number[UCAN_SERIAL_NO_SIZE]; /*!< device serial number */
}FDCAN_Device_DescritionDef;


/**
  * @brief UCAN_FD_INIT frame structure
  */
typedef struct {
	UCAN_FRAME_TYPE frame_type;  /*!< Frame type is @ref UCAN_FD_INIT.*/
	FDCAN_InitTypeDef can_init; /*!< FDCAN Init structure definition @ref FDCAN_InitTypeDef.*/
} UCAN_InitFrameDef;

/**
  * @brief UCAN_FD_DEINIT frame structure
  */
typedef struct {
	UCAN_FRAME_TYPE frame_type; /*!< Frame type is @ref UCAN_FD_DEINIT.*/
} UCAN_DeinitFrameDef;

/**
  * @brief UCAN_FD_TX frame structure
  */
typedef struct {
	UCAN_FRAME_TYPE frame_type; /*!< Frame type is @ref UCAN_FD_TX.*/
	FDCAN_TxHeaderTypeDef can_tx_header; /*!< FDCAN Tx event FIFO structure definition @ref FDCAN_TxHeaderTypeDef.*/
	uint8_t can_data[64]; /* Data CAN buffer */
} UCAN_TxFrameDef;

/**
  * @brief UCAN_FD_SAVE_CONFIG frame structure
  */
typedef struct {
	UCAN_FRAME_TYPE frame_type;  /*!< Frame type is @ref UCAN_FD_SAVE_CONFIG.*/
} UCAN_SaveConfigFrameDef;

/**
  * @brief UCAN_FD_GO_TO_BOOTLOADER frame structure
  */
typedef struct {
	UCAN_FRAME_TYPE frame_type;  /*!< Frame type is @ref UCAN_FD_GO_TO_BOOTLOADER.*/
} UCAN_GoToBootladerFrameDef;

/**
  * @brief UCAN_FD_GET_CAN_STATUS frame structure
  */
typedef struct {
	UCAN_FRAME_TYPE frame_type;  /*!< Frame type is @ref UCAN_FD_GET_CAN_STATUS.*/
} UCAN_Get_CAN_Status;

/**
  * @brief UCAN_FD_RX frame structure
  */
#define UCAN_RX_FRAME_DEF_CAN_COUNT_MAX 10u

typedef struct {
	FDCAN_RxHeaderTypeDef can_rx_header; /*!< FDCAN Rx header structure definition @ref FDCAN_RxHeaderTypeDef.*/
	uint8_t can_data[64]; /* Data CAN buffer */
	uint32_t packed_flags_and_error_counters;
} ucan_rx_can_def;

typedef struct {
	UCAN_FRAME_TYPE frame_type; /*!< Frame type is @ref UCAN_FD_RX.*/
	uint32_t can_frame_count;
	ucan_rx_can_def can_frame[UCAN_RX_FRAME_DEF_CAN_COUNT_MAX];
} UCAN_RxFrameDef;

/**
  * @brief UCAN_FD_ACK frame structure
  */
typedef struct {
	UCAN_FRAME_TYPE frame_type; /*!< Frame type is @ref UCAN_FD_GET_STATUS.*/
	UCAN_FRAME_CMD_STATUS cmd_status; /*!< Last command status @ref UCAN_FD_GET_STATUS.*/
	FDCAN_ProtocolStatusTypeDef can_protocol_status; /* FDCAN Protocol Status structure definition @ref FDCAN_ProtocolStatusTypeDef*/
	FDCAN_ErrorCountersTypeDef can_error_counters; /* FDCAN Error Counters structure definition @ref FDCAN_ErrorCountersTypeDef*/
	FDCAN_InitTypeDef can_init_structure; /*!< FDCAN Init structure definition @ref FDCAN_InitTypeDef.*/
	FDCAN_Device_DescritionDef dev_desc; /*< Holds Device description SW/HW version ID. */
} UCAN_AckFrameDef;

uint8_t UCAN_execute_USB_to_CAN_frame(uint8_t *data);
uint8_t UCAN_execute_CAN_to_USB_frame(uint8_t *data, uint32_t len);
uint32_t UCAN_get_frame_size(UCAN_FRAME_TYPE ucan_frame);

#endif /* SRC_UCAN_FD_PROTOCOL_STM32G431_H_ */
