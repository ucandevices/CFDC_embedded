#include "stm32g4xx_hal.h"
#include "stm32g4xx_hal_flash_ex.h"
#include "stm32g4xx_hal_flash.h"
#include "usb_device.h"

#define BOOTLOADER_ADDR 0x1FFF0000
#define APP_ADDR        0x08000000

typedef void (*pFunction)(void);
//call this at any time to initiate a reboot into bootloader
pFunction JumpToApplication;

FLASH_OBProgramInitTypeDef OBParam;

void RebootToBootloader() {
	extern uint8_t gotoboot_flag;
	gotoboot_flag = 0;

	HAL_FLASHEx_OBGetConfig(&OBParam);
	OBParam.OptionType = OPTIONBYTE_USER;
	OBParam.USERType = OB_USER_nSWBOOT0 | OB_USER_nBOOT0 | OB_USER_nBOOT1;
	OBParam.USERConfig = OB_BOOT0_FROM_OB | OB_nBOOT0_RESET | OB_BOOT1_SYSTEM;

	HAL_FLASH_Unlock();
	HAL_FLASH_OB_Unlock();
	HAL_FLASHEx_OBProgram(&OBParam);
	HAL_FLASH_OB_Lock();
	HAL_FLASH_OB_Launch();

	HAL_RCC_DeInit();
	HAL_DeInit();

	uint32_t JumpAddress = *(__IO uint32_t*) (BOOTLOADER_ADDR + 4);
	JumpToApplication = (pFunction) JumpAddress;

	__disable_irq();
	__HAL_SYSCFG_REMAPMEMORY_SYSTEMFLASH();
	__set_MSP(*(__IO uint32_t*) BOOTLOADER_ADDR);
	JumpToApplication();

	HAL_NVIC_SystemReset();
}

//turns off BOOT0 pin
void TurnOffBoot0() {
	HAL_FLASHEx_OBGetConfig(&OBParam);

	OBParam.OptionType = OPTIONBYTE_USER;
	OBParam.USERType = OB_USER_nSWBOOT0 | OB_USER_nBOOT0 | OB_USER_nBOOT1;
	OBParam.USERConfig = OB_BOOT0_FROM_PIN | OB_nBOOT0_SET | OB_BOOT1_SYSTEM;

	HAL_FLASH_Unlock();
	HAL_FLASH_OB_Unlock();

	HAL_FLASHEx_OBProgram(&OBParam);
	HAL_FLASH_OB_Lock();
	HAL_FLASH_Lock();
	HAL_FLASH_OB_Launch();
}

