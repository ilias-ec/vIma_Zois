///////////////////////////
// DiPUI - Γυμνάσιο Κανήθου
///////////////////////////

// TFT 1.8"
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>
#define TFT_CS     9
#define TFT_RST    7
#define TFT_DC     8
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);
#define TFT_SCLK 13
#define TFT_MOSI 11

// Real Time Clock
#include <DS3231.h>
DS3231  rtc(SDA, SCL);

// Temperature/Humidity Sensor
#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// Air Quality
int gas_din = 3;
int gas_ain = A0;
int ad_value;

//  Buzzer
const int buzzer = 6;

// Barometric Sensor
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#define BMP_CS 5 //10
Adafruit_BMP280 bme(BMP_CS);

// 433 MHz Receiver
#include <RH_ASK.h>
RH_ASK driver;


void setup(void) {

  Serial.begin(9600);

  //  RTC
  rtc.begin();

  //  TFT
  tft.initR(INITR_BLACKTAB);
  tft.setRotation(1);
  tft.fillScreen(ST7735_BLACK);
  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(2.7 );

  //  Air Quality
  pinMode(gas_din, INPUT);
  pinMode(gas_ain, INPUT);

  //  Buzzer
  pinMode(buzzer, OUTPUT);

  // LED red
  pinMode(10, OUTPUT);
  digitalWrite(10, LOW);

  //  Barometric Pressure
  Serial.println(F("BMP280 test"));
  if (!bme.begin()) {
    Serial.println("Could not find a valid BMP280 sensor, check wiring!");
    while (1);
  }

  //  Temperature/Humidity Sensor
  Serial.println("DHTxx test!");
  dht.begin();

  // 433 MHz Receiver
  if (!driver.init())
    Serial.println("init failed"); ///   /home/Arduino/RadioHead/RH_ASK.h - line 261 rxPin = 4

}

void loop()
{
  // Date - Time on TFT
  tft.fillScreen(ST7735_BLACK);
  tft.setCursor(0, 0);
  // Send Day-of-Week
  tft.println(rtc.getDOWStr());
  //tft.println(" ");
  // Send date
  tft.println(rtc.getDateStr());
  // Send time
  tft.println(rtc.getTimeStr());

  //  Temperature/Humidity Sensor
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t))
  {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  tft.print("Temper="); tft.print((int)t); tft.println(" oC");
  tft.print("Humid="); tft.print((int)h); tft.println(" RH%");

  //  Air Quality
  ad_value = analogRead(gas_ain);
  tft.print("Air Qual="); tft.println(ad_value);
  if (ad_value > 100) {
    tone(buzzer, 3000);
    digitalWrite(10, HIGH);
    delay(100);       // ...for 1 sec
    noTone(buzzer);
    digitalWrite(10, LOW);
    delay(100);        // ...for 1sec
    tft.fillScreen(ST7735_BLACK);
    tft.setCursor(0, 0);
    tft.setTextColor(ST7735_RED);
    tft.print("Open a window");
    tft.println(" ");
    tft.print("Fresh Air");
    tft.println(" ");
    tft.println(" ");
    tft.println(" ");
    delay(3000);
    tft.setTextColor(ST7735_WHITE);
  }

  tft.print("Press=");
  int pressure = bme.readPressure() / 100 ;
  tft.print(pressure);
  tft.print("hPa");
  tft.println();

  // 433 MHz Receiver
  uint8_t buf[6]; //12
  uint8_t buflen = sizeof(buf);
  if (driver.recv(buf, &buflen))
  {
    int i;
    String s = (char*)buf  ;
    Serial.print(s);
    float fff = s.toFloat();
    Serial.print(fff);
    if ( fff >= 999)
    {
      Serial.println("A man/woman FELL!!!");
      tft.fillScreen(ST7735_BLACK);
      tft.setCursor(0, 0);
      tft.setTextColor(ST7735_RED);
      tft.print("A man/woman");
      tft.println(" ");
      tft.print("FELL!!!");
      for (int hz = 440; hz < 5000; hz += 20)
      {
        tone(buzzer, hz, 5000);
        delay(50);
      }
      delay(5000);
      tft.setTextColor(ST7735_WHITE);
    }
    if (fff >= 160)
    {
      Serial.println("Attension!!! Heart Pulse Too High");
      tft.fillScreen(ST7735_BLACK);
      tft.setCursor(0, 0);
      tft.setTextColor(ST7735_RED);
      tft.print("Attension!!!");
      tft.println(" ");
      tft.print("Heart Pulse Too High");
      for (int hz = 440; hz < 4000; hz += 20)
      {
        tone(buzzer, hz, 5000);
        delay(50);
      }
      delay(5000);
      tft.setTextColor(ST7735_WHITE);
    }
  }
  delay(1000);
}
