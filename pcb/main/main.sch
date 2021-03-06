EESchema Schematic File Version 4
LIBS:main-cache
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Interface_CAN_LIN:MCP2542FDxMF U2
U 1 1 5D4AC5F1
P 1850 6250
F 0 "U2" H 1500 6600 50  0000 C CNN
F 1 "MCP2542FDxMF" H 2200 5850 50  0000 C CNN
F 2 "Housings_DFN_QFN:DFN-8-1EP_3x3mm_Pitch0.65mm" H 1850 5750 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/MCP2542FD-4FD-MCP2542WFD-4WFD-Data-Sheet20005514B.pdf" H 1850 6250 50  0001 C CNN
F 4 "https://octopart.com/mcp2542fdt-e%2Fmf-microchip-67312997?r=sp&s=23YyJb1rSaa9LVovInAklQ" H 1850 6250 50  0001 C CNN "1st Disrtib Link"
F 5 "Microchip" H 1850 6250 50  0001 C CNN "Manufacturer"
	1    1850 6250
	1    0    0    -1  
$EndComp
$Comp
L Connector:USB_B_Micro J1
U 1 1 5D4ACCF3
P 1300 2700
F 0 "J1" H 1070 2689 50  0000 R CNN
F 1 "USBMCS1B5W" H 1070 2598 50  0000 R CNN
F 2 "ucan_custom:USBMCS1B5W" H 1450 2650 50  0001 C CNN
F 3 "https://www.maritex.com.pl/product/attachment/37540/USBMCS1B5W-1.pdf" H 1450 2650 50  0001 C CNN
F 4 "https://www.maritex.com.pl/zlacza/zlacza_usb_hdmi_ieee/zlacza_i_kable_usb/zlacza_mini_i_micro_usb/usbmcs1b5w1.html" H 1300 2700 50  0001 C CNN "1st Disrtib Link"
F 5 "WELLCO" H 1300 2700 50  0001 C CNN "Manufacturer"
	1    1300 2700
	1    0    0    -1  
$EndComp
$Comp
L Power_Protection:USBLC6-2SC6 U3
U 1 1 5D4AD7C2
P 2500 2700
F 0 "U3" V 2100 2350 50  0000 L CNN
F 1 "USBLC6-2SC6" V 2850 2000 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23-6" H 1750 3100 50  0001 C CNN
F 3 "http://www2.st.com/resource/en/datasheet/CD00050750.pdf" H 2700 3050 50  0001 C CNN
F 4 "https://octopart.com/usblc6-2sc6-stmicroelectronics-39666276?r=sp" H 2500 2700 50  0001 C CNN "1st Disrtib Link"
F 5 "STMicroelectronics" H 2500 2700 50  0001 C CNN "Manufacturer"
	1    2500 2700
	0    -1   1    0   
$EndComp
$Comp
L Power_Protection:NUP2105L D1
U 1 1 5D4AF9F4
P 3500 6900
F 0 "D1" H 3650 7050 50  0000 L CNN
F 1 "PESD2CAN" H 3550 6750 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 3725 6850 50  0001 L CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/PESD2CAN.pdf" H 3625 7025 50  0001 C CNN
F 4 "https://octopart.com/pesd2can%2C215-nexperia-78741113?r=sp" H 3500 6900 50  0001 C CNN "1st Disrtib Link"
F 5 "Nexperia" H 3500 6900 50  0001 C CNN "Manufacturer"
	1    3500 6900
	1    0    0    -1  
$EndComp
Text GLabel 1350 6050 0    50   Input ~ 0
CAN_TX
Text GLabel 1350 6150 0    50   Input ~ 0
CAN_RX
Text GLabel 1350 6450 0    50   Input ~ 0
CAN_STBY
$Comp
L Connector:Screw_Terminal_01x03 J2
U 1 1 5D4B1563
P 4250 6350
F 0 "J2" H 4330 6392 50  0000 L CNN
F 1 "Screw_Terminal_01x03/3,5" H 4330 6301 50  0000 L CNN
F 2 "TerminalBlocks_Phoenix:TerminalBlock_Phoenix_PT-3.5mm_3pol" H 4250 6350 50  0001 C CNN
F 3 "https://www.maritex.com.pl/product/attachment/38073/tbx350xs.pdf" H 4250 6350 50  0001 C CNN
F 4 "https://www.maritex.com.pl/zlacza/listwy_zaciskowe/listwy_zaciskowe_standard_nierozlaczalne/listwy_zaciskowe_pionowe_z_ruchoma_oslona_przewodu_w_rastrze_3_50mm/tbx3503s-lf.html" H 4250 6350 50  0001 C CNN "1st Disrtib Link"
F 5 "XINYA" H 4250 6350 50  0001 C CNN "Manufacturer"
	1    4250 6350
	1    0    0    1   
