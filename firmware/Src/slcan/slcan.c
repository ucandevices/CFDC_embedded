/*
 * slcan_interface.c
 *
 *  Created on: Apr 2, 2016
 *      Author: Vostro1440
 */

#include "fdcan.h"
#include "string.h"
#include "slcan.h"
#include "usbd_cdc_if.h"

#define SLCAN_BELL 7
#define SLCAN_CR 13
#define SLCAN_LR 10


extern volatile int32_t serialNumber;
// internal slcan_interface state
static uint8_t state = STATE_CONFIG;
static uint8_t timestamping = 0;


static uint8_t terminator = SLCAN_CR;

extern FDCAN_HandleTypeDef hfdcan1;
static FDCAN_TxHeaderTypeDef can_tx_header;
static uint8_t can_tx_frame_data[64];

uint8_t sl_frame[32];
volatile uint8_t sl_frame_len=0;
/**
  * @brief  Adds data to send buffer
  * @param  c - data to add
  * @retval None
  */
static void slcanSetOutputChar(uint8_t c)
{
	if (sl_frame_len < sizeof(sl_frame))
	{
		sl_frame[sl_frame_len] = c;
		sl_frame_len ++;
	}
}

/**
  * @brief  Add given nible value as hexadecimal string to bufferr
  * @param  c - data to add
  * @retval None
  */
static void slCanSendNibble(uint8_t ch)
{
	ch = ch > 9 ? ch - 10 + 'A' : ch + '0';
	slcanSetOutputChar(ch);
}

/**
  * @brief  Add given byte value as hexadecimal string to buffer
  * @param  value - data to add
  * @retval None
  */
static void slcanSetOutputAsHex(uint8_t ch) {
	slCanSendNibble(ch >> 4);
	slCanSendNibble(ch & 0x0F);
}



/**
  * @brief  Flush data on active interface
  * @param  None
  * @retval None
  */
extern USBD_HandleTypeDef hUsbDeviceFS;


// frame buffer
//#define FRAME_BUFFER_SIZE 1024
//uint8_t frameBuffer[FRAME_BUFFER_SIZE];
//uint32_t dataToSend = 0;

void slcanClose()
{
	// HAL_NVIC_DisableIRQ(CEC_CAN_IRQn);
    HAL_FDCAN_Stop(&hfdcan1);
	state = STATE_CONFIG;
}

void slcanOutputFlush(void)
{
	if (sl_frame_len > 0)
	{
		{
            // check also CDC_Is_Busy() != USBD_BUSY
			while (((USBD_CDC_HandleTypeDef*)hUsbDeviceFS.pClassData)->TxState){;} //should change by hardware
			while (CDC_Transmit_FS(sl_frame, sl_frame_len) == USBD_BUSY);
		}
		sl_frame_len = 0;
	}

}

/**
  * @brief  Add to input buffer data from interfaces
  * @param  ch - data to add
  * @retval None
  */
uint8_t command[LINE_MAXLEN] = {0};

int slCanProccesInput(uint8_t ch)
{
	static uint8_t line[LINE_MAXLEN];
	static uint8_t linepos = 0;

    if (ch == SLCAN_CR) {
        line[linepos] = 0;
        memcpy(command,line,linepos);

        linepos = 0;
        return 1;
    } else if (ch != SLCAN_LR) {
        line[linepos] = ch;
        if (linepos < LINE_MAXLEN - 1) linepos++;
    }
    return 0;
}


/**
  * @brief  Parse hex value of given string
  * @param  canmsg - line Input string
  * 		len    - of characters to interpret
  * 		value  - Pointer to variable for the resulting decoded value
  * @retval 0 on error, 1 on success
  */
static uint8_t parseHex(uint8_t* line, uint8_t len, uint32_t* value) {
    *value = 0;
    while (len--) {
        if (*line == 0) return 0;
        *value <<= 4;
        if ((*line >= '0') && (*line <= '9')) {
           *value += *line - '0';
        } else if ((*line >= 'A') && (*line <= 'F')) {
           *value += *line - 'A' + 10;
        } else if ((*line >= 'a') && (*line <= 'f')) {
           *value += *line - 'a' + 10;
        } else return 0;
        line++;
    }
    return 1;
}

/**
 * @brief  Interprets given line and transmit can message
 * @param  line Line string which contains the transmit command
 * @retval HAL status
 */
