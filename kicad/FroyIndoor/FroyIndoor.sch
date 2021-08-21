EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A3 16535 11693
encoding utf-8
Sheet 1 1
Title "FroyIndoor.sch"
Date "14 MAR 2021"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text Notes 3250 1000 0    100  ~ 0
USB-UART-Bridge
Text Notes 850  1900 0    100  ~ 0
Mini-USB
Wire Wire Line
	1450 2500 1600 2500
$Comp
L power:GNDREF #PWR01
U 1 1 6053F158
P 1600 3400
F 0 "#PWR01" H 1600 3150 50  0001 C CNN
F 1 "GNDREF" H 1605 3227 50  0000 C CNN
F 2 "" H 1600 3400 50  0001 C CNN
F 3 "" H 1600 3400 50  0001 C CNN
	1    1600 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	1150 3100 1150 3250
$Comp
L power:+5V #PWR05
U 1 1 6055A333
P 2200 2250
F 0 "#PWR05" H 2200 2100 50  0001 C CNN
F 1 "+5V" H 2215 2423 50  0000 C CNN
F 2 "" H 2200 2250 50  0001 C CNN
F 3 "" H 2200 2250 50  0001 C CNN
	1    2200 2250
	1    0    0    -1  
$EndComp
Wire Wire Line
	1600 2900 1600 2500
NoConn ~ 1050 3100
$Comp
L Device:C C4
U 1 1 6060C986
P 5000 1850
F 0 "C4" V 4840 1850 50  0000 C CNN
F 1 "100nF" V 4749 1850 50  0000 C CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 5038 1700 50  0001 C CNN
F 3 "~" H 5000 1850 50  0001 C CNN
	1    5000 1850
	0    -1   -1   0   
$EndComp
$Comp
L Device:Ferrite_Bead FB1
U 1 1 6067AC7A
P 1850 2500
F 0 "FB1" V 2124 2500 50  0000 C CNN
F 1 "Ferrite_Bead" V 2033 2500 50  0000 C CNN
F 2 "Inductor_SMD:L_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 1780 2500 50  0001 C CNN
F 3 "~" H 1850 2500 50  0001 C CNN
	1    1850 2500
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1600 3200 1600 3250
Wire Wire Line
	1150 3250 1600 3250
Connection ~ 1600 3250
Wire Wire Line
	1600 3250 1600 3400
Wire Wire Line
	1700 2500 1600 2500
Connection ~ 1600 2500
$Comp
L Device:CP C3
U 1 1 6069D0B6
P 5000 1600
F 0 "C3" V 5255 1600 50  0000 C CNN
F 1 "4.7uF" V 5164 1600 50  0000 C CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 5038 1450 50  0001 C CNN
F 3 "~" H 5000 1600 50  0001 C CNN
	1    5000 1600
	0    -1   -1   0   
$EndComp
$Comp
L Device:CP C1
U 1 1 606A6381
P 1600 3050
F 0 "C1" H 1718 3096 50  0000 L CNN
F 1 "10nF" H 1718 3005 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 1638 2900 50  0001 C CNN
F 3 "~" H 1600 3050 50  0001 C CNN
	1    1600 3050
	1    0    0    -1  
$EndComp
Text Label 850  6100 0    50   ~ 0
EN
Text Label 850  6350 0    50   ~ 0
IO0
Wire Wire Line
	1600 7350 1750 7350
Text Label 850  7350 0    50   ~ 0
IO15
$Comp
L power:GNDREF #PWR03
U 1 1 607B9D67
P 1750 7450
F 0 "#PWR03" H 1750 7200 50  0001 C CNN
F 1 "GNDREF" H 1755 7277 50  0000 C CNN
F 2 "" H 1750 7450 50  0001 C CNN
F 3 "" H 1750 7450 50  0001 C CNN
	1    1750 7450
	1    0    0    -1  
$EndComp
Wire Wire Line
	1750 7350 1750 7450
$Comp
L power:+3V3 #PWR09
U 1 1 60870CBC
P 4050 5850
F 0 "#PWR09" H 4050 5700 50  0001 C CNN
F 1 "+3V3" H 4065 6023 50  0000 C CNN
F 2 "" H 4050 5850 50  0001 C CNN
F 3 "" H 4050 5850 50  0001 C CNN
	1    4050 5850
	-1   0    0    -1  
$EndComp
Wire Wire Line
	3550 5950 3450 5950
Wire Wire Line
	3150 5950 2750 5950
Text Label 2750 5950 0    50   ~ 0
IO5
Wire Notes Line
	4600 7300 3050 7300
