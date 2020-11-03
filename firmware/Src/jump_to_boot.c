#include "stm32g4xx_hal.h"
#include "stm32g4xx_hal_flash_ex.h"
#include "stm32g4xx_hal_flash.h"
#include "usb_device.h"

//call this at any time to initiate a reboot into bootloader
void RebootToBootloader(){


    FLASH_OBProgramInitTypeDef OBParam;

    HAL_FLASHEx_OBGetConfig(&OBParam);

//    OBParam.OptionType = OPTIONBYTE_USER | OPTIONBYTE_BOOT_LOCK;
    OBParam.OptionType = OPTIONBYTE_USER;
    OBParam.USERType = OB_USER_nBOOT1 | OB_USER_nBOOT0 | OB_USER_nSWBOOT0;
    OBParam.USERConfig = OB_BOOT1_SYSTEM | OB_nBOOT0_RESET | OB_BOOT0_FROM_OB;
//    OBParam.BootEntryPoint = OB_BOOT_LOCK_DISABLE;

    HAL_FLASH_Unlock();
    HAL_FLASH_OB_Unlock();
    HAL_FLASHEx_OBProgram(&OBParam);
    HAL_FLASH_OB_Lock();
    HAL_FLASH_Lock();
    HAL_FLASH_OB_Launch();

    HAL_FLASHEx_OBGetConfig(&OBParam);

    HAL_NVIC_SystemReset();
}

//turns off BOOT0 pin
void TurnOffBoot0(){
//    FLASH_OBProgramInitTypeDef OBParam;
//
//    HAL_FLASHEx_OBGetConfig(&OBParam);
//
////    if((OBParam.BootEntryPoint & OB_BOOT_LOCK_ENABLE) == 0)
////    {
////    	OBParam.OptionType = OPTIONBYTE_BOOT_LOCK;
////        OBParam.BootEntryPoint = OB_BOOT_LOCK_ENABLE;
//
//    if (((OBParam.USERConfig & FLASH_OPTR_nBOOT0) == 0) ||
//    		((OBParam.USERConfig & FLASH_OPTR_nSWBOOT0) != 0))
//    {
//
//        OBParam.OptionType = OPTIONBYTE_USER;
//        OBParam.USERType = OB_USER_nBOOT0 | OB_USER_nSWBOOT0;
//        OBParam.USERConfig =  OB_nBOOT0_SET | OB_BOOT0_FROM_OB;
//
//        HAL_FLASH_Unlock();
//        HAL_FLASH_OB_Unlock();
//        HAL_FLASHEx_OBProgram(&OBParam);
//        HAL_FLASH_OB_Lock();
//        HAL_FLASH_OB_Launch();
//
//        HAL_FLASHEx_OBGetConfig(&OBParam);
//
////        HAL_NVIC_SystemReset();
//    }
}

