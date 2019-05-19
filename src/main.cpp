#include <Arduino.h>
#include <WiFiClientSecureBearSSL.h>
#include "ESP8266HTTPClient.h"
#include "ESP8266WiFi.h"
#include "ESP8266WiFiMulti.h"
#include "WiFiClient.h"

const char* ssid = "NinjaTurtles";
const char* password = "FireFighter2";

ESP8266WiFiMulti WiFiMulti;

void getRequest(String url) {
  WiFiClient client;
  HTTPClient http;

  if (http.begin(client, url)) {
    Serial.print("Request Started Sending headers");
    int httpCode = http.GET();
    if (httpCode > 0) {
      Serial.print("Status Code: " + httpCode);

      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
        String payload = http.getString();
        Serial.print("Payload is: " + payload);
      }
    } else {
      Serial.printf("[HTTP] GET... failed, error: %s\n",
                    http.errorToString(httpCode).c_str());
    }

    Serial.println("Closing Http Connection");
    http.end();
    Serial.println("Closed Http Connection");
  }
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(ssid, password);
}

void loop() {
  if (WiFiMulti.run() == WL_CONNECTED) {
    if (Serial.available() > 0) {
      String url = Serial.readString();
      Serial.print("Starting GET request for " + url);
      getRequest(url);
    }
  } else {
    Serial.println("No Connected Yet !");
  }
  delay(1000);
}
