/*
 * jump_to_boot.c
 *
 *  Created on: 16 cze 2020
 *      Author: Admin
 */

#include "jump_to_boot.h"



	pFunction JumpToApplication;
	uint32_t JumpAddress;


void jump_to_boot() {

	HAL_RCC_DeInit();
	HAL_DeInit();

	JumpAddress = *(__IO uint32_t*) (BOOTLOADER_ADDR + 4);
	JumpToApplication = (pFunction) JumpAddress;

	__disable_irq();
	__HAL_SYSCFG_REMAPMEMORY_SYSTEMFLASH();
	__set_MSP(*(__IO uint32_t*) BOOTLOADER_ADDR);
	JumpToApplication();
}