Wire Notes Line
	3050 7300 3050 5550
Wire Notes Line
	4600 5550 3050 5550
Wire Notes Line
	4600 5550 4600 7300
Text Notes 3050 5500 0    50   ~ 0
optional LEDs
Text Label 7550 6050 2    50   ~ 0
RST
$Comp
L Device:R R9
U 1 1 608F39ED
P 6150 6300
F 0 "R9" V 5943 6300 50  0000 C CNN
F 1 "12k" V 6034 6300 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 6080 6300 50  0001 C CNN
F 3 "~" H 6150 6300 50  0001 C CNN
	1    6150 6300
	0    1    1    0   
$EndComp
$Comp
L Interface_USB:FT232RL U1
U 1 1 6091C515
P 4600 3100
F 0 "U1" H 5200 4000 50  0000 C CNN
F 1 "FT232RL" H 4100 4000 50  0000 C CNN
F 2 "Package_SO:SSOP-28_5.3x10.2mm_P0.65mm" H 5700 2200 50  0001 C CNN
F 3 "https://www.ftdichip.com/Support/Documents/DataSheets/ICs/DS_FT232R.pdf" H 4600 3100 50  0001 C CNN
	1    4600 3100
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR08
U 1 1 6069616D
P 4700 1350
F 0 "#PWR08" H 4700 1200 50  0001 C CNN
F 1 "+5V" H 4715 1523 50  0000 C CNN
F 2 "" H 4700 1350 50  0001 C CNN
F 3 "" H 4700 1350 50  0001 C CNN
	1    4700 1350
	1    0    0    -1  
$EndComp
Wire Wire Line
	4700 2100 4700 1850
Wire Wire Line
	3800 3100 2850 3100
Text Label 2850 3100 0    50   ~ 0
FTRESET
Text Label 850  5850 0    50   ~ 0
FTRESET
$Comp
L power:+5V #PWR02
U 1 1 606DBC8C
P 1750 5700
F 0 "#PWR02" H 1750 5550 50  0001 C CNN
F 1 "+5V" H 1765 5873 50  0000 C CNN
F 2 "" H 1750 5700 50  0001 C CNN
F 3 "" H 1750 5700 50  0001 C CNN
	1    1750 5700
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1600 5850 1750 5850
Wire Wire Line
	1750 5850 1750 5700
NoConn ~ 3800 3300
NoConn ~ 3800 3500
$Comp
L power:GNDREF #PWR06
U 1 1 606ECAF5
P 4400 4400
F 0 "#PWR06" H 4400 4150 50  0001 C CNN
F 1 "GNDREF" H 4405 4227 50  0000 C CNN
F 2 "" H 4400 4400 50  0001 C CNN
F 3 "" H 4400 4400 50  0001 C CNN
	1    4400 4400
	1    0    0    -1  
$EndComp
Wire Wire Line
	4400 4100 4400 4250
Wire Wire Line
	3800 3800 3700 3800
Wire Wire Line
	3700 3800 3700 4250
Wire Wire Line
	3700 4250 4400 4250
Connection ~ 4400 4250
Wire Wire Line
	4400 4250 4400 4400
Wire Wire Line
	4600 4100 4600 4250
Wire Wire Line
	4600 4250 4400 4250
Wire Wire Line
	4700 4100 4700 4250
Wire Wire Line
	4700 4250 4600 4250
Connection ~ 4600 4250
Wire Wire Line
	4800 4100 4800 4250
Wire Wire Line
	4800 4250 4700 4250
Connection ~ 4700 4250
$Comp
L Device:C C2
U 1 1 60713A9F
P 3400 3550
F 0 "C2" H 3515 3596 50  0000 L CNN
F 1 "100nF" H 3515 3505 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 3438 3400 50  0001 C CNN
F 3 "~" H 3400 3550 50  0001 C CNN
	1    3400 3550
	1    0    0    -1  
$EndComp
NoConn ~ 5400 2900
NoConn ~ 5400 3000
NoConn ~ 5400 3100
Wire Wire Line
	4500 2100 4500 2000
Wire Wire Line
	2200 2250 2200 2500
Wire Wire Line
	4500 2000 4500 1350
Connection ~ 4500 2000
$Comp
L power:+3V3 #PWR07
U 1 1 607551BF
P 4500 1350
F 0 "#PWR07" H 4500 1200 50  0001 C CNN
F 1 "+3V3" H 4515 1523 50  0000 C CNN
F 2 "" H 4500 1350 50  0001 C CNN
F 3 "" H 4500 1350 50  0001 C CNN
	1    4500 1350
	1    0    0    -1  
