/* IRremoteESP8266: IRsendDemo - demonstrates sending IR codes with IRsend.
 *
 * Version 1.1 January, 2019
 * Based on Ken Shirriff's IrsendDemo Version 0.1 July, 2009,
 * Copyright 2009 Ken Shirriff, http://arcfn.com
 *
 * An IR LED circuit *MUST* be connected to the ESP8266 on a pin
 * as specified by kIrLed below.
 *
 * TL;DR: The IR LED needs to be driven by a transistor for a good result.
 *
 * Suggested circuit:
 *     https://github.com/crankyoldgit/IRremoteESP8266/wiki#ir-sending
 *
 * Common mistakes & tips:
 *   * Don't just connect the IR LED directly to the pin, it won't
 *     have enough current to drive the IR LED effectively.
 *   * Make sure you have the IR LED polarity correct.
 *     See: https://learn.sparkfun.com/tutorials/polarity/diode-and-led-polarity
 *   * Typical digital camera/phones can be used to see if the IR LED is flashed.
 *     Replace the IR LED with a normal LED if you don't have a digital camera
 *     when debugging.
 *   * Avoid using the following pins unless you really know what you are doing:
 *     * Pin 0/D3: Can interfere with the boot/program mode & support circuits.
 *     * Pin 1/TX/TXD0: Any serial transmissions from the ESP8266 will interfere.
 *     * Pin 3/RX/RXD0: Any serial transmissions to the ESP8266 will interfere.
 *   * ESP-01 modules are tricky. We suggest you use a module with more GPIOs
 *     for your first time. e.g. ESP-12 etc.
 */

#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>

const uint16_t kIrLed = 4;  // ESP8266 GPIO pin to use. Recommended: 4 (D2).

IRsend irsend(kIrLed);  // Set the GPIO to be used to sending the message.

// Example of data captured by IRrecvDumpV2.ino
uint16_t rawData[439] = {3518, 1736,  368, 474,  390, 1332,  466, 400,  466, 400,  466, 400,  466, 396,  392, 474,  466, 404,  466, 400,  392, 472,  468, 422,  440, 400,  466, 398,  466, 1260,  468, 396,  466, 404,  392, 474,  464, 400,  466, 400,  456, 408,  468, 400,  464, 1258,  458, 1266,  466, 1260,  392, 474,  390, 474,  466, 1256,  468, 398,  468, 398,  390, 474,  466, 398,  466, 404,  464, 400,  466, 398,  390, 472,  392, 498,  442, 398,  466, 396,  468, 400,  468, 402,  466, 424,  366, 474,  390, 472,  466, 398,  392, 474,  392, 476,  388, 474,  392, 478,  392, 472,  392, 472,  392, 474,  390, 474,  390, 498,  366, 474,  392, 472,  392, 478,  466, 400,  392, 1332,  468, 1254,  468, 398,  468, 400,  390, 476,  390, 474,  390, 476,  392, 10000,  3426, 1802,  392, 474,  390, 1332,  466, 398,  392, 474,  466, 400,  464, 398,  468, 398,  392, 480,  390, 474,  466, 398,  468, 398,  466, 400,  390, 474,  390, 1332,  466, 398,  392, 480,  390, 472,  392, 474,  466, 398,  390, 472,  392, 474,  390, 1330,  470, 1256,  466, 1260,  392, 472,  468, 398,  390, 1332,  466, 400,  466, 400,  390, 474,  468, 396,  466, 404,  470, 396,  468, 398,  468, 398,  390, 474,  466, 398,  468, 398,  468, 398,  464, 404,  468, 1256,  466, 400,  466, 398,  466, 398,  466, 1258,  466, 1254,  468, 400,  390, 478,  468, 400,  464, 1228,  496, 1256,  468, 398,  466, 1256,  392, 1330,  392, 474,  466, 402,  366, 500,  466, 400,  464, 398,  468, 398,  390, 472,  392, 472,  392, 474,  392, 1350,  392, 472,  392, 474,  466, 398,  392, 474,  392, 474,  390, 1330,  392, 474,  392, 1336,  468, 398,  466, 400,  464, 398,  466, 400,  390, 474,  466, 400,  390, 472,  392, 478,  392, 474,  390, 474,  392, 472,  368, 498,  392, 472,  366, 498,  394, 474,  392, 478,  392, 474,  392, 1332,  392, 1330,  368, 498,  392, 472,  392, 474,  392, 472,  392, 478,  392, 472,  392, 472,  392, 474,  392, 472,  392, 472,  392, 1330,  392, 1332,  392, 478,  392, 472,  392, 474,  390, 474,  392, 474,  390, 474,  390, 474,  392, 472,  392, 478,  392, 472,  392, 474,  466, 400,  392, 474,  390, 472,  392, 474,  392, 474,  392, 478,  392, 474,  364, 500,  390, 474,  392, 474,  390, 474,  466, 398,  392, 474,  392, 1336,  392, 472,  392, 472,  392, 474,  390, 474,  392, 474,  392, 474,  392, 472,  392, 478,  366, 498,  392, 1332,  392, 1332,  392, 474,  392, 472,  392, 474,  366, 500,  390, 478,  392, 1332,  392, 472,  392, 474,  392, 1330,  392, 1332,  392, 1332,  390, 1332,  392, 500,  366};
// Example Samsung A/C state captured from IRrecvDumpV2.ino
/*uint8_t samsungState[kSamsungAcStateLength] = {
    0x02, 0x92, 0x0F, 0x00, 0x00, 0x00, 0xF0,
    0x01, 0xE2, 0xFE, 0x71, 0x40, 0x11, 0xF0};
*/
void setup() {
  irsend.begin();
/*
#if ESP8266
  Serial.begin(115200, SERIAL_8N1, SERIAL_TX_ONLY);
#else  // ESP8266
*/  
  Serial.begin(115200, SERIAL_8N1);
//#endif  // ESP8266
}

void loop() {
  for(int i = 0; i<2; i++){
  irsend.sendRaw(rawData, 439, 38);  // Send a raw data capture at 38kHz.
  delay(2000);
  }
  Serial.println("ON");
  /*
  Serial.println("NEC");
  irsend.sendNEC(0x00FFE01FUL);
  delay(2000);
  Serial.println("Sony");
  irsend.sendSony(0xa90, 12, 2);  // 12 bits & 2 repeats
  delay(2000);
  Serial.println("a rawData capture from IRrecvDumpV2");
  irsend.sendRaw(rawData, 439, 38);  // Send a raw data capture at 38kHz.
  delay(2000);
  Serial.println("a Samsung A/C state from IRrecvDumpV2");
  irsend.sendSamsungAC(samsungState);
  delay(2000);
  */
}
