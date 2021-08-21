EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A3 16535 11693
encoding utf-8
Sheet 1 1
Title "FroyForMen.sch"
Date "14 MAR 2021"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Wire Wire Line
	1550 5800 1450 5800
Wire Wire Line
	1150 5800 750  5800
Text Label 750  5800 0    50   ~ 0
LED
Wire Notes Line
	2300 6250 1050 6250
Wire Notes Line
	1050 6250 1050 5400
Wire Notes Line
	2300 5400 1050 5400
Wire Notes Line
	2300 5400 2300 6250
Text Notes 1050 5350 0    50   ~ 0
Status LED
Text Label 5450 6200 2    50   ~ 0
RST
$Comp
L Device:R R4
U 1 1 608F39ED
P 3750 6450
F 0 "R4" V 3543 6450 50  0000 C CNN
F 1 "10k" V 3634 6450 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 3680 6450 50  0001 C CNN
F 3 "~" H 3750 6450 50  0001 C CNN
	1    3750 6450
	0    1    1    0   
$EndComp
Text Label 2850 6450 0    50   ~ 0
DTR
Text Label 2850 7050 0    50   ~ 0
RTS
Wire Notes Line
	5200 7450 5200 5500
Wire Notes Line
	5200 5500 3250 5500
Wire Notes Line
	3250 5500 3250 7450
Wire Notes Line
	3250 7450 5200 7450
Text Notes 3250 5450 0    50   ~ 0
auto-reset
Wire Wire Line
	4950 7200 4950 7300
$Comp
L Device:R R6
U 1 1 607C09B0
P 4650 3700
F 0 "R6" H 4580 3654 50  0000 R CNN
F 1 "10k" H 4580 3745 50  0000 R CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 4580 3700 50  0001 C CNN
F 3 "~" H 4650 3700 50  0001 C CNN
	1    4650 3700
	-1   0    0    1   
$EndComp
$Comp
L Device:R R7
U 1 1 607A3701
P 4950 7050
F 0 "R7" H 5020 7004 50  0000 L CNN
F 1 "10k" H 5020 7095 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 4880 7050 50  0001 C CNN
F 3 "~" H 4950 7050 50  0001 C CNN
	1    4950 7050
	1    0    0    1   
$EndComp
$Comp
L Device:R R2
U 1 1 607A274F
P 3200 2350
F 0 "R2" H 3130 2396 50  0000 R CNN
F 1 "10k" H 3130 2305 50  0000 R CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 3130 2350 50  0001 C CNN
F 3 "~" H 3200 2350 50  0001 C CNN
	1    3200 2350
	-1   0    0    -1  
$EndComp
Text Notes 3050 1250 0    100  ~ 0
ESP-WROOM-02U/D
Text Label 5300 3250 2    50   ~ 0
I2C_CLK
Text Label 5300 2750 2    50   ~ 0
I2C_SDA
Text Label 5300 2650 2    50   ~ 0
IO0
Text Label 2550 2800 0    50   ~ 0
RST
Text Label 2550 3100 0    50   ~ 0
RXD
Text Label 2550 3000 0    50   ~ 0
TXD
Wire Wire Line
	4600 2750 5300 2750
Wire Wire Line
	4600 3250 5300 3250
Wire Wire Line
	3400 2700 3200 2700
Wire Wire Line
	3400 2800 2550 2800
Wire Wire Line
	3400 3100 2550 3100
Wire Wire Line
	3400 3000 2550 3000
$Comp
L power:GNDREF #PWR08
U 1 1 60798272
P 4150 4050
F 0 "#PWR08" H 4150 3800 50  0001 C CNN
F 1 "GNDREF" H 4155 3877 50  0000 C CNN
F 2 "" H 4150 4050 50  0001 C CNN
F 3 "" H 4150 4050 50  0001 C CNN
	1    4150 4050
	-1   0    0    -1  