$EndComp
$Comp
L power:+3V3 #PWR0101
U 1 1 5D4B28D6
P 1750 5550
F 0 "#PWR0101" H 1750 5400 50  0001 C CNN
F 1 "+3V3" H 1765 5723 50  0000 C CNN
F 2 "" H 1750 5550 50  0001 C CNN
F 3 "" H 1750 5550 50  0001 C CNN
	1    1750 5550
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0102
U 1 1 5D4B2F36
P 2000 2600
F 0 "#PWR0102" H 2000 2450 50  0001 C CNN
F 1 "+5V" H 2015 2773 50  0000 C CNN
F 2 "" H 2000 2600 50  0001 C CNN
F 3 "" H 2000 2600 50  0001 C CNN
	1    2000 2600
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR0103
U 1 1 5D4B3DE3
P 1850 6650
F 0 "#PWR0103" H 1850 6400 50  0001 C CNN
F 1 "GND" H 1855 6477 50  0000 C CNN
F 2 "" H 1850 6650 50  0001 C CNN
F 3 "" H 1850 6650 50  0001 C CNN
	1    1850 6650
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0104
U 1 1 5D4B963B
P 1600 2000
F 0 "#PWR0104" H 1600 1850 50  0001 C CNN
F 1 "+5V" H 1615 2173 50  0000 C CNN
F 2 "" H 1600 2000 50  0001 C CNN
F 3 "" H 1600 2000 50  0001 C CNN
	1    1600 2000
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1600 2700 1750 2700
Wire Wire Line
	1750 2700 1750 2200
Wire Wire Line
	2000 2600 2000 2700
Wire Wire Line
	1750 3200 1750 2800
Wire Wire Line
	1750 2800 1600 2800
$Comp
L power:GND #PWR0105
U 1 1 5D4BC768
P 3000 2700
F 0 "#PWR0105" H 3000 2450 50  0001 C CNN
F 1 "GND" H 3005 2527 50  0000 C CNN
F 2 "" H 3000 2700 50  0001 C CNN
F 3 "" H 3000 2700 50  0001 C CNN
	1    3000 2700
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR0106
U 1 1 5D4BCC02
P 1600 3150
F 0 "#PWR0106" H 1600 2900 50  0001 C CNN
F 1 "GND" H 1605 2977 50  0000 C CNN
F 2 "" H 1600 3150 50  0001 C CNN
F 3 "" H 1600 3150 50  0001 C CNN
	1    1600 3150
	-1   0    0    -1  
$EndComp
$Comp
L Regulator_Linear:MCP1700-3302E_SOT23 U1
U 1 1 5D4BD7B6
P 1750 1050
F 0 "U1" H 1550 1200 50  0000 C CNN
F 1 "MCP1700-3302E_SOT23" H 2300 700 50  0000 C CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 1750 1275 50  0001 C CNN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/20001826D.pdf" H 1750 1050 50  0001 C CNN
F 4 "https://octopart.com/mcp1703at-3302e%2Fcb-microchip-22267476?r=sp" H 1750 1050 50  0001 C CNN "1st Disrtib Link"
F 5 "Microchip" H 1750 1050 50  0001 C CNN "Manufacturer"
	1    1750 1050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0107
U 1 1 5D4C4FBB
P 1750 1350
F 0 "#PWR0107" H 1750 1100 50  0001 C CNN
F 1 "GND" H 1755 1177 50  0000 C CNN
F 2 "" H 1750 1350 50  0001 C CNN
F 3 "" H 1750 1350 50  0001 C CNN
	1    1750 1350
	-1   0    0    -1  
$EndComp
$Comp
L Device:C_Small C1
U 1 1 5D4C5E0F
P 1250 1150
F 0 "C1" H 1342 1196 50  0000 L CNN
F 1 "1u" H 1342 1105 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 1250 1150 50  0001 C CNN
F 3 "~" H 1250 1150 50  0001 C CNN
	1    1250 1150
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C4
U 1 1 5D4C637B
P 2050 1150
F 0 "C4" H 2142 1196 50  0000 L CNN
F 1 "1u" H 2142 1105 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 2050 1150 50  0001 C CNN
F 3 "~" H 2050 1150 50  0001 C CNN
	1    2050 1150
	1    0    0    -1  
$EndComp
Wire Wire Line
	1250 1050 1450 1050
Wire Wire Line
	1750 1350 1250 1350
Wire Wire Line
	1250 1350 1250 1250
Wire Wire Line
	1750 1350 2050 1350
Wire Wire Line
	2050 1350 2050 1250
