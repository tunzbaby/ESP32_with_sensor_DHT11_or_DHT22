/*
 * 1. @nhiet_do_va_do_am
 * 2. @dong_bo_thoi_gian
 * 3. @ir_dieu_khien
 * 4. @gui_email
 * 5. @LED_state // Trang thai led
 * 6. @Cua_ra_vao
 * 7. @Fan_control
 * 8. @test
 */

 /*
  * Lib: 
  * 1. IRremoteESP8266
  * 2. ESP32_MailClient
  */

/* PIN OUT ~ ESP32 ~ IR ~ 2 x DHT11 ~
 * GPIO32:
 * IR_send: GPIO_12 ~ DATA of IR send
 * LED_state_air: GPIO 26 ~ Res 300 Ohm ~ Anot of LED
 * LED_state_fan: GPIO 25 ~ Res 300 Ohm ~ Anot of LED
 * LED_state_door: GPIO 22 ~ Res 300 Ohm ~ Anot of LED
 * DHT11(in): GPIO_4 ~ RES 10k ~ VCC ~ Data DHT11(in)
 * DHT11(out): GPIO_0 ~ RES 10k ~ VCC ~ Data DHT11(out)
 */

//@ir_dieu_khien
#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
//@ir_dieu_khien

//@nhiet_do_va_do_am
#include "DHT.h"
//@nhiet_do_va_do_am

//@gui_email
#include "ESP32_MailClient.h"
//@gui_email

//@dong_bo_thoi_gian
#include <WiFi.h>
#include "time.h"
//@dong_bo_thoi_gian

//@dong_bo_thoi_gian
const char* ssid = "HYPERLOGY-Guest-02";
const char* password = "hyperlogy2019";
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 25200;
const int   daylightOffset_sec = 0;
//@dong_bo_thoi_gian

//@gui_email
#define emailSenderAccount    "tungpch1906001@fpt.edu.vn"    
#define emailSenderPassword   "Tung@1992"
#define emailRecipient        "phamtung@outlook.com"
#define smtpServer            "smtp.gmail.com"
#define smtpServerPort        465
#define emailSubject          "ESP32 Test"
//@gui_email

//@nhiet_do_va_do_am
#define DHTPIN_in 4     // Digital pin connected to the DHT sensor ~ GPIO 4ESP32 for ESP32
#define DHTPIN_out 0     // Digital pin connected to the DHT22 sensor ~ GPIO 0 for 
#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE_2 DHT11 // DHT 11
//@nhiet_do_va_do_am

//@LED_state
#define LED_state_air 26 // Digital pin connected to GPIO_26
#define LED_state_fan 25 // Digital Pin connected to GPIO_25
#define LED_state_door 32 // Digital Pin connected to GPIO_23
#define Door_sensor 17 // Digital pin input connected to GPIO_22
#define Fan_control 19 // Digital pin output connected to GPIO_19
#define Cua_dieu_khien 18 // Digital Pin output connected to GPIO_18
//@LED_state

//@gui_email
SMTPData smtpData; // The Email Sending data object contains config and data to send
void sendCallback(SendStatus info); // Callback function to get the Email sending status
//@gui_email

//@ir_dieu_khien
const uint16_t kIrLed = 12; // GPIO 12 ESP32
IRsend irsend(kIrLed);  // Set the GPIO to be used to sending the message.