$EndComp
Wire Wire Line
	4600 2650 5300 2650
NoConn ~ 4600 3150
NoConn ~ 4600 2850
Wire Wire Line
	4150 4050 4150 3900
$Comp
L xrstf:ESP-WROOM-02U_4MB IC1
U 1 1 607F9B42
P 4600 2600
F 0 "IC1" H 5550 2750 50  0000 C CNN
F 1 "ESP-WROOM-02U__4MB_" H 4700 2750 50  0001 C CNN
F 2 "xrstf:ESP-WROOM-02U" H 3900 2750 50  0001 L CNN
F 3 "" H 5650 2600 50  0001 L CNN
	1    4600 2600
	-1   0    0    -1  
$EndComp
Wire Wire Line
	4050 3800 4050 3900
Wire Wire Line
	4050 3900 4150 3900
Connection ~ 4150 3900
Wire Wire Line
	4150 3900 4150 3800
Wire Wire Line
	3950 3800 3950 3900
Wire Wire Line
	3950 3900 4050 3900
Connection ~ 4050 3900
Wire Wire Line
	3850 3800 3850 3900
Wire Wire Line
	3850 3900 3950 3900
Connection ~ 3950 3900
Wire Notes Line
	4900 1300 3050 1300
Wire Notes Line
	3050 4400 3050 1300
Wire Notes Line
	4900 1300 4900 4400
Wire Notes Line
	4900 4400 3050 4400
Wire Wire Line
	4950 6900 4950 6850
Wire Wire Line
	1850 5800 2100 5800
$Comp
L Device:LED D1
U 1 1 60871AC0
P 1700 5800
F 0 "D1" H 1693 6017 50  0000 C CNN
F 1 "STATUS" H 1693 5926 50  0000 C CNN
F 2 "LED_SMD:LED_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 1700 5800 50  0001 C CNN
F 3 "~" H 1700 5800 50  0001 C CNN
	1    1700 5800
	-1   0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 607C9920
P 1300 5800
F 0 "R1" V 1093 5800 50  0000 C CNN
F 1 "2k2" V 1184 5800 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 1230 5800 50  0001 C CNN
F 3 "~" H 1300 5800 50  0001 C CNN
	1    1300 5800
	0    -1   1    0   
$EndComp
Wire Wire Line
	4600 2950 5300 2950
Text Label 5300 2950 2    50   ~ 0
LED
$Comp
L Device:R R5
U 1 1 6086724D
P 3750 7050
F 0 "R5" V 3865 7050 50  0000 C CNN
F 1 "10k" V 3956 7050 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 3680 7050 50  0001 C CNN
F 3 "~" H 3750 7050 50  0001 C CNN
	1    3750 7050
	0    1    1    0   
$EndComp
Wire Wire Line
	3900 6450 4000 6450
Wire Wire Line
	4000 7050 3900 7050
Wire Wire Line
	4300 6850 4300 6800
Wire Wire Line
	4300 6800 3450 6800
Wire Wire Line
	3450 6450 3600 6450
Wire Wire Line
	2850 6450 3450 6450
Connection ~ 3450 6450
Wire Wire Line
	4300 6650 4300 6700
Wire Wire Line
	4300 6700 3350 6700
Wire Wire Line
	3450 6450 3450 6800
Wire Wire Line
	4300 6250 4300 6200
Wire Wire Line
	4300 7300 4950 7300
Text Label 5450 7300 2    50   ~ 0
IO0
Wire Wire Line
	2850 7050 3350 7050
Wire Wire Line
	3350 6700 3350 7050
Connection ~ 3350 7050
Wire Wire Line
	3350 7050 3600 7050
Wire Wire Line
	4300 7250 4300 7300