Connection ~ 1750 1350
$Comp
L power:+5V #PWR0108
U 1 1 5D4C8721
P 1250 950
F 0 "#PWR0108" H 1250 800 50  0001 C CNN
F 1 "+5V" H 1265 1123 50  0000 C CNN
F 2 "" H 1250 950 50  0001 C CNN
F 3 "" H 1250 950 50  0001 C CNN
	1    1250 950 
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1250 950  1250 1050
Connection ~ 1250 1050
$Comp
L power:+3V3 #PWR0109
U 1 1 5D4C90B3
P 2050 950
F 0 "#PWR0109" H 2050 800 50  0001 C CNN
F 1 "+3V3" H 2065 1123 50  0000 C CNN
F 2 "" H 2050 950 50  0001 C CNN
F 3 "" H 2050 950 50  0001 C CNN
	1    2050 950 
	1    0    0    -1  
$EndComp
Wire Wire Line
	2050 950  2050 1050
Connection ~ 2050 1050
$Comp
L Device:C_Small C3
U 1 1 5D4E523D
P 2100 5700
F 0 "C3" V 2329 5700 50  0000 C CNN
F 1 "100n" V 2238 5700 50  0000 C CNN
F 2 "Capacitors_SMD:C_0603" H 2100 5700 50  0001 C CNN
F 3 "~" H 2100 5700 50  0001 C CNN
	1    2100 5700
	0    -1   -1   0   
$EndComp
$Comp
L Device:C_Small C2
U 1 1 5D4E5EA7
P 1450 5700
F 0 "C2" V 1679 5700 50  0000 C CNN
F 1 "100n" V 1588 5700 50  0000 C CNN
F 2 "Capacitors_SMD:C_0603" H 1450 5700 50  0001 C CNN
F 3 "~" H 1450 5700 50  0001 C CNN
	1    1450 5700
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1550 5700 1750 5700
Wire Wire Line
	1750 5700 1750 5850
Connection ~ 1750 5700
Wire Wire Line
	1850 5850 1850 5700
Wire Wire Line
	1850 5700 1950 5700
$Comp
L power:+5V #PWR0112
U 1 1 5D4E9E5F
P 1950 5450
F 0 "#PWR0112" H 1950 5300 50  0001 C CNN
F 1 "+5V" H 1965 5623 50  0000 C CNN
F 2 "" H 1950 5450 50  0001 C CNN
F 3 "" H 1950 5450 50  0001 C CNN
	1    1950 5450
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1950 5450 1950 5700
Connection ~ 1950 5700
Wire Wire Line
	1950 5700 2000 5700
Wire Wire Line
	1750 5700 1750 5550
$Comp
L power:GND #PWR0113
U 1 1 5D4EC7DF
P 2200 5700
F 0 "#PWR0113" H 2200 5450 50  0001 C CNN
F 1 "GND" V 2205 5572 50  0000 R CNN
F 2 "" H 2200 5700 50  0001 C CNN
F 3 "" H 2200 5700 50  0001 C CNN
	1    2200 5700
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR0114
U 1 1 5D4ED209
P 1350 5700
F 0 "#PWR0114" H 1350 5450 50  0001 C CNN
F 1 "GND" V 1355 5572 50  0000 R CNN
F 2 "" H 1350 5700 50  0001 C CNN
F 3 "" H 1350 5700 50  0001 C CNN
	1    1350 5700
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small_US R2
U 1 1 5D4F04D7
P 2850 6350
F 0 "R2" H 2782 6304 50  0000 R CNN
F 1 "120" H 2782 6395 50  0000 R CNN
F 2 "Resistors_SMD:R_0603" H 2850 6350 50  0001 C CNN
F 3 "~" H 2850 6350 50  0001 C CNN
	1    2850 6350
	-1   0    0    1   
$EndComp
Wire Wire Line
	2850 5950 2850 6050
Wire Wire Line
	2350 6150 2450 6150
Wire Wire Line
	2450 6150 2450 5950
Wire Wire Line
	2450 5950 2850 5950
Connection ~ 2850 5950
Wire Wire Line
	2350 6350 2450 6350
Wire Wire Line
	2450 6350 2450 6550
Wire Wire Line
	2450 6550 2850 6550
Wire Wire Line
	2850 6450 2850 6550
Connection ~ 2850 6550
$Comp
L power:GND #PWR0116
U 1 1 5D50AE78
P 4050 7150
F 0 "#PWR0116" H 4050 6900 50  0001 C CNN
F 1 "GND" H 4055 6977 50  0000 C CNN
F 2 "" H 4050 7150 50  0001 C CNN
F 3 "" H 4050 7150 50  0001 C CNN
	1    4050 7150
	1    0    0    -1  
$EndComp
Wire Wire Line
	4050 6450 4050 7100