static uint8_t transmitStd(uint8_t* line) {
    uint32_t temp;
    uint8_t idlen;
    HAL_StatusTypeDef tr;

    can_tx_header.IdType = FDCAN_STANDARD_ID;
    can_tx_header.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
    can_tx_header.MessageMarker = 0;

    if ((line[0] == 'r') || (line[0] == 'R'))
    {
    	can_tx_header.TxFrameType = FDCAN_REMOTE_FRAME;
    } else
    {
    	can_tx_header.TxFrameType = FDCAN_DATA_FRAME;
    }

    // upper case -> extended identifier
    if (line[0] < 'Z') {
    	idlen = 8;
        if (!parseHex(&line[1], idlen, &temp)) return 0;
        can_tx_header.IdType = FDCAN_EXTENDED_ID;
        can_tx_header.Identifier = temp;

    } else {
    	idlen = 3;
    	if (!parseHex(&line[1], idlen, &temp)) return 0;
		can_tx_header.IdType = FDCAN_STANDARD_ID;
		can_tx_header.Identifier = ((uint32_t)temp);
    }


    if (!parseHex(&line[1 + idlen], 1, &temp)) return 0;
    switch (temp)
        {
            case 8:
                can_tx_header.DataLength = FDCAN_DLC_BYTES_8;
                break;
            case 7:
                can_tx_header.DataLength = FDCAN_DLC_BYTES_7;
                break;
            case 6:
                can_tx_header.DataLength = FDCAN_DLC_BYTES_6;
                break;
            case 5:
                can_tx_header.DataLength = FDCAN_DLC_BYTES_5;
                break;
            case 4:
                can_tx_header.DataLength = FDCAN_DLC_BYTES_4;
                break;
            case 3:
                can_tx_header.DataLength = FDCAN_DLC_BYTES_3;
                break;
            case 2:
                can_tx_header.DataLength = FDCAN_DLC_BYTES_2;
                break;
            case 1:
                can_tx_header.DataLength = FDCAN_DLC_BYTES_1;
                break;
            default:
                can_tx_header.DataLength = FDCAN_DLC_BYTES_0;
                break;
        }
        
    if (can_tx_header.TxFrameType == FDCAN_DATA_FRAME) {
    	uint8_t i;
        uint8_t length = temp;
        if (length > 8) length = 8;
        for (i = 0; i < length; i++) {
            if (!parseHex(&line[idlen + 2 + i*2], 2, &temp)) return 0;
            can_tx_frame_data[i] = temp;
        }
    }

    tr = HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &(can_tx_header), can_tx_frame_data);
    return tr;
}

void slcanSetCANBaudRate(uint8_t baudrate)
{

            // NominalTimeSeg1Value = bt.phase_seg1 + bt.prop_seg
            // NominalTimeSeg2Value = bt.phase_seg2
            // NominalPrescalerValue = bt.brp
            // NominalSyncJumpWidthValue = bt.sjw

    hfdcan1.Init.ClockDivider = FDCAN_CLOCK_DIV1;
    hfdcan1.Init.NominalTimeSeg1 = 13;
	hfdcan1.Init.NominalTimeSeg2 = 2;
    switch (baudrate)
	{
		case CAN_BR_1M:
			hfdcan1.Init.NominalPrescaler = 9;
		break;
		case CAN_BR_500K:
			hfdcan1.Init.NominalPrescaler = 18;
		break;
		case CAN_BR_250K:
            hfdcan1.Init.NominalPrescaler = 36;
		break;
		case CAN_BR_125K:
			hfdcan1.Init.NominalPrescaler = 72;
		break;
		case CAN_BR_100K:
			hfdcan1.Init.NominalPrescaler = 90;
		break;
		case CAN_BR_50K:
			hfdcan1.Init.NominalPrescaler = 180;
		break;
		case CAN_BR_20K:
			hfdcan1.Init.NominalPrescaler = 320;
		break;
		case CAN_BR_10K:
            hfdcan1.Init.ClockDivider = FDCAN_CLOCK_DIV10;
            hfdcan1.Init.NominalTimeSeg1 = 8+7;
	        hfdcan1.Init.NominalTimeSeg2 = 7;
			hfdcan1.Init.NominalPrescaler = 60;
		break;
		case CAN_BR_83K:
            hfdcan1.Init.ClockDivider = FDCAN_CLOCK_DIV10;
            hfdcan1.Init.NominalTimeSeg1 = 1;
	        hfdcan1.Init.NominalTimeSeg2 = 1;
			hfdcan1.Init.NominalPrescaler = 29;
		break;

		default:
			break;
	}
}