$Comp
L power:GNDREF #PWR04
U 1 1 60995317
P 2100 5950
F 0 "#PWR04" H 2100 5700 50  0001 C CNN
F 1 "GNDREF" H 2105 5777 50  0000 C CNN
F 2 "" H 2100 5950 50  0001 C CNN
F 3 "" H 2100 5950 50  0001 C CNN
	1    2100 5950
	1    0    0    -1  
$EndComp
Wire Wire Line
	2100 5800 2100 5950
$Comp
L Switch:SW_SPST SW1
U 1 1 60A341F2
P 1550 7000
F 0 "SW1" H 1550 7235 50  0000 C CNN
F 1 "SW_SPST" H 1550 7144 50  0000 C CNN
F 2 "Button_Switch_SMD:SW_SPST_CK_RS282G05A3" H 1550 7000 50  0001 C CNN
F 3 "~" H 1550 7000 50  0001 C CNN
	1    1550 7000
	1    0    0    -1  
$EndComp
Wire Wire Line
	1350 7000 950  7000
Text Label 950  7000 0    50   ~ 0
RST
$Comp
L power:GNDREF #PWR03
U 1 1 60A40159
P 1850 7200
F 0 "#PWR03" H 1850 6950 50  0001 C CNN
F 1 "GNDREF" H 1855 7027 50  0000 C CNN
F 2 "" H 1850 7200 50  0001 C CNN
F 3 "" H 1850 7200 50  0001 C CNN
	1    1850 7200
	1    0    0    -1  
$EndComp
Wire Wire Line
	1750 7000 1850 7000
Wire Wire Line
	1850 7000 1850 7200
Wire Notes Line
	1200 7500 2100 7500
Wire Notes Line
	2100 7500 2100 6650
Wire Notes Line
	2100 6650 1200 6650
Wire Notes Line
	1200 6650 1200 7500
Text Notes 1200 6600 0    50   ~ 0
Reset button
$Comp
L Device:C C1
U 1 1 60A5BC82
P 4300 2100
F 0 "C1" V 4140 2100 50  0000 C CNN
F 1 "100nF" V 4049 2100 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 4338 1950 50  0001 C CNN
F 3 "~" H 4300 2100 50  0001 C CNN
	1    4300 2100
	0    -1   -1   0   
$EndComp
$Comp
L power:GNDREF #PWR09
U 1 1 60A5BC96
P 4650 2200
F 0 "#PWR09" H 4650 1950 50  0001 C CNN
F 1 "GNDREF" H 4655 2027 50  0000 C CNN
F 2 "" H 4650 2200 50  0001 C CNN
F 3 "" H 4650 2200 50  0001 C CNN
	1    4650 2200
	1    0    0    -1  
$EndComp
Wire Wire Line
	4450 2100 4650 2100
Wire Wire Line
	4650 2100 4650 2200
Wire Wire Line
	4150 2100 4000 2100
Connection ~ 4000 2100
Wire Wire Line
	4000 2100 4000 2300
$Comp
L Sensor:BME280 U1
U 1 1 60AA4898
P 6650 3050
F 0 "U1" H 6221 3096 50  0000 R CNN
F 1 "BME280" H 6750 3050 50  0000 R CNN
F 2 "xrstf:BME280_680_BMP280" H 8150 2600 50  0001 C CNN
F 3 "https://ae-bst.resource.bosch.com/media/_tech/media/datasheets/BST-BME280-DS002.pdf" H 6650 2850 50  0001 C CNN
	1    6650 3050
	1    0    0    -1  
$EndComp
$Comp
L power:GNDREF #PWR012
U 1 1 60AA5A53
P 6550 3900
F 0 "#PWR012" H 6550 3650 50  0001 C CNN
F 1 "GNDREF" H 6555 3727 50  0000 C CNN
F 2 "" H 6550 3900 50  0001 C CNN
F 3 "" H 6550 3900 50  0001 C CNN
	1    6550 3900
	-1   0    0    -1  
$EndComp
Wire Wire Line
	6750 3650 6750 3750
