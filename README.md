# Peltier Cooling for Test Modules
## Introduction
Peltier cooling system and PID control loop. The peltier_cooling program can be called with optional parameters to define the ports for the Arduino and Bk16XXPs power supply, respectively. For example:

./peltier_cooling /dev/ttyACM0 /dev/ttyUSB0

The default ports are: Arduino - /dev/ttyACM0 ; PS - /dev/ttyUSB0

The arduinoTemp.ino program should be uploaded to the Arduino first. The Arduino makes temperature calculations and sends them continuously. The peltier_cooling program parses the measurements and accepts the most recent, complete temperature reading.

This project requires labRemote as a submodule.

## Materials
* 2 x CP85438 (Peltier devices; $23 each): [https://www.digikey.com/product-detail/en/cui-inc/CP85438/102-1682-ND/1747374](https://www.digikey.com/product-detail/en/cui-inc/CP85438/102-1682-ND/1747374)
* 1 x 1688B (single-channel DC power supply; $367): [https://www.digikey.com/product-detail/en/b-k-precision/1688B/BK1688B-ND/3476792](https://www.digikey.com/product-detail/en/b-k-precision/1688B/BK1688B-ND/3476792)
* 1 x MF52C1103F3380 (NTC thermistor; $2): [https://www.digikey.com/product-detail/en/cantherm/MF52C1103F3380/317-1376-ND/1840604](https://www.digikey.com/product-detail/en/cantherm/MF52C1103F3380/317-1376-ND/1840604)
* 1 x Arduino Mega 2560 ($30): [https://store.arduino.cc/usa/mega-2560-r3](https://store.arduino.cc/usa/mega-2560-r3)
* 1 x SparkFun ProtoShield v2 ($11): [https://www.sparkfun.com/products/13820](https://www.sparkfun.com/products/13820)
* 1 x Corsair H115i (CPU liquid cooler; $134): [https://www.corsair.com/us/en/Categories/Products/Liquid-Cooling/Dual-Radiator-Liquid-Coolers/Hydro-Series%E2%84%A2-H115i-280mm-Extreme-Performance-Liquid-CPU-Cooler/p/CW-9060027-WW](https://www.corsair.com/us/en/Categories/Products/Liquid-Cooling/Dual-Radiator-Liquid-Coolers/Hydro-Series%E2%84%A2-H115i-280mm-Extreme-Performance-Liquid-CPU-Cooler/p/CW-9060027-WW)
* 2 x NH0503R000FC02 (3 ohm, 50 watt resistor; $15 each): [https://www.mouser.com/ProductDetail/Vishay-Dale/NH0503R000FC02?qs=sGAEpiMZZMtbXrIkmrvidIBArrzlwrMErhRuYEXc72g%3D](https://www.mouser.com/ProductDetail/Vishay-Dale/NH0503R000FC02?qs=sGAEpiMZZMtbXrIkmrvidIBArrzlwrMErhRuYEXc72g%3D)
* 1 x NH0506R000FE02 (6 ohm, 50 watt resistor; $15): [https://www.mouser.com/ProductDetail/Vishay-Dale/NH0506R000FE02?qs=sGAEpiMZZMtbXrIkmrvidDNaDpN5VXc5shjJv5Q4YpI%3D](https://www.mouser.com/ProductDetail/Vishay-Dale/NH0506R000FE02?qs=sGAEpiMZZMtbXrIkmrvidDNaDpN5VXc5shjJv5Q4YpI%3D)

## Troubleshooting
`Resource temporarily unavailable`  
A blocking/non-blocking socket error. Make sure Serial Monitor is closed in Arduino Studio and that the program is not already running in a different window.