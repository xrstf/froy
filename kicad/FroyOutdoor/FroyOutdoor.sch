EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A3 16535 11693
encoding utf-8
Sheet 1 1
Title "FroyOutdoor.sch"
Date "14 MAR 2021"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Wire Wire Line
	3500 5750 3400 5750
Wire Wire Line
	3100 5750 2700 5750
Text Label 2700 5750 0    50   ~ 0
LED
Wire Notes Line
	4250 6200 3000 6200
Wire Notes Line
	3000 6200 3000 5350
Wire Notes Line
	4250 5350 3000 5350
Wire Notes Line
	4250 5350 4250 6200
Text Notes 3000 5300 0    50   ~ 0
Status LED
Text Label 7400 6150 2    50   ~ 0
RST
$Comp
L Device:R R9
U 1 1 608F39ED
P 5700 6400
F 0 "R9" V 5493 6400 50  0000 C CNN
F 1 "12k" V 5584 6400 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 5630 6400 50  0001 C CNN
F 3 "~" H 5700 6400 50  0001 C CNN
	1    5700 6400
	0    1    1    0
$EndComp
Text Label 4800 6400 0    50   ~ 0
DTR
Text Label 4800 7000 0    50   ~ 0
RTS
Wire Notes Line
	7150 7400 7150 5450
Wire Notes Line
	7150 5450 5200 5450
Wire Notes Line
	5200 5450 5200 7400
Wire Notes Line
	5200 7400 7150 7400
Text Notes 5200 5400 0    50   ~ 0
auto-reset
Wire Wire Line
	6900 7150 6900 7250
$Comp
L Device:R R4
U 1 1 607C09B0
P 4650 3700
F 0 "R4" H 4580 3654 50  0000 R CNN
F 1 "10k" H 4580 3745 50  0000 R CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 4580 3700 50  0001 C CNN
F 3 "~" H 4650 3700 50  0001 C CNN
	1    4650 3700
	-1   0    0    1
$EndComp
$Comp
L Device:R R3
U 1 1 607A3701
P 6900 7000
F 0 "R3" H 6970 6954 50  0000 L CNN
F 1 "10k" H 6970 7045 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 6830 7000 50  0001 C CNN
F 3 "~" H 6900 7000 50  0001 C CNN
	1    6900 7000
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
L power:GNDREF #PWR014
U 1 1 60798272
P 4150 4050
F 0 "#PWR014" H 4150 3800 50  0001 C CNN
F 1 "GNDREF" H 4155 3877 50  0000 C CNN
F 2 "" H 4150 4050 50  0001 C CNN
F 3 "" H 4150 4050 50  0001 C CNN
	1    4150 4050
	-1   0    0    -1
$EndComp
Wire Wire Line
	4600 2650 5300 2650
NoConn ~ 4600 3050
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
F 2 "xrstf:ESP-WROOM-02U" H 5650 2700 50  0001 L CNN
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
	6900 6850 6900 6800
Wire Wire Line
	3800 5750 4050 5750
$Comp
L Device:LED D1
U 1 1 60871AC0
P 3650 5750
F 0 "D1" H 3643 5967 50  0000 C CNN
F 1 "STATUS" H 3643 5876 50  0000 C CNN
F 2 "LED_SMD:LED_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 3650 5750 50  0001 C CNN
F 3 "~" H 3650 5750 50  0001 C CNN
	1    3650 5750
	-1   0    0    -1
$EndComp
$Comp
L Device:R R5
U 1 1 607C9920
P 3250 5750
F 0 "R5" V 3043 5750 50  0000 C CNN
F 1 "2k2" V 3134 5750 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 3180 5750 50  0001 C CNN
F 3 "~" H 3250 5750 50  0001 C CNN
	1    3250 5750
	0    -1   1    0
$EndComp
Wire Wire Line
	4600 2950 5300 2950