$EndComp
Text Label 5250 6300 0    50   ~ 0
DTR
Text Label 5250 6900 0    50   ~ 0
RTS
Wire Notes Line
	7300 7300 7300 5350
Wire Notes Line
	7300 5350 5650 5350
Wire Notes Line
	5650 5350 5650 7300
Wire Notes Line
	5650 7300 7300 7300
Text Notes 5650 5300 0    50   ~ 0
auto-reset
Wire Notes Line
	2300 7750 2300 5400
Wire Notes Line
	2300 5400 1200 5400
Wire Notes Line
	1200 5400 1200 7750
Wire Notes Line
	1200 7750 2300 7750
Text Notes 1200 5350 0    50   ~ 0
pull-up's and down's
Text Notes 2300 7850 2    50   ~ 0
all resistors are 10k
Wire Wire Line
	1300 7350 850  7350
Wire Wire Line
	1300 6350 850  6350
Wire Wire Line
	1300 6100 850  6100
Wire Wire Line
	1300 5850 850  5850
$Comp
L Device:R R4
U 1 1 607C09B0
P 1450 7350
F 0 "R4" V 1335 7350 50  0000 C CNN
F 1 "10k" V 1656 7350 50  0001 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 1380 7350 50  0001 C CNN
F 3 "~" H 1450 7350 50  0001 C CNN
	1    1450 7350
	0    1    1    0   
$EndComp
$Comp
L Device:R R3
U 1 1 607A3701
P 1450 6350
F 0 "R3" V 1335 6350 50  0000 C CNN
F 1 "10k" V 1656 6350 50  0001 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 1380 6350 50  0001 C CNN
F 3 "~" H 1450 6350 50  0001 C CNN
	1    1450 6350
	0    -1   1    0   
$EndComp
$Comp
L Device:R R2
U 1 1 607A274F
P 1450 6100
F 0 "R2" V 1335 6100 50  0000 C CNN
F 1 "10k" V 1334 6100 50  0001 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 1380 6100 50  0001 C CNN
F 3 "~" H 1450 6100 50  0001 C CNN
	1    1450 6100
	0    -1   1    0   
$EndComp
$Comp
L Device:R R1
U 1 1 60797333
P 1450 5850
F 0 "R1" V 1335 5850 50  0000 C CNN
F 1 "10k" V 1334 5850 50  0001 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 1380 5850 50  0001 C CNN
F 3 "~" H 1450 5850 50  0001 C CNN
	1    1450 5850
	0    -1   1    0   
$EndComp
Wire Notes Line
	5700 4700 5700 1050
Wire Notes Line
	5700 1050 3250 1050
Wire Notes Line
	3250 1050 3250 4700
Wire Notes Line
	3250 4700 5700 4700
Wire Wire Line
	3400 3700 3400 4250
Wire Wire Line
	3400 4250 3700 4250
Connection ~ 3700 4250
Wire Wire Line
	4500 2000 3400 2000
Wire Wire Line
	3400 3400 3400 2400
Connection ~ 3400 2400
Wire Wire Line
	3400 2400 3800 2400
Wire Wire Line
	3400 2000 3400 2400
$Comp
L Device:LED D2
U 1 1 609E4076
P 3700 6350
F 0 "D2" H 3693 6095 50  0000 C CNN
F 1 "TX" H 3693 6186 50  0000 C CNN
F 2 "LED_SMD:LED_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 3700 6350 50  0001 C CNN
F 3 "~" H 3700 6350 50  0001 C CNN
	1    3700 6350
	1    0    0    1   
$EndComp
$Comp
L Device:LED D3
U 1 1 609E4639
P 3700 6750
F 0 "D3" H 3693 6495 50  0000 C CNN
F 1 "RX" H 3693 6586 50  0000 C CNN
F 2 "LED_SMD:LED_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 3700 6750 50  0001 C CNN
F 3 "~" H 3700 6750 50  0001 C CNN
	1    3700 6750
	1    0    0    1   
$EndComp
Wire Wire Line
	3150 6750 2750 6750
Text Label 2750 6350 0    50   ~ 0
CBUS0
Text Label 2750 6750 0    50   ~ 0
CBUS1
$Comp
L Device:R R6
U 1 1 60A002F9
P 3300 6350
F 0 "R6" V 3093 6350 50  0000 C CNN
F 1 "270" V 3184 6350 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 3230 6350 50  0001 C CNN
F 3 "~" H 3300 6350 50  0001 C CNN
	1    3300 6350
	0    -1   1    0   
