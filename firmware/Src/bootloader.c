#include "stm32g4xx_hal.h"
#include "stm32g4xx_hal_flash_ex.h"
#include "stm32g4xx_hal_flash.h"
#include "usb_device.h"

/*
* @brief Initiate a reboot into bootloader
*/
void reboot_into_bootloader() 
{    
	__HAL_RCC_USB_CONFIG(0);

	uint32_t i=0;
	void (*SysMemBootJump)(void);

	/* Set the address of the entry point to bootloader */
	volatile uint32_t BootAddr = 0x1FFF0000;

	/* Disable all interrupts */
	__disable_irq();

	/* Disable Systick timer */
	SysTick->CTRL = 0;

	/* Set the clock to the default state */
	HAL_RCC_DeInit();

	/* Clear Interrupt Enable Register & Interrupt Pending Register */
	for (i=0;i<5;i++)
	{
		NVIC->ICER[i]=0xFFFFFFFF;
		NVIC->ICPR[i]=0xFFFFFFFF;
	}	

	/* Re-enable all interrupts */
	__enable_irq();

	/* Set up the jump to booloader address + 4 */
	SysMemBootJump = (void (*)(void)) (*((uint32_t *) ((BootAddr + 4))));

	/* Set the main stack pointer to the bootloader stack */
	__set_MSP(*(uint32_t *)BootAddr);

	/* Call the function to jump to bootloader location */
	SysMemBootJump(); 

	/* Jump is done successfully */
	while (1)
	{
		/* Code should never reach this loop */
	}
}