Text Label 5300 2950 2    50   ~ 0
LED
$Comp
L Device:R R8
U 1 1 6086724D
P 5700 7000
F 0 "R8" V 5815 7000 50  0000 C CNN
F 1 "12k" V 5906 7000 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 5630 7000 50  0001 C CNN
F 3 "~" H 5700 7000 50  0001 C CNN
	1    5700 7000
	0    1    1    0
$EndComp
Wire Wire Line
	5850 6400 5950 6400
Wire Wire Line
	5950 7000 5850 7000
Wire Wire Line
	6250 6800 6250 6750
Wire Wire Line
	6250 6750 5400 6750
Wire Wire Line
	5400 6400 5550 6400
Wire Wire Line
	4800 6400 5400 6400
Connection ~ 5400 6400
Wire Wire Line
	6250 6600 6250 6650
Wire Wire Line
	6250 6650 5300 6650
Wire Wire Line
	5400 6400 5400 6750
Wire Wire Line
	6250 6200 6250 6150
Wire Wire Line
	6250 7250 6900 7250
Text Label 7400 7250 2    50   ~ 0
IO0
Wire Wire Line
	4800 7000 5300 7000
Wire Wire Line
	5300 6650 5300 7000
Connection ~ 5300 7000
Wire Wire Line
	5300 7000 5550 7000
Wire Wire Line
	6250 7200 6250 7250
$Comp
L power:GNDREF #PWR0101
U 1 1 60995317
P 4050 5900
F 0 "#PWR0101" H 4050 5650 50  0001 C CNN
F 1 "GNDREF" H 4055 5727 50  0000 C CNN
F 2 "" H 4050 5900 50  0001 C CNN
F 3 "" H 4050 5900 50  0001 C CNN
	1    4050 5900
	1    0    0    -1
$EndComp
Wire Wire Line
	4050 5750 4050 5900
$Comp
L Switch:SW_SPST SW1
U 1 1 60A341F2
P 3500 6950
F 0 "SW1" H 3500 7185 50  0000 C CNN
F 1 "SW_SPST" H 3500 7094 50  0000 C CNN
F 2 "Button_Switch_SMD:SW_SPST_CK_RS282G05A3" H 3500 6950 50  0001 C CNN
F 3 "~" H 3500 6950 50  0001 C CNN
	1    3500 6950
	1    0    0    -1
$EndComp
Wire Wire Line
	3300 6950 2900 6950
Text Label 2900 6950 0    50   ~ 0
RST
$Comp
L power:GNDREF #PWR04
U 1 1 60A40159
P 3800 7150
F 0 "#PWR04" H 3800 6900 50  0001 C CNN
F 1 "GNDREF" H 3805 6977 50  0000 C CNN
F 2 "" H 3800 7150 50  0001 C CNN
F 3 "" H 3800 7150 50  0001 C CNN
	1    3800 7150
	1    0    0    -1
$EndComp
Wire Wire Line
	3700 6950 3800 6950
Wire Wire Line
	3800 6950 3800 7150
Wire Notes Line
	3150 7450 4050 7450
Wire Notes Line
	4050 7450 4050 6600
Wire Notes Line
	4050 6600 3150 6600
Wire Notes Line
	3150 6600 3150 7450
Text Notes 3150 6550 0    50   ~ 0
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
L power:GNDREF #PWR012
U 1 1 60A5BC96
P 4650 2200
F 0 "#PWR012" H 4650 1950 50  0001 C CNN
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
L Sensor:BME280 U2
U 1 1 60AA4898
P 6650 3050
F 0 "U2" H 6221 3096 50  0000 R CNN
F 1 "BME280" H 6750 3050 50  0000 R CNN
F 2 "xrstf:BME280_680_BMP280" H 8150 2600 50  0001 C CNN
F 3 "https://ae-bst.resource.bosch.com/media/_tech/media/datasheets/BST-BME280-DS002.pdf" H 6650 2850 50  0001 C CNN
	1    6650 3050
	1    0    0    -1
