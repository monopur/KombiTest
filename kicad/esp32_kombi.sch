EESchema Schematic File Version 4
EELAYER 29 0
EELAYER END
$Descr A3 16535 11700
encoding utf-8
Sheet 1 1
Title "ESP32 Kombi Test Cihazı"
Date "2025-06-01"
Rev "A"
Comp "monopur"
$EndDescr
$Comp
L ESP32-DEV U1
U 1 1 00000001
P 2500 2000
F 0 "U1" H 2500 1950 50  0000 C CNN
F 1 "ESP32-DEV" H 2500 2050 50  0000 C CNN
F 2 "Module:ESP32-DevKitC" H 2500 2200 50  0001 C CNN
F 3 "" H 2500 2000 50  0001 C CNN
	1    2500 2000
	1    0    0    -1
$EndComp
$Comp
L Display_OLED:SSD1306 I2C_OLED1
U 1 1 00000002
P 4500 1800
F 0 "I2C_OLED1" H 4500 1750 50  0000 C CNN
F 1 "SSD1306" H 4500 1850 50  0000 C CNN
F 2 "Display:OLED-128x64-I2C" H 4500 2000 50  0001 C CNN
F 3 "" H 4500 1800 50  0001 C CNN
	1    4500 1800
	1    0    0    -1
$EndComp
# Buraya diğer bileşenler (ör: röle, MOSFET, dijital pot, encoder, ACS712, vs.) eklenir.
# ... diğer netler ve bileşenler ...
$Comp
L TestPoint TP_BOSCH_RX
U 1 1 60C6A011
P 9000 3200
F 0 "TP_BOSCH_RX" V 9000 3350 50  0000 C CNN
F 1 "BOSCH_RX" H 9000 3200 50  0000 C CNN
	1    9000 3200
	1    0    0    -1
$EndComp
$Comp
L TestPoint TP_BOSCH_TX
U 1 1 60C6A012
P 9000 3400
F 0 "TP_BOSCH_TX" V 9000 3550 50  0000 C CNN
F 1 "BOSCH_TX" H 9000 3400 50  0000 C CNN
	1    9000 3400
	1    0    0    -1
$EndComp
# ... bağlantılar, netler ...
$EndSCHEMATC
