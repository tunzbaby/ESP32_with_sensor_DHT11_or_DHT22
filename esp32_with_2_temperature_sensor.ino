#include "DHT.h"

#define DHTPIN 4     // Digital pin connected to the DHT sensor ~ GPIO 4ESP32 for ESP32
#define DHTPIN_22 0     // Digital pin connected to the DHT22 sensor ~ GPIO 0 for 
// ESP32 ~ GPIO4
// Feather HUZZAH ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --
// Pin 15 can work but DHT must be disconnected during program upload.

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE_2 DHT11 // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
// to 3.3V instead of 5V!
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

// Initialize DHT sensor.
// Note that older versions of this library took an optional third parameter to
// tweak the timings for faster processors.  This parameter is no longer needed
// as the current DHT reading algorithm adjusts itself to work on faster procs.
DHT dht(DHTPIN, DHTTYPE);
DHT dht_22(DHTPIN_22, DHTTYPE_2);

void setup() {
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));
  dht.begin(); // DHT11 (1) enable
  dht_22.begin(); // DHT11 (2) 
}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float dht_h = dht.readHumidity();
  float dht_t = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(dht_h) || isnan(dht_t)) {
    Serial.println(F("Failed to read from DHT(IN) sensor!"));
    return;
  }
  /*Result of DHT11 sensor*/
  /*Temperature sensor on Sever*/
  Serial.print(F("DHT(IN) - H: "));
  Serial.print(dht_h);
  Serial.print(F("% ,T: "));
  Serial.print(dht_t);
  Serial.print(F("°C and "));
  
  /* Sensor DH11 (2)*/
  float dht22_h = dht_22.readHumidity();
  float dht22_t = dht_22.readTemperature();
  if (isnan(dht22_h) || isnan(dht22_t)) {
    Serial.println(F("Failed to read from DHT(OUT) sensor!"));
    return;
  }
  /*Result of DHT(OUT) sensor*/
  /*Temperature sensor on outside*/
  Serial.print(F("DHT(OUT)- H: "));
  Serial.print(dht22_h);
  Serial.print(F("% ,T: "));
  Serial.print(dht22_t);
  Serial.println(F("°C "));

  /*Code logic chay tai day*/
  float delta_temp = dht_t - dht22_t;
  if ((delta_temp > 1) and (delta_temp < 4))
  {
    Serial.print(F("Chenh lech = "));
    Serial.print(delta_temp);
    Serial.println(F("°C "));
    Serial.println(F("Mo cua"));
  }
  else
  {
    Serial.print(F("Chenh lech = "));
    Serial.print(delta_temp);
    Serial.println(F("°C "));
    Serial.println(F("Dong cua"));
  }
 
}