void RebootToBootloader();
/**
 * @brief  Parse given command line
 * @param  line Line string to parse
 * @retval None
 */
uint8_t slCanCheckCommand(uint8_t *line)
{
	uint8_t result = SLCAN_BELL;
	if (line[0] == 0)
	{
		return 0;
	}
    switch (line[0]) {
    	case 'a':
    	{
    		if (terminator == SLCAN_CR)
    			terminator = SLCAN_LR;
    		else
    			terminator = SLCAN_CR;
    		result = terminator;
    		break;
    	}
        case 'S': // Setup with standard CAN bitrates
            if (state == STATE_CONFIG)
            {
                switch (line[1]) {
                    case '0': slcanSetCANBaudRate(CAN_BR_10K);  result = terminator; break;
                    case '1': slcanSetCANBaudRate(CAN_BR_20K);  result = terminator; break;
                    case '2': slcanSetCANBaudRate(CAN_BR_50K);  result = terminator; break;
                    case '3': slcanSetCANBaudRate(CAN_BR_100K); result = terminator; break;
                    case '4': slcanSetCANBaudRate(CAN_BR_125K); result = terminator; break;
                    case '5': slcanSetCANBaudRate(CAN_BR_250K); result = terminator; break;
                    case '6': slcanSetCANBaudRate(CAN_BR_500K); result = terminator; break;
                    case '7': slcanSetCANBaudRate(CAN_BR_800K); result = terminator; break;
                    case '8': slcanSetCANBaudRate(CAN_BR_1M);   result = terminator; break;
                    case '9': slcanSetCANBaudRate(CAN_BR_83K);   result = terminator; break;

                }
            }
            break;

        case 'G': // Read given MCP2515 register
        case 'W':
			result = terminator;
			break;

        case 's': // Setup with user defined timing settings for CNF1/CNF2/CNF3
            break;
        case 'V': // Get hardware version
            {

                slcanSetOutputChar('V');
                slcanSetOutputAsHex(VERSION_HARDWARE_MAJOR);
                slcanSetOutputAsHex(VERSION_HARDWARE_MINOR);
                result = terminator;
            }
            break;
        case 'v': // Get firmware version
            {

                slcanSetOutputChar('v');
                slcanSetOutputAsHex(VERSION_FIRMWARE_MAJOR);
                slcanSetOutputAsHex(VERSION_FIRMWARE_MINOR);
                result = terminator;
            }
            break;
        case 'N': // Get serial number
            {
                slcanSetOutputChar('N');
                slcanSetOutputAsHex((uint8_t)(serialNumber));
                slcanSetOutputAsHex((uint8_t)(serialNumber>>8));
                slcanSetOutputAsHex((uint8_t)(serialNumber>>16));
                slcanSetOutputAsHex((uint8_t)(serialNumber>>24));
                result = terminator;
            }
            break;
        case 'o':
        case 'O': // Open CAN channel
//            if (state == STATE_CONFIG)
            {
                hfdcan1.Init.Mode = FDCAN_MODE_NORMAL;
            
                MX_FDCAN1_Init();
            	{
					state = STATE_OPEN;
					result = terminator;
            	}
                HAL_FDCAN_Start(&hfdcan1);
            }
            break;
        case 'l': // Loop-back mode
//            if (state == STATE_CONFIG)
            {
            	hfdcan1.Init.Mode = FDCAN_MODE_INTERNAL_LOOPBACK;
                MX_FDCAN1_Init();
                {
                    state = STATE_OPEN;
                    result = terminator;
                }
                 HAL_FDCAN_Start(&hfdcan1);
            }
            break;
        case 'L': // Open CAN channel in listen-only mode
            //if (state == STATE_CONFIG)
            {
            	hfdcan1.Init.Mode = FDCAN_MODE_BUS_MONITORING;
            	MX_FDCAN1_Init();
                {
                    state = STATE_LISTEN;
                    result = terminator;
                }
                HAL_FDCAN_Start(&hfdcan1);
            }
            break;
        case 'C': // Close CAN channel
            slcanClose();
            break;
        case 'r': // Transmit standard RTR (11 bit) frame
        case 'R': // Transmit extended RTR (29 bit) frame
        case 't': // Transmit standard (11 bit) frame
        case 'T': // Transmit extended (29 bit) frame
            if (state == STATE_OPEN)
            {
                if (transmitStd(line) == HAL_OK) {
                    if (line[0] < 'Z') slcanSetOutputChar('Z');
                    else slcanSetOutputChar('z');
                    result = terminator;
                }
            }
            break;
        case 'F': // Read status flags
            {
                static FDCAN_ProtocolStatusTypeDef flags;
                HAL_FDCAN_GetProtocolStatus(&hfdcan1, &flags);
                uint8_t status = 0;
                if (flags.Warning) status |= 0x04; // error warning
                if (flags.LastErrorCode != FDCAN_PROTOCOL_ERROR_NONE) status |= 0x08; // data overrun
                if (flags.ErrorPassive) status |= 0x20; // passive error
                if (flags.BusOff) status |= 0x80; // bus error
                slcanSetOutputChar('F');
                slcanSetOutputAsHex(status);
                result = terminator;
            }
            break;
         case 'Z': // Set time stamping
            {
                unsigned long stamping;
                if (parseHex(&line[1], 1, &stamping)) {
                    timestamping = (stamping != 0);
                    result = terminator;
                }
            }
            break;
         case 'm': // Set accpetance filter mask
         case 'M': // Set accpetance filter code
            break;
         case 'b':
        	 if ((line[1] == 'o') && (line[2] == 'o') && (line[3] == 't')){
        		 line[0] = 0;
        		 line[1] = 0;
        		 line[2] = 0;
        		 line[3] = 0;
        		 reboot_into_bootloader();
        	 }
        	 break;

    }

   line[0] = 0;
   slcanSetOutputChar(result);
   slcanOutputFlush(); // Send ACK
   return 1;
}

