#include <Arduino.h>
#include "ESP8266WiFi.h"
#include "WiFiClient.h"
#include "ESP8266HTTPClient.h"

const char* ssid = "NinjaTurtles";
const char* password = "FireFighter2";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.print("\n\r \n\rWorking to connect");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("DHT Weather Reading Server");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  Serial.println("HTTP server started");
}

void loop() {
  Serial.println("Start Loop");
  if(WiFi.status() == WL_CONNECTED){
    HTTPClient http;
    WiFiClient client;

    // put your main code here, to run repeatedly:
    Serial.print("Starting GET request");
    if(http.begin(client, "http://192.168.178.29:8080")) {
      Serial.print("Request Started Sending headers");
      int httpCode = http.GET();
      if(httpCode > 0) {
        Serial.print("Status Code: " + httpCode);
        
        if(httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          String payload = http.getString();
          Serial.print("Payload is: " + payload);
        }
      } else {
          Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }

      Serial.println("Closing Http Connection");
      http.end();
      Serial.println("Closed Http Connection");
    }
  } else {
    Serial.println("Not Connected !!");
  }
  Serial.println("End loop");
}