/*@IR_data*/
//Power: On, Mode: 0 (Cool), Fan: 2 (Med), Temp: 25C, Zone Follow: Off, Sensor Temp: Off
uint16_t rawData[199] = {4330, 4400,  512, 1632,  512, 528,  542, 1630,  514, 1656,  486, 556,  514, 558,  514, 1656,  488, 584,  488, 558,  512, 1630,  512, 558,  512, 584,  488, 1656,  486, 1656,  488, 584,  486, 1654,  488, 556,  514, 1630,  514, 560,  512, 1630,  514, 1630,  512, 1630,  512, 1630,  514, 1630,  514, 1628,  540, 532,  514, 1628,  512, 558,  516, 582,  488, 556,  540, 556,  512, 558,  514, 1604,  512, 1630,  514, 556,  514, 556,  540, 530,  514, 584,  488, 582,  514, 530,  540, 532,  540, 530,  540, 1604,  538, 1630,  488, 1628,  542, 1602,  542, 1604,  540, 1630,  514, 5184,  4384, 4374,  538, 1606,  538, 558,  488, 1654,  514, 1630,  514, 530,  540, 532,  538, 1606,  538, 530,  540, 530,  540, 1630,  514, 556,  514, 532,  540, 1628,  514, 1628,  514, 506,  566, 1602,  540, 530,  542, 1602,  540, 532,  540, 1602,  540, 1628,  514, 1604,  538, 1630,  514, 1602,  542, 1604,  538, 530,  540, 1604,  538, 532,  540, 556,  514, 556,  514, 532,  540, 530,  542, 1604,  540, 1604,  540, 530,  542, 528,  542, 530,  540, 532,  540, 530,  540, 530,  540, 530,  540, 530,  542, 1602,  540, 1602,  540, 1602,  540, 1602,  540, 1602,  540, 1576,  568};
//Power: Off
uint16_t off_air[199] = {4378, 4402,  462, 1658,  510, 558,  512, 1658,  486, 1630,  512, 558,  512, 560,  510, 1632,  512, 584,  486, 534,  536, 1632,  510, 584,  486, 584,  462, 1682,  486, 1632,  486, 554,  542, 1632,  512, 532,  538, 1632,  510, 1632,  486, 1682,  462, 1682,  460, 586,  510, 1632,  486, 1658,  510, 1634,  510, 558,  512, 586,  462, 584,  486, 584,  486, 1656,  488, 584,  488, 584,  486, 1658,  510, 1632,  486, 1662,  482, 584,  488, 610,  462, 610,  484, 586,  462, 584,  486, 584,  510, 558,  488, 610,  462, 1656,  488, 1682,  462, 1656,  486, 1658,  486, 1656,  510, 5186,  4384, 4400,  512, 1658,  460, 584,  486, 1656,  512, 1658,  460, 584,  488, 584,  510, 1656,  462, 584,  486, 584,  488, 1682,  462, 582,  512, 532,  538, 1658,  460, 1658,  510, 560,  512, 1630,  488, 560,  536, 1630,  514, 1632,  512, 1632,  512, 1656,  462, 610,  462, 1682,  486, 1630,  514, 1630,  488, 584,  512, 556,  514, 530,  540, 584,  486, 1632,  514, 558,  512, 558,  512, 1656,  488, 1628,  512, 1656,  486, 560,  512, 582,  488, 556,  514, 558,  514, 532,  540, 556,  514, 560,  536, 532,  540, 1578,  538, 1630,  514, 1630,  512, 1628,  540, 1604,  514};
//@ir_dieu_khien

//@nhiet_do_va_do_am
DHT dht_in(DHTPIN_in, DHTTYPE);
DHT dht_out(DHTPIN_out, DHTTYPE_2);
//@nhiet_do_va_do_am

void setup() {
  irsend.begin(); //@ir_dieu_khien
  
  //@nhiet_do_va_do_am
  dht_in.begin(); // DHT11 (1) enable
  dht_out.begin(); // DHT11 (2) 
  //@nhiet_do_va_do_am
  
  //@Led_state
  pinMode(LED_state_air, OUTPUT);
  pinMode(LED_state_fan, OUTPUT);
  pinMode(LED_state_door, OUTPUT);
  pinMode(Fan_control, OUTPUT);
  pinMode(Door_sensor, INPUT);
  //@Led_state
  
  Serial.begin(115200, SERIAL_8N1);

   // @dong_bo_thoi_gian to Wi-Fi
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  
  // Init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  dong_bo_thoi_gian();

  //disconnect WiFi as it's no longer needed
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
  //@dong_bo_thoi_gian

  /*
  //@gui_email
  Serial.println("Preparing to send email");
  Serial.println();
  smtpData.setLogin(smtpServer, smtpServerPort, emailSenderAccount, emailSenderPassword);
  smtpData.setSender("ESP32", emailSenderAccount);
  // Set Email priority or importance High, Normal, Low or 1 to 5 (1 is highest)
  smtpData.setPriority("High");
  // Set the subject
  smtpData.setSubject(emailSubject);
  // Set the message with HTML format
  smtpData.setMessage("<div style=\"color:#2f4468;\"><h1>Hello World!</h1><p>- Sent from ESP32 board</p></div>", true);
  // Set the email message in text format (raw)
  //smtpData.setMessage("Hello World! - Sent from ESP32 board", false);
  // Add recipients, you can add more than one recipient
  smtpData.addRecipient(emailRecipient);
  //smtpData.addRecipient("YOUR_OTHER_RECIPIENT_EMAIL_ADDRESS@EXAMPLE.com");
  smtpData.setSendCallback(sendCallback);
  //Start sending Email, can be set callback function to track the status
  if (!MailClient.sendMail(smtpData))
  Serial.println("Error sending Email, " + MailClient.smtpErrorReason());
  //Clear all data from Email object to free memory
  smtpData.empty();
  //@gui_email
  */
}

void loop() {
  
  float dht_in_h = dht_in.readHumidity();
  float dht_in_t = dht_in.readTemperature();
  //DHT (out)
  float dht_out_h = dht_out.readHumidity();
  float dht_out_t = dht_out.readTemperature();
  
  if (dht_in_h > 35 || dht_out_h > 30) // Nếu nhiệt độ trong > 35 độ || (hoặc) Nhiệt độ ngoài > 30 độ
  {
    //state_air = 1; // Bật điều hòa
    bat_tat_dieu_hoa(1);
    //state_fan = 0; // Tắt quạt
    Quat_dieu_khien(0);
    //state_door = 1; // Đóng cửa
    Cua_trang_thai(1);
  }
  else
  {
    //state_air = 0; // Tắt điều hòa
    bat_tat_dieu_hoa(0);
    //state_fan = 1; // Bật quạt
    Quat_dieu_khien(1);
    //state_door = 0; // Mở cửa
    Cua_trang_thai(0);
  }
}