/**
 * @brief  get slcan state
 * @param  none
 * @retval slcan state
 */
uint8_t slcan_getState()
{
	return state;
}

/**
 * @brief  reciving CAN frame
 * @param  canmsg Pointer to can message
 * 			step Current step
 * @retval Next character to print out
 */
uint8_t slcanReciveCanFrame(ucan_rx_can_def *pRxMsg)
{
	uint8_t i;
    
	// type
	if (pRxMsg->can_rx_header.IdType == FDCAN_EXTENDED_ID) {
		if (pRxMsg->can_rx_header.RxFrameType == FDCAN_REMOTE_FRAME)
		{
			slcanSetOutputChar('R');
		}
		else
		{
			slcanSetOutputChar('T');
		}
		// id
		for (i = 4; i != 0; i--)
		{
			slcanSetOutputAsHex(((uint8_t*)&pRxMsg->can_rx_header.Identifier)[i - 1]);
		}
	} else
	{
		if (pRxMsg->can_rx_header.RxFrameType == FDCAN_REMOTE_FRAME)
		{
			slcanSetOutputChar('r');
		}
		else
		{
			slcanSetOutputChar('t');
		}
		//id
		slCanSendNibble(((uint8_t*)&pRxMsg->can_rx_header.Identifier)[1] & 0x0F);
		slcanSetOutputAsHex(((uint8_t*)&pRxMsg->can_rx_header.Identifier)[0]);
	}
	// length
    uint8_t len = 0;
    switch (pRxMsg->can_rx_header.DataLength)
        {
            case FDCAN_DLC_BYTES_8:
                len = 8;
                break;
            case FDCAN_DLC_BYTES_7:
                len = 7;
                break;
            case FDCAN_DLC_BYTES_6:
                len = 6;
                break;
            case FDCAN_DLC_BYTES_5:
                len = 5;
                break;
            case FDCAN_DLC_BYTES_4:
                len = 4;
                break;
            case FDCAN_DLC_BYTES_3:
                len = 3;
                break;
            case FDCAN_DLC_BYTES_2:
                len = 2;
                break;
            case FDCAN_DLC_BYTES_1:
                len = 1;
                break;
            default:
                len = 0;
                break;
        }
	slCanSendNibble(len);

	//data
	if ((len > 0) && (pRxMsg->can_rx_header.RxFrameType != FDCAN_REMOTE_FRAME))
	{
		for (i = 0;  i != len; i ++)
		{
			slcanSetOutputAsHex(pRxMsg->can_data[i]);
		}
	}
	slcanSetOutputChar(terminator);
	slcanOutputFlush();
	return 0;
}