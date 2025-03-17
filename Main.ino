#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include "secrets.h" 
#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 
#define OLED_RESET     -1 
#define SCREEN_ADDRESS 0x3C 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const char* ssid = "SSID";
const char* password = "PASSWORD";

// Powered by CoinDesk - https://www.coindesk.com/price/bitcoin
const String url = "http://api.coindesk.com/v1/bpi/currentprice.json";
const String historyURL = "http://api.coindesk.com/v1/bpi/historical/close.json";
const String cryptoCode = "BTC";

// BTC logo
const unsigned char bitcoinIcon [] PROGMEM = {
0x00, 0x7e, 0x00, 0x03, 0xff, 0xc0, 0x07, 0x81, 0xe0, 0x0e, 0x00, 0x70, 0x18, 0x28, 0x18, 0x30, 
0x28, 0x0c, 0x70, 0xfc, 0x0e, 0x60, 0xfe, 0x06, 0x60, 0xc7, 0x06, 0xc0, 0xc3, 0x03, 0xc0, 0xc7, 
0x03, 0xc0, 0xfe, 0x03, 0xc0, 0xff, 0x03, 0xc0, 0xc3, 0x83, 0xc0, 0xc1, 0x83, 0x60, 0xc3, 0x86, 
0x60, 0xff, 0x06, 0x70, 0xfe, 0x0e, 0x30, 0x28, 0x0c, 0x18, 0x28, 0x18, 0x0e, 0x00, 0x70, 0x07, 
0x81, 0xe0, 0x03, 0xff, 0xc0, 0x00, 0x7e, 0x00
};

HTTPClient http;
WiFiClient wificlient;
String lastPrice;

void setup() {
  Serial.begin(115200);

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("ASIGNACION DE SSD1306 FALLIDA"));
    for (;;); 
  }

  display.clearDisplay();
  display.setTextSize(1);           
  display.setTextColor(SSD1306_WHITE);      
  display.setCursor(0,0); 
  display.println("Conectando al WiFi...");
  display.display();

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
  }

  
  Serial.println(ssid);

  
  display.println(ssid);
  display.display();
  delay(5000);
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Leyendo datos...");

    http.begin(wificlient, url);
    int httpCode = http.GET();
    Serial.print("HTTP Code: ");
    Serial.println(httpCode);
    if (httpCode > 0) {
      StaticJsonDocument<768> doc;
      DeserializationError error = deserializeJson(doc, http.getString());

      if (error) {
        Serial.print(F("deserializeJson failed: "));
        Serial.println(error.f_str());
        delay(2500);
        return;
      }

      Serial.print("HTTP Status Code: ");
      Serial.println(httpCode);

      String BTCUSDPrice = doc["bpi"]["USD"]["rate_float"].as<String>();
      if(BTCUSDPrice == lastPrice) {
        Serial.print("El precio no ha cambiado (Actual/Anterior): ");
        Serial.print(BTCUSDPrice);
        Serial.print(" : ");
        Serial.println(lastPrice);
        delay(1250);
        return;
      } else {
        lastPrice = BTCUSDPrice;
      }
      String lastUpdated = doc["time"]["updated"].as<String>();
      http.end();

      Serial.println("Obteniendo historial...");
      StaticJsonDocument<1536> historyDoc;
      http.begin(wificlient, historyURL);
      int historyHttpCode = http.GET();
      DeserializationError historyError = deserializeJson(historyDoc, http.getString());

      if (historyError) {
        Serial.print(F("deserializeJson(History) failed: "));
        Serial.println(historyError.f_str());
        delay(2500);
        return;
      }

      
      display.clearDisplay();
      display.drawBitmap((128/2) - (24/2), 0, bitcoinIcon, 24, 24, WHITE);
      display.display();

 //Precio BTC
 display.setTextSize(1);
 printCenter("$" + BTCUSDPrice, 0, 32);

 //Firma
 display.setTextSize(1);
 display.setCursor(5, 55);
 display.println("@ivxn.ramos_ - RYC");

      display.display();
      http.end();
    }
    delay(1250);
  }
}

void printCenter(const String buf, int x, int y)
{
  int16_t x1, y1;
  uint16_t w, h;
  display.getTextBounds(buf, x, y, &x1, &y1, &w, &h); 
  display.setCursor((x - w / 2) + (128 / 2), y);
  display.print(buf);
}