//@LED_state
void LED_state(bool state)
{
  if(state == 1){digitalWrite(LED_state_air, HIGH);}
  else{digitalWrite(LED_state_air, LOW);}
}

void Led_state_fan(bool state)
{
  if(state == 1){digitalWrite(LED_state_fan, HIGH);}
  else{digitalWrite(LED_state_fan, LOW);}
}

void Led_doors(bool state)
{
  if(state == 1){digitalWrite(LED_state_door, HIGH);}
  else{digitalWrite(LED_state_door, LOW);}
}
  
//@ir_dieu_khien
void bat_tat_dieu_hoa(bool state)
{
  if(state == 1)
  {
    irsend.sendRaw(rawData, 199, 38);
    Serial.println("Air on");
    Led_doors(1);
  }
  if(state == 0)
  {
    irsend.sendRaw(off_air, 199, 38);
    Serial.println("Air off");
    Led_doors(0);
  }  
}

//@Cua_ra_vao
void trang_thai_cua_ra_vao()
{
    if(digitalRead(Door_sensor) == LOW)
  {
    Serial.println(F("Cua dang dong"));
    Led_doors(1);
  }
  else
  {
    Serial.println(F("Cua dang mo"));
    Led_doors(0);
  }
}

//@Cua_dieu_khien
void Cua_trang_thai(bool state)
{
  if(state == 1)
  {
    digitalWrite(Cua_dieu_khien, HIGH);
    digitalWrite(LED_state_door, HIGH);
    Serial.println(F("Cua dong"));
  }
  else
  {
    digitalWrite(Cua_dieu_khien, LOW);
    digitalWrite(LED_state_door, LOW);
    Serial.println(F("Cua mo"));    
  }
}

//@Quat_dieu_khien
void Quat_dieu_khien(bool state)
{
  if(state == 1)
  {
    digitalWrite(Fan_control, HIGH);
    digitalWrite(LED_state_fan, HIGH);
    Serial.println(F("Quat chay"));
  }
  else
  {
    
    digitalWrite(Fan_control, LOW);
    digitalWrite(LED_state_fan, LOW);
    Serial.println(F("Quat tat"));
    
  }
}

//@nhiet_do_va_do_am
void nhiet_do_va_do_am()
{
  //1 - DHT in
  //0 - DHT out
  //DHT (in)
  float dht_in_h = dht_in.readHumidity();
  float dht_in_t = dht_in.readTemperature();
  //DHT (out)
  float dht_out_h = dht_out.readHumidity();
  float dht_out_t = dht_out.readTemperature();
  //Check neu xay ra loi
  if (isnan(dht_in_h) || isnan(dht_in_t)) 
  {
    Serial.println(F("Failed to read from DHT(IN) sensor!"));
    return;
  }
   if (isnan(dht_out_h) || isnan(dht_out_t)) 
  {
    Serial.println(F("Failed to read from DHT(OUT) sensor!"));
    return;
  }
  /*
  if(side == 1)
  {
    //dht_in_h;
    Serial.print(F("DHT(in) Temp: "));
    Serial.print(dht_in_t);
    Serial.println(F("°C"));
  }
  if(side == 0)
  {
    //dht_out_h;
    Serial.print(F("DHT(out) Temp: "));
    Serial.print(dht_out_t);
    Serial.println(F("°C"));
  }
  */
}

//@dong_bo_thoi_gian
void dong_bo_thoi_gian()
{
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
  Serial.print("Day of week: ");
  Serial.println(&timeinfo, "%A");
  Serial.print("Month: ");
  Serial.println(&timeinfo, "%B");
  Serial.print("Day of Month: ");
  Serial.println(&timeinfo, "%d");
  Serial.print("Year: ");
  Serial.println(&timeinfo, "%Y");
  Serial.print("Hour: ");
  Serial.println(&timeinfo, "%H");
  Serial.print("Hour (12 hour format): ");
  Serial.println(&timeinfo, "%I");
  Serial.print("Minute: ");
  Serial.println(&timeinfo, "%M");
  Serial.print("Second: ");
  Serial.println(&timeinfo, "%S");

  Serial.println("Time variables");
  char timeHour[3];
  strftime(timeHour,3, "%H", &timeinfo);
  Serial.println(timeHour);
  char timeWeekDay[10];
  strftime(timeWeekDay,10, "%A", &timeinfo);
  Serial.println(timeWeekDay);
  Serial.println();
}
//@dong_bo_thoi_gian

//@gui_email
// Callback function to get the Email sending status
void sendCallback(SendStatus msg) {
  // Print the current status
  Serial.println(msg.info());

  // Do something when complete
  if (msg.success()) {
    Serial.println("----------------");
  }
}
//@gui_email
