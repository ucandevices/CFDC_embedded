#!/bin/bash

/mnt/d/Programy/STMicroelectronics/STM32CubeProgrammer/bin/STM32_Programmer_CLI.exe -c port=usb1 -e all -d ./../bin/CFUC_0000.bin 0x08000000 -ob nBOOT0=1 -v -s