$EndComp
$Comp
L Device:R R7
U 1 1 60A00724
P 3300 6750
F 0 "R7" V 3093 6750 50  0000 C CNN
F 1 "270" V 3184 6750 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 3230 6750 50  0001 C CNN
F 3 "~" H 3300 6750 50  0001 C CNN
	1    3300 6750
	0    -1   1    0   
$EndComp
Wire Wire Line
	3450 6750 3550 6750
Wire Wire Line
	3450 6350 3550 6350
Wire Wire Line
	3150 6350 2750 6350
Wire Wire Line
	3850 6750 4050 6750
Wire Wire Line
	4050 6750 4050 6350
Wire Wire Line
	3850 6350 4050 6350
Connection ~ 4050 6350
Text Label 6000 2800 2    50   ~ 0
DTR
Wire Wire Line
	5400 2800 6000 2800
Text Label 6000 3400 2    50   ~ 0
CBUS0
Wire Wire Line
	5400 3400 6000 3400
Text Label 6000 3500 2    50   ~ 0
CBUS1
Wire Wire Line
	5400 3500 6000 3500
NoConn ~ 5400 3600
NoConn ~ 5400 3700
NoConn ~ 5400 3800
Wire Wire Line
	2000 2500 2200 2500
$Comp
L power:GNDREF #PWR010
U 1 1 60B45088
P 5450 1950
F 0 "#PWR010" H 5450 1700 50  0001 C CNN
F 1 "GNDREF" H 5455 1777 50  0000 C CNN
F 2 "" H 5450 1950 50  0001 C CNN
F 3 "" H 5450 1950 50  0001 C CNN
	1    5450 1950
	1    0    0    -1  
$EndComp
Wire Wire Line
	5150 1850 5450 1850
Wire Wire Line
	5450 1850 5450 1950
Wire Wire Line
	5150 1600 5450 1600
Wire Wire Line
	5450 1600 5450 1850
Connection ~ 5450 1850
Wire Wire Line
	4850 1600 4700 1600
Connection ~ 4700 1600
Wire Wire Line
	4700 1600 4700 1350
Wire Wire Line
	4850 1850 4700 1850
Connection ~ 4700 1850
Wire Wire Line
	4700 1850 4700 1600
Wire Notes Line
	2400 3700 2400 1950
Wire Notes Line
	2400 1950 850  1950
Wire Notes Line
	850  1950 850  3700
Wire Notes Line
	850  3700 2400 3700
Wire Wire Line
	1450 2700 3800 2700
Wire Wire Line
	1450 2800 3800 2800
Text Label 6000 2500 2    50   ~ 0
TXD
Text Label 6000 2400 2    50   ~ 0
RXD
Text Notes 5850 2300 0    50   ~ 0
RX/TX are swapped here!
Wire Wire Line
	5400 2500 6000 2500
Wire Wire Line
	5400 2400 6000 2400
Text Notes 7350 1050 0    100  ~ 0
ESP-WROOM-02U/D
Text Label 3800 2700 2    50   ~ 0
USBD+
Text Label 3800 2800 2    50   ~ 0
USBD-
Text Label 9400 3050 2    50   ~ 0
I2C_CLK
Text Label 9400 3150 2    50   ~ 0
IO15
Text Label 9400 2550 2    50   ~ 0
I2C_SDA
Text Label 9400 2450 2    50   ~ 0
IO0
Text Label 7100 2500 0    50   ~ 0
EN
Text Label 7100 2600 0    50   ~ 0
RST
Text Label 7100 2900 0    50   ~ 0
RXD
Text Label 7100 2800 0    50   ~ 0
TXD
Wire Wire Line
	8700 2550 9400 2550
Wire Wire Line
	8700 3050 9400 3050
Wire Wire Line
	7500 2500 7100 2500
Wire Wire Line
	7500 2600 7100 2600
Wire Wire Line
	7500 2900 7100 2900
Wire Wire Line
	7500 2800 7100 2800
$Comp
L power:GNDREF #PWR014
U 1 1 60798272
P 8250 3850
F 0 "#PWR014" H 8250 3600 50  0001 C CNN
F 1 "GNDREF" H 8255 3677 50  0000 C CNN
F 2 "" H 8250 3850 50  0001 C CNN
F 3 "" H 8250 3850 50  0001 C CNN
	1    8250 3850
	-1   0    0    -1  
$EndComp
Wire Wire Line
	8700 3150 9400 3150
NoConn ~ 7500 3100
Wire Wire Line
	8700 2450 9400 2450