Wire Wire Line
	6750 3750 6550 3750
Wire Wire Line
	6550 3750 6550 3900
Wire Wire Line
	6550 3650 6550 3750
Connection ~ 6550 3750
Wire Wire Line
	6550 2450 6550 2300
Wire Wire Line
	6750 2450 6750 2300
Wire Wire Line
	6750 2300 6550 2300
Connection ~ 6550 2300
Wire Wire Line
	6550 2300 6550 2150
Wire Wire Line
	7250 2750 7450 2750
Wire Wire Line
	7450 2750 7450 3750
Wire Wire Line
	7450 3750 6750 3750
Connection ~ 6750 3750
Wire Wire Line
	7250 2950 8000 2950
Text Label 8000 2950 2    50   ~ 0
I2C_CLK
Wire Wire Line
	7250 3150 8000 3150
Text Label 8000 3150 2    50   ~ 0
I2C_SDA
Wire Wire Line
	7250 3350 7350 3350
Wire Notes Line
	5850 1850 5850 4150
Wire Notes Line
	5850 4150 7600 4150
Wire Notes Line
	7600 4150 7600 1850
Wire Notes Line
	7600 1850 5850 1850
Text Notes 5850 1800 0    100  ~ 0
BME280/680
$Comp
L power:+3V3 #PWR07
U 1 1 60A8BC25
P 4000 1600
F 0 "#PWR07" H 4000 1450 50  0001 C CNN
F 1 "+3V3" H 4015 1773 50  0000 C CNN
F 2 "" H 4000 1600 50  0001 C CNN
F 3 "" H 4000 1600 50  0001 C CNN
	1    4000 1600
	1    0    0    -1  
$EndComp
$Comp
L Device:Q_NPN_BEC Q2
U 1 1 60A9DA12
P 4200 6450
F 0 "Q2" H 4391 6496 50  0000 L CNN
F 1 "Q_NPN_BEC" H 4391 6405 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 4400 6550 50  0001 C CNN
F 3 "~" H 4200 6450 50  0001 C CNN
	1    4200 6450
	1    0    0    -1  
$EndComp
$Comp
L Device:Q_NPN_BEC Q3
U 1 1 60A9E362
P 4200 7050
F 0 "Q3" H 4391 7004 50  0000 L CNN
F 1 "Q_NPN_BEC" H 4391 7095 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 4400 7150 50  0001 C CNN
F 3 "~" H 4200 7050 50  0001 C CNN
	1    4200 7050
	1    0    0    1   
$EndComp
Wire Wire Line
	4600 3450 5300 3450
Text Label 5300 3450 2    50   ~ 0
WAKE_UP
Text Label 2850 5650 0    50   ~ 0
WAKE_UP
Wire Wire Line
	4300 6200 5450 6200
$Comp
L Device:Q_NPN_BEC Q1
U 1 1 60BC62B6
P 4200 5950
F 0 "Q1" H 4391 5996 50  0000 L CNN
F 1 "Q_NPN_BEC" H 4391 5905 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 4400 6050 50  0001 C CNN
F 3 "~" H 4200 5950 50  0001 C CNN
	1    4200 5950
	1    0    0    -1  
$EndComp
Wire Wire Line
	4300 6150 4300 6200
Connection ~ 4300 6200
Wire Wire Line
	4300 5750 4300 5650
Wire Wire Line
	4300 5650 2850 5650
Wire Wire Line
	3350 6700 3350 5950
Connection ~ 3350 6700
$Comp
L Device:R R3
U 1 1 60BF9F09
P 3750 5950
F 0 "R3" V 3543 5950 50  0000 C CNN
F 1 "10k" V 3634 5950 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 3680 5950 50  0001 C CNN
F 3 "~" H 3750 5950 50  0001 C CNN
	1    3750 5950
	0    1    1    0   
$EndComp
Wire Wire Line
	4000 5950 3900 5950