$EndComp
$Comp
L power:GNDREF #PWR015
U 1 1 60AA5A53
P 6550 3900
F 0 "#PWR015" H 6550 3650 50  0001 C CNN
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
L power:+3V3 #PWR0103
U 1 1 60A86F8A
P 6550 2150
F 0 "#PWR0103" H 6550 2000 50  0001 C CNN
F 1 "+3V3" H 6565 2323 50  0000 C CNN
F 2 "" H 6550 2150 50  0001 C CNN
F 3 "" H 6550 2150 50  0001 C CNN
	1    6550 2150
	1    0    0    -1
$EndComp
$Comp
L power:+3V3 #PWR0106
U 1 1 60A8BC25
P 4000 1600
F 0 "#PWR0106" H 4000 1450 50  0001 C CNN
F 1 "+3V3" H 4015 1773 50  0000 C CNN
F 2 "" H 4000 1600 50  0001 C CNN
F 3 "" H 4000 1600 50  0001 C CNN
	1    4000 1600
	1    0    0    -1
$EndComp
$Comp
L Device:Q_NPN_BEC Q1
U 1 1 60A9DA12
P 6150 6400
F 0 "Q1" H 6341 6446 50  0000 L CNN
F 1 "Q_NPN_BEC" H 6341 6355 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 6350 6500 50  0001 C CNN
F 3 "~" H 6150 6400 50  0001 C CNN
	1    6150 6400
	1    0    0    -1
$EndComp
$Comp
L Device:Q_NPN_BEC Q2
U 1 1 60A9E362
P 6150 7000
F 0 "Q2" H 6341 6954 50  0000 L CNN
F 1 "Q_NPN_BEC" H 6341 7045 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 6350 7100 50  0001 C CNN
F 3 "~" H 6150 7000 50  0001 C CNN
	1    6150 7000
	1    0    0    1
$EndComp
Wire Wire Line
	4600 3450 5300 3450
Text Label 5300 3450 2    50   ~ 0
WAKE_UP
Text Label 4800 5600 0    50   ~ 0
WAKE_UP
Wire Wire Line
	6250 6150 7400 6150
$Comp
L Device:Q_NPN_BEC Q3
U 1 1 60BC62B6
P 6150 5900
F 0 "Q3" H 6341 5946 50  0000 L CNN
F 1 "Q_NPN_BEC" H 6341 5855 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 6350 6000 50  0001 C CNN
F 3 "~" H 6150 5900 50  0001 C CNN
	1    6150 5900
	1    0    0    -1
$EndComp
Wire Wire Line
	6250 6100 6250 6150
Connection ~ 6250 6150
Wire Wire Line
	6250 5700 6250 5600
Wire Wire Line
	6250 5600 4800 5600
Wire Wire Line
	5300 6650 5300 5900
Connection ~ 5300 6650
$Comp
L Device:R R11
U 1 1 60BF9F09
P 5700 5900
F 0 "R11" V 5493 5900 50  0000 C CNN
F 1 "12k" V 5584 5900 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 5630 5900 50  0001 C CNN
F 3 "~" H 5700 5900 50  0001 C CNN
	1    5700 5900
	0    1    1    0
$EndComp
Wire Wire Line
	5950 5900 5850 5900
Wire Wire Line
	5300 5900 5550 5900
$Comp
L Device:Battery_Cell BT1
U 1 1 60CE3F05
P 1300 1950
F 0 "BT1" H 1418 2046 50  0000 L CNN
F 1 "CR123A" H 1418 1955 50  0000 L CNN
F 2 "xrstf:CR123A_Holder_ThroughHole" H 1050 1650 50  0001 L BNN
F 3 "MPD" H 1300 1950 50  0001 L BNN
	1    1300 1950
	1    0    0    -1
$EndComp
Wire Wire Line
	4000 2100 3200 2100
Wire Wire Line
	3200 2100 3200 2200
Wire Wire Line
	3200 2500 3200 2700
$Comp
L power:+3V3 #PWR07
U 1 1 60D0F31D
P 6900 6800
F 0 "#PWR07" H 6900 6650 50  0001 C CNN
F 1 "+3V3" H 6915 6973 50  0000 C CNN
F 2 "" H 6900 6800 50  0001 C CNN
F 3 "" H 6900 6800 50  0001 C CNN
	1    6900 6800
	1    0    0    -1