NoConn ~ 8700 2850
NoConn ~ 8700 2950
NoConn ~ 8700 2650
Wire Wire Line
	8250 3850 8250 3700
$Comp
L xrstf:ESP-WROOM-02U_4MB IC1
U 1 1 607F9B42
P 8700 2400
F 0 "IC1" H 9650 2550 50  0000 C CNN
F 1 "ESP-WROOM-02U__4MB_" H 8800 2550 50  0001 C CNN
F 2 "xrstf:ESP-WROOM-02U" H 9750 2500 50  0001 L CNN
F 3 "" H 9750 2400 50  0001 L CNN
	1    8700 2400
	-1   0    0    -1  
$EndComp
Wire Wire Line
	8150 3600 8150 3700
Wire Wire Line
	8150 3700 8250 3700
Connection ~ 8250 3700
Wire Wire Line
	8250 3700 8250 3600
Wire Wire Line
	8050 3600 8050 3700
Wire Wire Line
	8050 3700 8150 3700
Connection ~ 8150 3700
Wire Wire Line
	7950 3600 7950 3700
Wire Wire Line
	7950 3700 8050 3700
Connection ~ 8050 3700
Wire Notes Line
	9000 1100 7350 1100
Wire Notes Line
	7350 4200 7350 1100
Wire Notes Line
	9000 1100 9000 4200
Wire Notes Line
	9000 4200 7350 4200
Wire Wire Line
	8100 1400 8100 1650
$Comp
L Connector_Generic:Conn_01x04 J2
U 1 1 6069D35A
P 10850 2650
F 0 "J2" H 10930 2642 50  0000 L CNN
F 1 "BME260_Breakout" H 10930 2551 50  0000 L CNN
F 2 "xrstf:PinHeader_1x04_P2.54mm_Vertical" H 10850 2650 50  0001 C CNN
F 3 "~" H 10850 2650 50  0001 C CNN
	1    10850 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	10650 2550 10500 2550
Wire Wire Line
	10500 2550 10500 2350
Wire Notes Line
	11650 3300 11650 2100
Wire Notes Line
	11650 2100 10300 2100
Wire Notes Line
	10300 2100 10300 3300
Wire Notes Line
	10300 3300 11650 3300
Text Notes 10300 2050 0    100  ~ 0
BME280 Breakout
Wire Wire Line
	10650 2650 10500 2650
$Comp
L power:GNDREF #PWR0102
U 1 1 606A2FD2
P 10500 3050
F 0 "#PWR0102" H 10500 2800 50  0001 C CNN
F 1 "GNDREF" H 10505 2877 50  0000 C CNN
F 2 "" H 10500 3050 50  0001 C CNN
F 3 "" H 10500 3050 50  0001 C CNN
	1    10500 3050
	-1   0    0    -1  
$EndComp
Wire Wire Line
	10500 2650 10500 3050
Wire Wire Line
	10650 2750 9900 2750
Text Label 9900 2850 0    50   ~ 0
I2C_CLK
Wire Wire Line
	10650 2850 9900 2850
Text Label 9900 2750 0    50   ~ 0
I2C_SDA
Wire Wire Line
	1600 6100 2050 6100
Wire Wire Line
	2050 6100 2050 5700
Wire Wire Line
	1600 6350 2050 6350
Wire Wire Line
	2050 6350 2050 6100
Connection ~ 2050 6100
Wire Wire Line
	4050 5850 4050 6350
Wire Wire Line
	3850 5950 4350 5950
Wire Wire Line
	5400 2600 6000 2600
Text Label 6000 2600 2    50   ~ 0
RTS
$Comp
L Connector:USB_B_Mini J1
U 1 1 607CDAC7
P 1150 2700
F 0 "J1" H 1207 3167 50  0000 C CNN
F 1 "USB_B_Mini" H 1207 3076 50  0000 C CNN
F 2 "xrstf:USB_BWM_MIniUSB_THT_reichelt" H 1300 2650 50  0001 C CNN
F 3 "~" H 1300 2650 50  0001 C CNN
	1    1150 2700
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D1
U 1 1 60871AC0
P 3700 5950
F 0 "D1" H 3693 6167 50  0000 C CNN
F 1 "STATUS" H 3693 6076 50  0000 C CNN
F 2 "LED_SMD:LED_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 3700 5950 50  0001 C CNN
F 3 "~" H 3700 5950 50  0001 C CNN
	1    3700 5950
	-1   0    0    -1  