Wire Wire Line
	4050 7100 4050 7150
Connection ~ 4050 7100
Wire Wire Line
	8700 1400 8700 1300
Wire Wire Line
	9550 1300 9950 1300
Connection ~ 9550 1300
Wire Wire Line
	9150 1300 9550 1300
Connection ~ 9150 1300
Wire Wire Line
	8700 1300 9150 1300
Connection ~ 8700 1300
Wire Wire Line
	8350 1300 8700 1300
Connection ~ 8350 1300
Wire Wire Line
	7950 1300 8350 1300
Connection ~ 7950 1300
Wire Wire Line
	7550 1300 7950 1300
Wire Wire Line
	9550 1100 9950 1100
Connection ~ 8350 1100
Wire Wire Line
	8350 1100 8700 1100
$Comp
L power:GND #PWR0117
U 1 1 5D4DC1E5
P 8700 1400
F 0 "#PWR0117" H 8700 1150 50  0001 C CNN
F 1 "GND" H 8705 1227 50  0000 C CNN
F 2 "" H 8700 1400 50  0001 C CNN
F 3 "" H 8700 1400 50  0001 C CNN
	1    8700 1400
	-1   0    0    -1  
$EndComp
Wire Wire Line
	7550 1100 7950 1100
$Comp
L Device:C_Small C10
U 1 1 5D4D86A5
P 9150 1200
F 0 "C10" H 9058 1154 50  0000 R CNN
F 1 "1u" H 9058 1245 50  0000 R CNN
F 2 "Capacitors_SMD:C_0603" H 9150 1200 50  0001 C CNN
F 3 "~" H 9150 1200 50  0001 C CNN
	1    9150 1200
	-1   0    0    1   
$EndComp
$Comp
L Device:C_Small C8
U 1 1 5D4D66DA
P 8350 1200
F 0 "C8" H 8442 1246 50  0000 L CNN
F 1 "10u" H 8442 1155 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 8350 1200 50  0001 C CNN
F 3 "~" H 8350 1200 50  0001 C CNN
	1    8350 1200
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C9
U 1 1 5D4D633C
P 8700 1200
F 0 "C9" H 8608 1154 50  0000 R CNN
F 1 "100n" H 8608 1245 50  0000 R CNN
F 2 "Capacitors_SMD:C_0603" H 8700 1200 50  0001 C CNN
F 3 "~" H 8700 1200 50  0001 C CNN
	1    8700 1200
	-1   0    0    1   
$EndComp
$Comp
L Device:C_Small C7
U 1 1 5D4D5C7E
P 7950 1200
F 0 "C7" H 7858 1154 50  0000 R CNN
F 1 "10u" H 7858 1245 50  0000 R CNN
F 2 "Capacitors_SMD:C_0603" H 7950 1200 50  0001 C CNN
F 3 "~" H 7950 1200 50  0001 C CNN
	1    7950 1200
	-1   0    0    1   
$EndComp
$Comp
L Device:C_Small C6
U 1 1 5D4D5901
P 7550 1200
F 0 "C6" H 7458 1154 50  0000 R CNN
F 1 "100n" H 7458 1245 50  0000 R CNN
F 2 "Capacitors_SMD:C_0603" H 7550 1200 50  0001 C CNN
F 3 "~" H 7550 1200 50  0001 C CNN
	1    7550 1200
	-1   0    0    1   
$EndComp
$Comp
L Device:C_Small C12
U 1 1 5D4D3DFC
P 9950 1200
F 0 "C12" H 9858 1154 50  0000 R CNN
F 1 "4,7u" H 9858 1245 50  0000 R CNN
F 2 "Capacitors_SMD:C_0603" H 9950 1200 50  0001 C CNN
F 3 "~" H 9950 1200 50  0001 C CNN
	1    9950 1200
	-1   0    0    1   
$EndComp
$Comp
L Device:C_Small C11
U 1 1 5D4C5A98
P 9550 1200
F 0 "C11" H 9458 1154 50  0000 R CNN
F 1 "100n" H 9458 1245 50  0000 R CNN
F 2 "Capacitors_SMD:C_0603" H 9550 1200 50  0001 C CNN
F 3 "~" H 9550 1200 50  0001 C CNN
	1    9550 1200
	-1   0    0    1   
$EndComp
$Comp
L power:+3V3 #PWR0118
U 1 1 5D53DCBC
P 4450 1900
F 0 "#PWR0118" H 4450 1750 50  0001 C CNN
F 1 "+3V3" H 4465 2073 50  0000 C CNN
F 2 "" H 4450 1900 50  0001 C CNN
F 3 "" H 4450 1900 50  0001 C CNN
	1    4450 1900
	1    0    0    -1  
