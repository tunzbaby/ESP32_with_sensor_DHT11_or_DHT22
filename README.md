# ESP32_with_sensor_DHT11_or_DHT22

Update 2020.12.31
Install before run:

+ Python
$ pyserial
$ esptool
$ update-alternatives --install /usr/bin/python python /usr/bin/python3 1 // Setup python3 mac dinh

+ Board:
ESP32

+ Lib:
IRremoteESP8266
DHT
ESP32 mail client

+ Ubuntu:
$ sudo chmod a+rw /dev/ttyUSB0


Update 2020.10.12
Monitor temperature and humidity on ESP32 using DHT11 or DHT22.
Component:
1. ESP32
2. DHT11 or DHT22
3. Resistor 10k

Connection:
ESP32 (GPIO4) ~ (PIN2) DHT11 or DHT22
ESP32 (GPIO4) ~ Resistor 10k ~ VCC (3.3V): Pull up resitor

IDE:
Arduino 1.8.13
Python 2.7