$EndComp
$Comp
L Device:R R5
U 1 1 607C9920
P 3300 5950
F 0 "R5" V 3093 5950 50  0000 C CNN
F 1 "270" V 3184 5950 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 3230 5950 50  0001 C CNN
F 3 "~" H 3300 5950 50  0001 C CNN
	1    3300 5950
	0    -1   1    0   
$EndComp
Wire Wire Line
	8700 2750 9400 2750
Text Label 9400 2750 2    50   ~ 0
IO5
$Comp
L Device:R R8
U 1 1 6086724D
P 6150 6900
F 0 "R8" V 6265 6900 50  0000 C CNN
F 1 "12k" V 6356 6900 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 6080 6900 50  0001 C CNN
F 3 "~" H 6150 6900 50  0001 C CNN
	1    6150 6900
	0    1    1    0   
$EndComp
Wire Wire Line
	6300 6300 6400 6300
Wire Wire Line
	6400 6900 6300 6900
Wire Wire Line
	6700 6700 6700 6650
Wire Wire Line
	6700 6650 5850 6650
Wire Wire Line
	5850 6300 6000 6300
Wire Wire Line
	5250 6300 5850 6300
Connection ~ 5850 6300
Wire Wire Line
	6700 6500 6700 6550
Wire Wire Line
	6700 6550 5750 6550
Wire Wire Line
	5850 6300 5850 6650
Wire Wire Line
	6700 6100 6700 6050
Wire Wire Line
	6700 7150 7550 7150
Text Label 7550 7150 2    50   ~ 0
IO0
Wire Wire Line
	5250 6900 5750 6900
Wire Wire Line
	5750 6550 5750 6900
Connection ~ 5750 6900
Wire Wire Line
	5750 6900 6000 6900
Wire Wire Line
	6700 7100 6700 7150
NoConn ~ 1450 2900
$Comp
L power:GNDREF #PWR0101
U 1 1 60995317
P 4350 6950
F 0 "#PWR0101" H 4350 6700 50  0001 C CNN
F 1 "GNDREF" H 4355 6777 50  0000 C CNN
F 2 "" H 4350 6950 50  0001 C CNN
F 3 "" H 4350 6950 50  0001 C CNN
	1    4350 6950
	1    0    0    -1  
$EndComp
Wire Wire Line
	4350 5950 4350 6950
$Comp
L Switch:SW_SPST SW1
U 1 1 60A341F2
P 3900 8150
F 0 "SW1" H 3900 8385 50  0000 C CNN
F 1 "SW_SPST" H 3900 8294 50  0000 C CNN
F 2 "Button_Switch_THT:SW_Tactile_SPST_Angled_PTS645Vx83-2LFS" H 3900 8150 50  0001 C CNN
F 3 "~" H 3900 8150 50  0001 C CNN
	1    3900 8150
	1    0    0    -1  
$EndComp
Wire Wire Line
	3700 8150 3300 8150
Text Label 3300 8150 0    50   ~ 0
RST
$Comp
L power:GNDREF #PWR04
U 1 1 60A40159
P 4200 8350
F 0 "#PWR04" H 4200 8100 50  0001 C CNN
F 1 "GNDREF" H 4205 8177 50  0000 C CNN
F 2 "" H 4200 8350 50  0001 C CNN
F 3 "" H 4200 8350 50  0001 C CNN
	1    4200 8350
	1    0    0    -1  
$EndComp
Wire Wire Line
	4100 8150 4200 8150
Wire Wire Line
	4200 8150 4200 8350
Wire Notes Line
	3550 8650 4450 8650
Wire Notes Line
	4450 8650 4450 7800
Wire Notes Line
	4450 7800 3550 7800
Wire Notes Line
	3550 7800 3550 8650
Text Notes 3550 7750 0    50   ~ 0
Reset button
$Comp
L Device:C C6
U 1 1 60A5BC82
P 8400 1900
F 0 "C6" V 8240 1900 50  0000 C CNN
F 1 "100nF" V 8149 1900 50  0000 C CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 8438 1750 50  0001 C CNN
F 3 "~" H 8400 1900 50  0001 C CNN
	1    8400 1900
	0    -1   -1   0   
$EndComp
$Comp
L Device:CP C5
U 1 1 60A5BC8C
P 8400 1650
F 0 "C5" V 8655 1650 50  0000 C CNN
F 1 "470uF" V 8564 1650 50  0000 C CNN
F 2 "Capacitor_SMD:CP_Elec_10x12.5" H 8438 1500 50  0001 C CNN
F 3 "~" H 8400 1650 50  0001 C CNN
	1    8400 1650
	0    -1   -1   0   