$EndComp
Wire Wire Line
	7950 1100 8350 1100
Connection ~ 7950 1100
Wire Wire Line
	8700 1100 9150 1100
Connection ~ 8700 1100
Connection ~ 9550 1100
Connection ~ 9150 1100
Wire Wire Line
	9150 1100 9550 1100
$Comp
L power:+3V3 #PWR0119
U 1 1 5D54647E
P 8700 950
F 0 "#PWR0119" H 8700 800 50  0001 C CNN
F 1 "+3V3" H 8715 1123 50  0000 C CNN
F 2 "" H 8700 950 50  0001 C CNN
F 3 "" H 8700 950 50  0001 C CNN
	1    8700 950 
	1    0    0    -1  
$EndComp
Wire Wire Line
	8700 950  8700 1100
Text GLabel 9150 3850 0    50   Input ~ 0
SW_CLK
Text GLabel 9350 4050 0    50   Input ~ 0
SW_DIO
Text GLabel 9150 3750 0    50   Input ~ 0
RESET
$Comp
L power:GND #PWR0120
U 1 1 5D54BE5C
P 9100 3950
F 0 "#PWR0120" H 9100 3700 50  0001 C CNN
F 1 "GND" H 9105 3777 50  0000 C CNN
F 2 "" H 9100 3950 50  0001 C CNN
F 3 "" H 9100 3950 50  0001 C CNN
	1    9100 3950
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR0122
U 1 1 5D5530EA
P 4050 2150
F 0 "#PWR0122" H 4050 1900 50  0001 C CNN
F 1 "GND" H 4055 1977 50  0000 C CNN
F 2 "" H 4050 2150 50  0001 C CNN
F 3 "" H 4050 2150 50  0001 C CNN
	1    4050 2150
	0    1    -1   0   
$EndComp
Text GLabel 4050 2900 0    50   Input ~ 0
RESET
Text GLabel 5650 1900 1    50   Input ~ 0
SW_CLK
Text GLabel 6250 2300 2    50   Input ~ 0
SW_DIO
Text GLabel 2750 3200 2    50   Input ~ 0
USB_DM
Wire Wire Line
	2600 3200 2750 3200
Text GLabel 2700 2200 2    50   Input ~ 0
USB_DP
Wire Wire Line
	2700 2200 2600 2200
Text GLabel 4650 1900 1    50   Input ~ 0
CAN_TX
Text GLabel 4750 1900 1    50   Input ~ 0
CAN_RX
$Comp
L Device:LED D2
U 1 1 5D55A37D
P 5200 1450
F 0 "D2" H 5193 1195 50  0000 C CNN
F 1 "LED" H 5193 1286 50  0000 C CNN
F 2 "LEDs:LED_0603" H 5200 1450 50  0001 C CNN
F 3 "~" H 5200 1450 50  0001 C CNN
F 4 "https://www.maritex.com.pl/led/diody_led_smd/diody_led_0603/diody_led_smd_0603_standardowej_jasnosci/led0603-gyw120-h.html" H 5200 1450 50  0001 C CNN "1st Disrtib Link"
	1    5200 1450
	-1   0    0    1   
$EndComp
$Comp
L Device:R_Small_US R3
U 1 1 5D55B428
P 5050 1800
F 0 "R3" V 5150 1800 50  0000 C CNN
F 1 "1k" V 4950 1800 50  0000 C CNN
F 2 "Resistors_SMD:R_0603" H 5050 1800 50  0001 C CNN
F 3 "~" H 5050 1800 50  0001 C CNN
	1    5050 1800
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR0123
U 1 1 5D55D639
P 5350 1450
F 0 "#PWR0123" H 5350 1200 50  0001 C CNN
F 1 "GND" H 5355 1277 50  0000 C CNN
F 2 "" H 5350 1450 50  0001 C CNN
F 3 "" H 5350 1450 50  0001 C CNN
	1    5350 1450
	-1   0    0    -1  
$EndComp
Wire Wire Line
	2850 6550 3400 6550
Wire Wire Line
	3800 6250 4050 6250
Wire Wire Line
	3950 5950 3950 6350
Wire Wire Line
	3950 6350 4050 6350
$Comp
L Connector:Conn_01x04_Male J4
U 1 1 5D4F331E
P 1100 3700
F 0 "J4" H 1208 3889 50  0000 C CNN
F 1 "Conn_01x04_Male" H 1208 3890 50  0001 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_2x02_Pitch1.27mm" H 1100 3700 50  0001 C CNN
F 3 "~" H 1100 3700 50  0001 C CNN
	1    1100 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	1300 3600 1400 3600