Wire Wire Line
	3350 5950 3600 5950
Wire Wire Line
	4000 2100 3200 2100
Wire Wire Line
	3200 2100 3200 2200
Wire Wire Line
	3200 2500 3200 2700
$Comp
L power:+3V3 #PWR010
U 1 1 60D0F31D
P 4950 6850
F 0 "#PWR010" H 4950 6700 50  0001 C CNN
F 1 "+3V3" H 4965 7023 50  0000 C CNN
F 2 "" H 4950 6850 50  0001 C CNN
F 3 "" H 4950 6850 50  0001 C CNN
	1    4950 6850
	1    0    0    -1  
$EndComp
Connection ~ 4950 7300
Wire Wire Line
	4950 7300 5450 7300
Wire Wire Line
	4600 3350 4650 3350
Wire Wire Line
	4650 3350 4650 3550
Wire Wire Line
	4150 3900 4650 3900
Wire Wire Line
	4650 3900 4650 3850
Wire Wire Line
	7350 2300 6750 2300
Connection ~ 6750 2300
$Comp
L Device:C C2
U 1 1 60D4B72C
P 6250 2300
F 0 "C2" V 6502 2300 50  0000 C CNN
F 1 "100nF" V 6411 2300 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 6288 2150 50  0001 C CNN
F 3 "~" H 6250 2300 50  0001 C CNN
	1    6250 2300
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6100 2300 6000 2300
Wire Wire Line
	6000 2300 6000 3750
Wire Wire Line
	6000 3750 6550 3750
Wire Wire Line
	6400 2300 6550 2300
Wire Wire Line
	7350 2300 7350 3350
Text Label 6000 7550 0    50   ~ 0
I2C_CLK
Text Label 6000 7350 0    50   ~ 0
I2C_SDA
$Comp
L Device:R R8
U 1 1 60D6AC5D
P 6650 7100
F 0 "R8" H 6580 7146 50  0000 R CNN
F 1 "4k7" H 6580 7055 50  0000 R CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 6580 7100 50  0001 C CNN
F 3 "~" H 6650 7100 50  0001 C CNN
	1    6650 7100
	-1   0    0    -1  
$EndComp
Wire Wire Line
	6650 7350 6000 7350
Wire Wire Line
	6650 7250 6650 7350
$Comp
L Device:R R9
U 1 1 60D714B3
P 6950 7100
F 0 "R9" H 6880 7146 50  0000 R CNN
F 1 "4k7" H 6880 7055 50  0000 R CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 6880 7100 50  0001 C CNN
F 3 "~" H 6950 7100 50  0001 C CNN
	1    6950 7100
	-1   0    0    -1  
$EndComp
Wire Wire Line
	6950 7250 6950 7550
Wire Wire Line
	6000 7550 6950 7550
Wire Wire Line
	6800 6800 6650 6800
Wire Wire Line
	6650 6800 6650 6950
Wire Wire Line
	6800 6800 6950 6800
Wire Wire Line
	6950 6800 6950 6950
Connection ~ 6800 6800
Wire Wire Line
	6800 6700 6800 6800
Wire Notes Line
	6450 7750 7250 7750
Wire Notes Line
	7250 7750 7250 6400
Wire Notes Line
	7250 6400 6450 6400
Wire Notes Line
	6450 6400 6450 7750
Text Notes 6450 6350 0    50   ~ 0
I²C Pull Ups
$Comp
L Connector_Generic:Conn_01x06 J2
U 1 1 60DD9688
P 1150 4100
F 0 "J2" H 1068 3575 50  0000 C CNN
F 1 "Conn_01x06" H 1068 3666 50  0000 C CNN
F 2 "xrstf:PinHeader_1x06_P2.54mm_Vertical" H 1150 4100 50  0001 C CNN
F 3 "~" H 1150 4100 50  0001 C CNN
	1    1150 4100
	-1   0    0    1   
