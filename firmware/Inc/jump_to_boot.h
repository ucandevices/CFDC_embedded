/*
 * jump_to_boot.h
 *
 *  Created on: 16 cze 2020
 *      Author: Admin
 */

#ifndef JUMP_TO_BOOT_H_
#define JUMP_TO_BOOT_H_

#include "main.h"

#define BOOTLOADER_ADDR 0x1FFF0000
#define APP_ADDR        0x08000000

typedef void (*pFunction)(void);

void jump_to_boot();

#endif /* JUMP_TO_BOOT_H_ */