$Comp
L power:GND #PWR0125
U 1 1 5D4F8EAC
P 1700 3800
F 0 "#PWR0125" H 1700 3550 50  0001 C CNN
F 1 "GND" H 1705 3627 50  0000 C CNN
F 2 "" H 1700 3800 50  0001 C CNN
F 3 "" H 1700 3800 50  0001 C CNN
	1    1700 3800
	0    -1   1    0   
$EndComp
Text GLabel 1800 2700 2    50   Input ~ 0
D+
Text GLabel 1800 2800 2    50   Input ~ 0
D-
Wire Wire Line
	1800 2800 1750 2800
Connection ~ 1750 2800
Wire Wire Line
	1750 2700 1800 2700
Connection ~ 1750 2700
Text GLabel 1700 3600 2    50   Input ~ 0
D+
Text GLabel 1700 3700 2    50   Input ~ 0
D-
Wire Wire Line
	1400 3700 1300 3700
Wire Wire Line
	9150 3750 9500 3750
Wire Wire Line
	9350 4050 9500 4050
Wire Wire Line
	9100 3950 9500 3950
$Comp
L Connector:Conn_01x02_Female J5
U 1 1 5D65410E
P 3050 6050
F 0 "J5" H 3078 5980 50  0000 L CNN
F 1 "Conn_01x02_Female" H 3078 5935 50  0001 L CNN
F 2 "Pin_Header_Straight_1x02_Pitch2.54mm" H 3050 6050 50  0001 C CNN
F 3 "~" H 3050 6050 50  0001 C CNN
F 4 "https://www.maritex.com.pl/zlacza/listwy_stykowe/listwy_w_rastrze_2_54mm/listwy_kolkowe_proste_jednorzedowe_w_rastrze_2_54mm/pls02su.html" H 3050 6050 50  0001 C CNN "1st Disrtib Link"
	1    3050 6050
	1    0    0    -1  
$EndComp
Wire Wire Line
	2850 6150 2850 6250
Wire Wire Line
	1200 3100 1300 3100
Wire Wire Line
	1300 3100 1600 3100
Wire Wire Line
	1600 3100 1600 3150
Connection ~ 1300 3100
Wire Wire Line
	2400 2200 1750 2200
Wire Wire Line
	2400 3200 1750 3200
Text GLabel 6250 2500 2    50   Input ~ 0
USB_DP
Text GLabel 6250 2600 2    50   Input ~ 0
USB_DM
$Comp
L Device:L_Core_Ferrite_Small L1
U 1 1 5D759A2E
P 1600 2100
F 0 "L1" H 1556 2054 50  0000 R CNN
F 1 "BLM18TG601TN1D" H 1556 2145 50  0000 R CNN
F 2 "Resistors_SMD:R_0603" H 1600 2100 50  0001 C CNN
F 3 "https://octopart.com/blm18tg601tn1d-murata-5405438?r=sp&s=IUm1s-ppRWC8jOS_8ERnwA" H 1600 2100 50  0001 C CNN
F 4 "https://octopart.com/blm18tg601tn1d-murata-5405438?r=sp&s=IUm1s-ppRWC8jOS_8ERnwA" H 1600 2100 50  0001 C CNN "1st Disrtib Link"
	1    1600 2100
	-1   0    0    1   
$EndComp
Wire Wire Line
	1600 2200 1600 2500
Text GLabel 1650 2500 2    50   Input ~ 0
VB_N
Wire Wire Line
	1650 2500 1600 2500
Connection ~ 1600 2500
Text GLabel 1700 3900 2    50   Input ~ 0
VB_N
$Comp
L cfuc:STM32G431CBUx U4
U 1 1 5DBB910B
P 4300 2450
F 0 "U4" H 4300 2900 50  0000 L CNN
F 1 "STM32G431CBUx" H 5750 1300 50  0000 L CNN
F 2 "Housings_DFN_QFN:QFN-48-1EP_7x7mm_Pitch0.5mm" H 4300 2450 50  0001 C CNN
F 3 "http://datasheet.octopart.com/STM32G431CBU6-STMicroelectronics-datasheet-136120343.pdf" H 4300 2450 50  0001 C CNN
F 4 "https://octopart.com/stm32g431cbu6-stmicroelectronics-102308472?r=sp" H 4300 2450 50  0001 C CNN "1st Disrtib Link"
F 5 "STMicroelectronics" H 4300 2450 50  0001 C CNN "Manufacturer"
	1    4300 2450
	1    0    0    -1  
$EndComp
Wire Wire Line
	4450 1900 4550 1900
$Comp
L power:+3V3 #PWR01
U 1 1 5DBC5E63
P 3900 2300
F 0 "#PWR01" H 3900 2150 50  0001 C CNN
F 1 "+3V3" H 3915 2473 50  0000 C CNN
F 2 "" H 3900 2300 50  0001 C CNN
F 3 "" H 3900 2300 50  0001 C CNN
	1    3900 2300
	0    -1   -1   0   