$EndComp
Wire Notes Line
	2800 2350 2800 1150
Wire Notes Line
	2800 1150 700  1150
Wire Notes Line
	700  1150 700  2350
Wire Notes Line
	700  2350 2800 2350
Text Notes 700  1100 0    100  ~ 0
AC Power In
$Comp
L power:+3V3 #PWR01
U 1 1 60DE945E
P 1550 3600
F 0 "#PWR01" H 1550 3450 50  0001 C CNN
F 1 "+3V3" H 1565 3773 50  0000 C CNN
F 2 "" H 1550 3600 50  0001 C CNN
F 3 "" H 1550 3600 50  0001 C CNN
	1    1550 3600
	1    0    0    -1  
$EndComp
$Comp
L power:GNDREF #PWR02
U 1 1 60DE9B71
P 1650 4450
F 0 "#PWR02" H 1650 4200 50  0001 C CNN
F 1 "GNDREF" H 1655 4277 50  0000 C CNN
F 2 "" H 1650 4450 50  0001 C CNN
F 3 "" H 1650 4450 50  0001 C CNN
	1    1650 4450
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1350 4300 1550 4300
Wire Wire Line
	1550 4300 1550 3600
Wire Wire Line
	1350 4200 1650 4200
Wire Wire Line
	1650 4200 1650 4450
Wire Wire Line
	1350 4100 2150 4100
Text Label 2150 4100 2    50   ~ 0
TXD
Wire Wire Line
	1350 4000 2150 4000
Wire Wire Line
	1350 3900 2150 3900
Wire Wire Line
	1350 3800 2150 3800
Text Label 2150 4000 2    50   ~ 0
RXD
Text Label 2150 3900 2    50   ~ 0
DTR
Text Label 2150 3800 2    50   ~ 0
RTS
Wire Notes Line
	1900 4750 1900 3300
Wire Notes Line
	1900 3300 900  3300
Wire Notes Line
	900  3300 900  4750
Wire Notes Line
	900  4750 1900 4750
Text Notes 900  3250 0    100  ~ 0
Progr. Port
Wire Wire Line
	3400 3300 2550 3300
Text Label 2550 3300 0    50   ~ 0
BATT_SENS
Wire Wire Line
	4000 1600 4000 2100
$Comp
L power:+3V3 #PWR05
U 1 1 60FC6BB7
P 2600 1450
F 0 "#PWR05" H 2600 1300 50  0001 C CNN
F 1 "+3V3" H 2615 1623 50  0000 C CNN
F 2 "" H 2600 1450 50  0001 C CNN
F 3 "" H 2600 1450 50  0001 C CNN
	1    2600 1450
	1    0    0    -1  
$EndComp
Wire Wire Line
	2450 1650 2600 1650
Wire Wire Line
	2600 1650 2600 1450
$Comp
L power:GNDREF #PWR06
U 1 1 60FCB4EB
P 2600 2050
F 0 "#PWR06" H 2600 1800 50  0001 C CNN
F 1 "GNDREF" H 2605 1877 50  0000 C CNN
F 2 "" H 2600 2050 50  0001 C CNN
F 3 "" H 2600 2050 50  0001 C CNN
	1    2600 2050
	-1   0    0    -1  
$EndComp
Wire Wire Line
	2450 1850 2600 1850
Wire Wire Line
	2600 1850 2600 2050
$Comp
L Connector:Screw_Terminal_01x02 J1
U 1 1 60FD4D44
P 1100 1700
F 0 "J1" H 1100 1500 50  0000 C CNN
F 1 "Screw_Terminal_01x02" H 1050 1900 50  0000 C CNN
F 2 "TerminalBlock_Philmore:TerminalBlock_Philmore_TB132_1x02_P5.00mm_Horizontal" H 1100 1700 50  0001 C CNN
F 3 "~" H 1100 1700 50  0001 C CNN
	1    1100 1700
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1300 1700 1400 1700
Wire Wire Line
	1400 1700 1400 1650
