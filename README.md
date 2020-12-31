# ESP32_with_sensor_DHT11_or_DHT22

Update 2020.12.31<br>
Install before run:<br>
<br>
+ Python<br>
$ pyserial<br>
$ esptool<br>
$ update-alternatives --install /usr/bin/python python /usr/bin/python3 1 // Setup python3 mac dinh<br>

+ Board:<br>
ESP32<br>

+ Lib:<br>
IRremoteESP8266<br>
DHT<br>
ESP32 mail client<br>

+ Ubuntu:<br>
$ sudo chmod a+rw /dev/ttyUSB0<br>


Update 2020.10.12<br>
Monitor temperature and humidity on ESP32 using DHT11 or DHT22.<br>
Component:<br>
1. ESP32<br>
2. DHT11 or DHT22<br>
3. Resistor 10k<br>

Connection:<br>
ESP32 (GPIO4) ~ (PIN2) DHT11 or DHT22<br>
ESP32 (GPIO4) ~ Resistor 10k ~ VCC (3.3V): Pull up resitor<br>

IDE:<br>
Arduino 1.8.13<br>
Python 2.7<br>