$EndComp
$Comp
L power:+3V3 #PWR02
U 1 1 5DBC63AD
P 5350 3700
F 0 "#PWR02" H 5350 3550 50  0001 C CNN
F 1 "+3V3" H 5365 3873 50  0000 C CNN
F 2 "" H 5350 3700 50  0001 C CNN
F 3 "" H 5350 3700 50  0001 C CNN
	1    5350 3700
	-1   0    0    1   
$EndComp
$Comp
L power:+3V3 #PWR04
U 1 1 5DBC6C30
P 6700 2400
F 0 "#PWR04" H 6700 2250 50  0001 C CNN
F 1 "+3V3" H 6715 2573 50  0000 C CNN
F 2 "" H 6700 2400 50  0001 C CNN
F 3 "" H 6700 2400 50  0001 C CNN
	1    6700 2400
	1    0    0    -1  
$EndComp
Wire Wire Line
	6250 2400 6700 2400
Wire Wire Line
	3900 2300 4050 2300
$Comp
L power:+3V3 #PWR03
U 1 1 5DBD08F0
P 5550 3700
F 0 "#PWR03" H 5550 3550 50  0001 C CNN
F 1 "+3V3" H 5565 3873 50  0000 C CNN
F 2 "" H 5550 3700 50  0001 C CNN
F 3 "" H 5550 3700 50  0001 C CNN
	1    5550 3700
	-1   0    0    1   
$EndComp
Wire Wire Line
	9150 3850 9500 3850
Wire Wire Line
	5050 1700 5050 1450
$Comp
L Connector:TestPoint TP1
U 1 1 5DBBB855
P 9500 3750
F 0 "TP1" V 9454 3938 50  0000 L CNN
F 1 "TestPoint" V 9545 3938 50  0001 L CNN
F 2 "Measurement_Points:Measurement_Point_Round-SMD-Pad_Small" H 9700 3750 50  0001 C CNN
F 3 "~" H 9700 3750 50  0001 C CNN
	1    9500 3750
	0    1    1    0   
$EndComp
$Comp
L Connector:TestPoint TP2
U 1 1 5DBBC61F
P 9500 3850
F 0 "TP2" V 9454 4038 50  0000 L CNN
F 1 "TestPoint" V 9545 4038 50  0001 L CNN
F 2 "Measurement_Points:Measurement_Point_Round-SMD-Pad_Small" H 9700 3850 50  0001 C CNN
F 3 "~" H 9700 3850 50  0001 C CNN
	1    9500 3850
	0    1    1    0   
$EndComp
$Comp
L Connector:TestPoint TP3
U 1 1 5DBBC798
P 9500 3950
F 0 "TP3" V 9454 4138 50  0000 L CNN
F 1 "TestPoint" V 9545 4138 50  0001 L CNN
F 2 "Measurement_Points:Measurement_Point_Round-SMD-Pad_Small" H 9700 3950 50  0001 C CNN
F 3 "~" H 9700 3950 50  0001 C CNN
	1    9500 3950
	0    1    1    0   
$EndComp
$Comp
L Connector:TestPoint TP4
U 1 1 5DBBC8FA
P 9500 4050
F 0 "TP4" V 9454 4238 50  0000 L CNN
F 1 "TestPoint" V 9545 4238 50  0001 L CNN
F 2 "Measurement_Points:Measurement_Point_Round-SMD-Pad_Small" H 9700 4050 50  0001 C CNN
F 3 "~" H 9700 4050 50  0001 C CNN
	1    9500 4050
	0    1    1    0   
$EndComp
Wire Wire Line
	1300 3800 1700 3800
Text GLabel 4050 2400 0    50   Input ~ 0
CAN_STBY
$Comp
L Jumper:SolderJumper_2_Open JP1
U 1 1 5E6428F6
P 1550 3600
F 0 "JP1" H 1350 3650 50  0000 C CNN
F 1 "SolderJumper_2_Open" H 1550 3714 50  0001 C CNN
F 2 "ucan_custom:mini_GS2" H 1550 3600 50  0001 C CNN
F 3 "~" H 1550 3600 50  0001 C CNN
	1    1550 3600
	1    0    0    -1  
$EndComp
$Comp
L Jumper:SolderJumper_2_Open JP2
U 1 1 5E643C64
P 1550 3700
F 0 "JP2" H 1350 3750 50  0000 C CNN
F 1 "SolderJumper_2_Open" H 1550 3814 50  0001 C CNN
F 2 "ucan_custom:mini_GS2" H 1550 3700 50  0001 C CNN
F 3 "~" H 1550 3700 50  0001 C CNN
	1    1550 3700
	1    0    0    -1  