$EndComp
$Comp
L power:GNDREF #PWR012
U 1 1 60A5BC96
P 8750 2000
F 0 "#PWR012" H 8750 1750 50  0001 C CNN
F 1 "GNDREF" H 8755 1827 50  0000 C CNN
F 2 "" H 8750 2000 50  0001 C CNN
F 3 "" H 8750 2000 50  0001 C CNN
	1    8750 2000
	1    0    0    -1  
$EndComp
Wire Wire Line
	8550 1900 8750 1900
Wire Wire Line
	8750 1900 8750 2000
Wire Wire Line
	8550 1650 8750 1650
Wire Wire Line
	8750 1650 8750 1900
Connection ~ 8750 1900
Wire Wire Line
	8250 1650 8100 1650
Wire Wire Line
	8250 1900 8100 1900
Connection ~ 8100 1650
Wire Wire Line
	8100 1650 8100 1900
Connection ~ 8100 1900
Wire Wire Line
	8100 1900 8100 2100
$Comp
L Sensor:BME280 U2
U 1 1 60AA4898
P 13300 2700
F 0 "U2" H 12871 2746 50  0000 R CNN
F 1 "BME280" H 12871 2655 50  0000 R CNN
F 2 "xrstf:BME280_680_BMP280" H 14800 2250 50  0001 C CNN
F 3 "https://ae-bst.resource.bosch.com/media/_tech/media/datasheets/BST-BME280-DS002.pdf" H 13300 2500 50  0001 C CNN
	1    13300 2700
	1    0    0    -1  
$EndComp
$Comp
L power:GNDREF #PWR015
U 1 1 60AA5A53
P 13200 3550
F 0 "#PWR015" H 13200 3300 50  0001 C CNN
F 1 "GNDREF" H 13205 3377 50  0000 C CNN
F 2 "" H 13200 3550 50  0001 C CNN
F 3 "" H 13200 3550 50  0001 C CNN
	1    13200 3550
	-1   0    0    -1  
$EndComp
Wire Wire Line
	13400 3300 13400 3400
Wire Wire Line
	13400 3400 13200 3400
Wire Wire Line
	13200 3400 13200 3550
Wire Wire Line
	13200 3300 13200 3400
Connection ~ 13200 3400
Wire Wire Line
	13200 2100 13200 1950
Wire Wire Line
	13400 2100 13400 1950
Wire Wire Line
	13400 1950 13200 1950
Connection ~ 13200 1950
Wire Wire Line
	13200 1950 13200 1800
Wire Wire Line
	13900 2400 14100 2400
Wire Wire Line
	14100 2400 14100 3400
Wire Wire Line
	14100 3400 13400 3400
Connection ~ 13400 3400
Wire Wire Line
	13900 2600 14650 2600
Text Label 14650 2600 2    50   ~ 0
I2C_CLK
Wire Wire Line
	13900 2800 14650 2800
Text Label 14650 2800 2    50   ~ 0
I2C_SDA
Wire Wire Line
	13900 3000 14650 3000
Text Label 14650 3000 2    50   ~ 0
CSB
Wire Notes Line
	12500 1500 12500 3800
Wire Notes Line
	12500 3800 14250 3800
Wire Notes Line
	14250 3800 14250 1500
Wire Notes Line
	14250 1500 12500 1500
Text Notes 12500 1450 0    100  ~ 0
BME280
Text Notes 11800 2750 0    100  ~ 0
- or -
$Comp
L Device:R R10
U 1 1 60B0692B
P 1450 6600
F 0 "R10" V 1335 6600 50  0000 C CNN
F 1 "10k" V 1656 6600 50  0001 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 1380 6600 50  0001 C CNN
F 3 "~" H 1450 6600 50  0001 C CNN
	1    1450 6600
	0    -1   1    0   
$EndComp
Wire Wire Line
	1600 6600 2050 6600
Wire Wire Line
	2050 6600 2050 6350
Connection ~ 2050 6350
Wire Wire Line
	1300 6600 850  6600
