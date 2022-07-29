#!/bin/bash

/mnt/d/program/STM32Cube/bin/STM32_Programmer_CLI.exe -c port=usb1 -e all -d ./../bin/CFUC_0002.bin 0x08000000 -ob nSWBOOT0=0 nBOOT0=1 nBOOT1=0 -s