Wire Wire Line
	1400 1650 1650 1650
Wire Wire Line
	1300 1800 1400 1800
Wire Wire Line
	1400 1800 1400 1850
Wire Wire Line
	1400 1850 1650 1850
Text Label 1650 1650 2    50   ~ 0
AC_L
Text Label 1650 1850 2    50   ~ 0
AC_N
$Comp
L Converter_ACDC:IRM-03-3.3 PS1
U 1 1 6115D7F4
P 2050 1750
F 0 "PS1" H 2050 2117 50  0000 C CNN
F 1 "IRM-03-3.3" H 2050 2026 50  0000 C CNN
F 2 "Converter_ACDC:Converter_ACDC_MeanWell_IRM-03-xx_THT" H 2050 1400 50  0001 C CNN
F 3 "https://www.meanwell.com/Upload/PDF/IRM-03/IRM-03-SPEC.PDF" H 2050 1350 50  0001 C CNN
	1    2050 1750
	1    0    0    -1  
$EndComp
$Comp
L Device:Q_NPN_BEC Q4
U 1 1 611A415E
P 6650 5250
F 0 "Q4" H 6841 5296 50  0000 L CNN
F 1 "Q_NPN_BEC" H 6841 5205 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 6850 5350 50  0001 C CNN
F 3 "~" H 6650 5250 50  0001 C CNN
	1    6650 5250
	1    0    0    -1  
$EndComp
Text Label 5300 3050 2    50   ~ 0
SENS_PWR
Wire Wire Line
	5300 3050 4600 3050
Text Label 5850 5250 0    50   ~ 0
SENS_PWR
Wire Wire Line
	5850 5250 6450 5250
$Comp
L power:+3V3 #PWR014
U 1 1 611AD9EB
P 6750 4900
F 0 "#PWR014" H 6750 4750 50  0001 C CNN
F 1 "+3V3" H 6765 5073 50  0000 C CNN
F 2 "" H 6750 4900 50  0001 C CNN
F 3 "" H 6750 4900 50  0001 C CNN
	1    6750 4900
	1    0    0    -1  
$EndComp
Wire Wire Line
	6750 5050 6750 4900
$Comp
L power:+3.3VP #PWR015
U 1 1 611B333D
P 6750 5600
F 0 "#PWR015" H 6900 5550 50  0001 C CNN
F 1 "+3.3VP" H 6765 5773 50  0000 C CNN
F 2 "" H 6750 5600 50  0001 C CNN
F 3 "" H 6750 5600 50  0001 C CNN
	1    6750 5600
	-1   0    0    1   
$EndComp
Wire Wire Line
	6750 5450 6750 5600
Wire Notes Line
	7350 5850 7350 4650
Wire Notes Line
	7350 4650 6350 4650
Wire Notes Line
	6350 4650 6350 5850
Wire Notes Line
	6350 5850 7350 5850
Text Notes 6350 4600 0    50   ~ 0
Sensor Power Mngt
$Comp
L power:+3.3VP #PWR011
U 1 1 611D535E
P 6550 2150
F 0 "#PWR011" H 6700 2100 50  0001 C CNN
F 1 "+3.3VP" H 6565 2323 50  0000 C CNN
F 2 "" H 6550 2150 50  0001 C CNN
F 3 "" H 6550 2150 50  0001 C CNN
	1    6550 2150
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3VP #PWR?
U 1 1 611D9307
P 6800 6700
F 0 "#PWR?" H 6950 6650 50  0001 C CNN
F 1 "+3.3VP" H 6815 6873 50  0000 C CNN
F 2 "" H 6800 6700 50  0001 C CNN
F 3 "" H 6800 6700 50  0001 C CNN
	1    6800 6700
	1    0    0    -1  
$EndComp
$EndSCHEMATC