$EndComp
$Comp
L Jumper:SolderJumper_2_Open JP3
U 1 1 5E6444B1
P 1550 3900
F 0 "JP3" H 1350 3950 50  0000 C CNN
F 1 "SolderJumper_2_Open" H 1550 4014 50  0001 C CNN
F 2 "Connectors:GS2" H 1550 3900 50  0001 C CNN
F 3 "~" H 1550 3900 50  0001 C CNN
	1    1550 3900
	1    0    0    -1  
$EndComp
Wire Wire Line
	1300 3900 1400 3900
Text GLabel 5250 1900 1    50   Input ~ 0
SW_SWO
$Comp
L Connector:TestPoint TP5
U 1 1 5E87D787
P 9500 4150
F 0 "TP5" V 9454 4338 50  0000 L CNN
F 1 "TestPoint" V 9545 4338 50  0001 L CNN
F 2 "Measurement_Points:Measurement_Point_Round-SMD-Pad_Small" H 9700 4150 50  0001 C CNN
F 3 "~" H 9700 4150 50  0001 C CNN
	1    9500 4150
	0    1    1    0   
$EndComp
Text GLabel 9350 4150 0    50   Input ~ 0
SW_SWO
Wire Wire Line
	9350 4150 9500 4150
Wire Wire Line
	3800 6550 3800 6250
Wire Wire Line
	2850 5950 3600 5950
Wire Wire Line
	3500 7100 4050 7100
Wire Wire Line
	3400 6700 3400 6550
Connection ~ 3400 6550
Wire Wire Line
	3400 6550 3800 6550
Wire Wire Line
	3600 6700 3600 5950
Connection ~ 3600 5950
Wire Wire Line
	3600 5950 3950 5950
Text Label 3200 5950 0    50   ~ 0
CANH
Text Label 3200 6550 0    50   ~ 0
CANL
$Comp
L Connector:TestPoint TP7
U 1 1 5ECC3EBA
P 4050 3300
F 0 "TP7" V 4004 3488 50  0000 L CNN
F 1 "TestPoint" V 4095 3488 50  0001 L CNN
F 2 "Measurement_Points:Measurement_Point_Round-SMD-Pad_Small" H 4250 3300 50  0001 C CNN
F 3 "~" H 4250 3300 50  0001 C CNN
	1    4050 3300
	0    -1   -1   0   
$EndComp
$Comp
L Connector:TestPoint TP6
U 1 1 5ECC68A8
P 4050 3200
F 0 "TP6" V 4004 3388 50  0000 L CNN
F 1 "TestPoint" V 4095 3388 50  0001 L CNN
F 2 "Measurement_Points:Measurement_Point_Round-SMD-Pad_Small" H 4250 3200 50  0001 C CNN
F 3 "~" H 4250 3200 50  0001 C CNN
	1    4050 3200
	0    -1   -1   0   
$EndComp
$Comp
L Connector:TestPoint TP9
U 1 1 5ECD5181
P 3650 4050
F 0 "TP9" V 3604 4238 50  0000 L CNN
F 1 "TestPoint" V 3695 4238 50  0001 L CNN
F 2 "Measurement_Points:Measurement_Point_Round-SMD-Pad_Small" H 3850 4050 50  0001 C CNN
F 3 "~" H 3850 4050 50  0001 C CNN
	1    3650 4050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0110
U 1 1 5ECD530A
P 3650 4050
F 0 "#PWR0110" H 3650 3800 50  0001 C CNN
F 1 "GND" H 3655 3877 50  0000 C CNN
F 2 "" H 3650 4050 50  0001 C CNN
F 3 "" H 3650 4050 50  0001 C CNN
	1    3650 4050
	-1   0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR0111
U 1 1 5ECD5863
P 3300 4000
F 0 "#PWR0111" H 3300 3850 50  0001 C CNN
F 1 "+3V3" H 3315 4173 50  0000 C CNN
F 2 "" H 3300 4000 50  0001 C CNN
F 3 "" H 3300 4000 50  0001 C CNN
	1    3300 4000
	1    0    0    -1  
$EndComp
$Comp
L Connector:TestPoint TP8
U 1 1 5ECD8750
P 3300 4000
F 0 "TP8" V 3254 4188 50  0000 L CNN
F 1 "TestPoint" V 3345 4188 50  0001 L CNN
F 2 "Measurement_Points:Measurement_Point_Round-SMD-Pad_Small" H 3500 4000 50  0001 C CNN
F 3 "~" H 3500 4000 50  0001 C CNN
	1    3300 4000
	-1   0    0    1   
$EndComp
$EndSCHEMATC