Text Label 850  6600 0    50   ~ 0
CSB
$Comp
L power:+3V3 #PWR0103
U 1 1 60A86F8A
P 13200 1800
F 0 "#PWR0103" H 13200 1650 50  0001 C CNN
F 1 "+3V3" H 13215 1973 50  0000 C CNN
F 2 "" H 13200 1800 50  0001 C CNN
F 3 "" H 13200 1800 50  0001 C CNN
	1    13200 1800
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR0104
U 1 1 60A88F57
P 10500 2350
F 0 "#PWR0104" H 10500 2200 50  0001 C CNN
F 1 "+3V3" H 10515 2523 50  0000 C CNN
F 2 "" H 10500 2350 50  0001 C CNN
F 3 "" H 10500 2350 50  0001 C CNN
	1    10500 2350
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR0105
U 1 1 60A89FFC
P 2050 5700
F 0 "#PWR0105" H 2050 5550 50  0001 C CNN
F 1 "+3V3" H 2065 5873 50  0000 C CNN
F 2 "" H 2050 5700 50  0001 C CNN
F 3 "" H 2050 5700 50  0001 C CNN
	1    2050 5700
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR0106
U 1 1 60A8BC25
P 8100 1400
F 0 "#PWR0106" H 8100 1250 50  0001 C CNN
F 1 "+3V3" H 8115 1573 50  0000 C CNN
F 2 "" H 8100 1400 50  0001 C CNN
F 3 "" H 8100 1400 50  0001 C CNN
	1    8100 1400
	1    0    0    -1  
$EndComp
NoConn ~ 5400 2700
$Comp
L Device:Q_NPN_BEC Q1
U 1 1 60A9DA12
P 6600 6300
F 0 "Q1" H 6791 6346 50  0000 L CNN
F 1 "Q_NPN_BEC" H 6791 6255 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 6800 6400 50  0001 C CNN
F 3 "~" H 6600 6300 50  0001 C CNN
	1    6600 6300
	1    0    0    -1  
$EndComp
$Comp
L Device:Q_NPN_BEC Q2
U 1 1 60A9E362
P 6600 6900
F 0 "Q2" H 6791 6854 50  0000 L CNN
F 1 "Q_NPN_BEC" H 6791 6945 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 6800 7000 50  0001 C CNN
F 3 "~" H 6600 6900 50  0001 C CNN
	1    6600 6900
	1    0    0    1   
$EndComp
Wire Wire Line
	8700 3250 9400 3250
Text Label 9400 3250 2    50   ~ 0
WAKE_UP
Text Label 5250 5500 0    50   ~ 0
WAKE_UP
Wire Wire Line
	6700 6050 7550 6050
$Comp
L Device:Q_NPN_BEC Q3
U 1 1 60BC62B6
P 6600 5800
F 0 "Q3" H 6791 5846 50  0000 L CNN
F 1 "Q_NPN_BEC" H 6791 5755 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 6800 5900 50  0001 C CNN
F 3 "~" H 6600 5800 50  0001 C CNN
	1    6600 5800
	1    0    0    -1  
$EndComp
Wire Wire Line
	6700 6000 6700 6050
Connection ~ 6700 6050
Wire Wire Line
	6700 5600 6700 5500
Wire Wire Line
	6700 5500 5250 5500
Wire Wire Line
	5750 6550 5750 5800
Connection ~ 5750 6550
$Comp
L Device:R R11
U 1 1 60BF9F09
P 6150 5800
F 0 "R11" V 5943 5800 50  0000 C CNN
F 1 "12k" V 6034 5800 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 6080 5800 50  0001 C CNN
F 3 "~" H 6150 5800 50  0001 C CNN
	1    6150 5800
	0    1    1    0   
$EndComp
Wire Wire Line
	6400 5800 6300 5800
Wire Wire Line
	5750 5800 6000 5800
$Comp
L Device:R R12
U 1 1 60E31A29
P 1450 6850
F 0 "R12" V 1335 6850 50  0000 C CNN
F 1 "10k" V 1656 6850 50  0001 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 1380 6850 50  0001 C CNN
F 3 "~" H 1450 6850 50  0001 C CNN
	1    1450 6850
	0    -1   1    0   
$EndComp
$Comp
L Device:R R13
U 1 1 60E31F44
P 1450 7100
F 0 "R13" V 1335 7100 50  0000 C CNN
F 1 "10k" V 1656 7100 50  0001 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 1380 7100 50  0001 C CNN
F 3 "~" H 1450 7100 50  0001 C CNN
	1    1450 7100
	0    -1   1    0   
$EndComp
Text Label 850  6850 0    50   ~ 0
I2C_SDA
Wire Wire Line
	850  6850 1300 6850
Wire Wire Line
	1600 6850 2050 6850
Wire Wire Line
	2050 6850 2050 6600
Connection ~ 2050 6600
Wire Wire Line
	1600 7100 2050 7100
Wire Wire Line
	2050 7100 2050 6850
Connection ~ 2050 6850
Wire Wire Line
	1300 7100 850  7100
Text Label 850  7100 0    50   ~ 0
I2C_CLK
$EndSCHEMATC