$EndComp
Connection ~ 6900 7250
Wire Wire Line
	6900 7250 7400 7250
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
Text Label 7900 6850 0    50   ~ 0
I2C_CLK
Text Label 7900 6650 0    50   ~ 0
I2C_SDA
$Comp
L Device:R R1
U 1 1 60D6AC5D
P 8550 6400
F 0 "R1" H 8480 6446 50  0000 R CNN
F 1 "4k7" H 8480 6355 50  0000 R CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 8480 6400 50  0001 C CNN
F 3 "~" H 8550 6400 50  0001 C CNN
	1    8550 6400
	-1   0    0    -1
$EndComp
Wire Wire Line
	8550 6650 7900 6650
Wire Wire Line
	8550 6550 8550 6650
$Comp
L Device:R R6
U 1 1 60D714B3
P 8850 6400
F 0 "R6" H 8780 6446 50  0000 R CNN
F 1 "4k7" H 8780 6355 50  0000 R CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 8780 6400 50  0001 C CNN
F 3 "~" H 8850 6400 50  0001 C CNN
	1    8850 6400
	-1   0    0    -1
$EndComp
Wire Wire Line
	8850 6550 8850 6850
Wire Wire Line
	7900 6850 8850 6850
$Comp
L power:+3V3 #PWR06
U 1 1 60D73F62
P 8700 6000
F 0 "#PWR06" H 8700 5850 50  0001 C CNN
F 1 "+3V3" H 8715 6173 50  0000 C CNN
F 2 "" H 8700 6000 50  0001 C CNN
F 3 "" H 8700 6000 50  0001 C CNN
	1    8700 6000
	1    0    0    -1
$EndComp
Wire Wire Line
	8700 6100 8550 6100
Wire Wire Line
	8550 6100 8550 6250
Wire Wire Line
	8700 6100 8850 6100
Wire Wire Line
	8850 6100 8850 6250
Connection ~ 8700 6100
Wire Wire Line
	8700 6000 8700 6100
Wire Notes Line
	8350 7050 9150 7050
Wire Notes Line
	9150 7050 9150 5700
Wire Notes Line
	9150 5700 8350 5700
Wire Notes Line
	8350 5700 8350 7050
Text Notes 8350 5650 0    50   ~ 0
I²C Pull Ups
$Comp
L Connector_Generic:Conn_01x06 J1
U 1 1 60DD9688
P 1150 4100
F 0 "J1" H 1068 3575 50  0000 C CNN
F 1 "Conn_01x06" H 1068 3666 50  0000 C CNN
F 2 "xrstf:PinHeader_1x06_P2.54mm_Vertical" H 1150 4100 50  0001 C CNN
F 3 "~" H 1150 4100 50  0001 C CNN
	1    1150 4100
	-1   0    0    1
$EndComp
$Comp
L power:+3V3 #PWR01
U 1 1 60DDB8FB
P 1300 1500
F 0 "#PWR01" H 1300 1350 50  0001 C CNN
F 1 "+3V3" H 1315 1673 50  0000 C CNN
F 2 "" H 1300 1500 50  0001 C CNN
F 3 "" H 1300 1500 50  0001 C CNN
	1    1300 1500
	1    0    0    -1
$EndComp
Wire Wire Line
	1300 1500 1300 1750
$Comp
L power:GNDREF #PWR02
U 1 1 60DDED01
P 1300 2250
F 0 "#PWR02" H 1300 2000 50  0001 C CNN
F 1 "GNDREF" H 1305 2077 50  0000 C CNN
F 2 "" H 1300 2250 50  0001 C CNN
F 3 "" H 1300 2250 50  0001 C CNN
	1    1300 2250
	-1   0    0    -1
$EndComp
Wire Wire Line
	1300 2050 1300 2250
Wire Notes Line
	1800 2550 1800 1200
Wire Notes Line
	1800 1200 1050 1200
Wire Notes Line
	1050 1200 1050 2550
Wire Notes Line
	1050 2550 1800 2550
Text Notes 1050 1150 0    100  ~ 0
Battery
$Comp
L power:+3V3 #PWR03
U 1 1 60DE945E
P 1550 3600
F 0 "#PWR03" H 1550 3450 50  0001 C CNN
F 1 "+3V3" H 1565 3773 50  0000 C CNN
F 2 "" H 1550 3600 50  0001 C CNN
F 3 "" H 1550 3600 50  0001 C CNN
	1    1550 3600
	1    0    0    -1
$EndComp
$Comp
L power:GNDREF #PWR05
U 1 1 60DE9B71
P 1650 4450
F 0 "#PWR05" H 1650 4200 50  0001 C CNN
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
$Comp
L Device:R R7
U 1 1 60E62BD0
P 1450 6100
F 0 "R7" H 1380 6146 50  0000 R CNN
F 1 "47k" H 1380 6055 50  0000 R CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 1380 6100 50  0001 C CNN
F 3 "~" H 1450 6100 50  0001 C CNN
	1    1450 6100
	-1   0    0    -1
$EndComp
$Comp
L Device:R R10
U 1 1 60E6326F
P 1450 6600
F 0 "R10" H 1380 6646 50  0000 R CNN
F 1 "22k" H 1380 6555 50  0000 R CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 1380 6600 50  0001 C CNN
F 3 "~" H 1450 6600 50  0001 C CNN
	1    1450 6600
	-1   0    0    -1
$EndComp
$Comp
L power:+3V3 #PWR08
U 1 1 60E636CB
P 1450 5800
F 0 "#PWR08" H 1450 5650 50  0001 C CNN
F 1 "+3V3" H 1465 5973 50  0000 C CNN
F 2 "" H 1450 5800 50  0001 C CNN
F 3 "" H 1450 5800 50  0001 C CNN
	1    1450 5800
	1    0    0    -1
$EndComp
Wire Wire Line
	1450 5800 1450 5950
Wire Wire Line
	1450 6250 1450 6350
Wire Wire Line
	1450 6350 750  6350
Connection ~ 1450 6350
Wire Wire Line
	1450 6350 1450 6450
Text Label 750  6350 0    50   ~ 0
BATT_SENS
$Comp
L power:GNDREF #PWR09
U 1 1 60E6FB45
P 1450 6950
F 0 "#PWR09" H 1450 6700 50  0001 C CNN
F 1 "GNDREF" H 1455 6777 50  0000 C CNN
F 2 "" H 1450 6950 50  0001 C CNN
F 3 "" H 1450 6950 50  0001 C CNN
	1    1450 6950
	1    0    0    -1
$EndComp
Wire Wire Line
	1450 6750 1450 6850
$Comp
L Device:C C3
U 1 1 60E7C120
P 1850 6600
F 0 "C3" H 1735 6554 50  0000 R CNN
F 1 "100nF" H 1735 6645 50  0000 R CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 1888 6450 50  0001 C CNN
F 3 "~" H 1850 6600 50  0001 C CNN
	1    1850 6600
	-1   0    0    1
$EndComp
Wire Wire Line
	1450 6350 1850 6350
Wire Wire Line
	1850 6350 1850 6450
Wire Wire Line
	1850 6750 1850 6850
Wire Wire Line
	1850 6850 1450 6850
Connection ~ 1450 6850
Wire Wire Line
	1450 6850 1450 6950
Wire Notes Line
	1250 7200 2300 7200
Wire Notes Line
	2300 7200 2300 5550
Wire Notes Line
	2300 5550 1250 5550
Wire Notes Line
	1250 5550 1250 7200
Text Notes 1250 5500 0    50   ~ 0
Battery Sensing
Text Notes 1050 7400 0    50   ~ 0
with 3.3V, this gives 0..1.05V on BATT_SENS\nTOUT is max 1.1V
Wire Wire Line
	4000 1600 4000 2100
$EndSCHEMATC