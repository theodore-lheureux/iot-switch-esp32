#include <Arduino.h>
#include <WiFi.h>
#define RELAY_PIN_1 2

#include "fauxmoESP.h"

#define SERIAL_BAUDRATE 115200

#define WIFI_SSID ""
#define WIFI_PASS ""

#define COMPUTER "ESP32 Comp"

fauxmoESP fauxmo;

static unsigned long LAST = millis();
static bool COMPUTER_STATE = false;

void wifiSetup()
{
  WiFi.mode(WIFI_STA);

  Serial.printf("[WIFI] Connecting to %s ", WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(100);
  }
  Serial.println();

  Serial.printf("[WIFI] STATION Mode, SSID: %s, IP address: %s\n", WiFi.SSID().c_str(), WiFi.localIP().toString().c_str());
}

void setup()
{
  Serial.begin(SERIAL_BAUDRATE);
  Serial.println();

  wifiSetup();
  
  // LED
  pinMode(RELAY_PIN_1, OUTPUT);
  digitalWrite(RELAY_PIN_1, HIGH);

  // Init fauxmo
  fauxmo.createServer(true); 
  fauxmo.setPort(80);
  fauxmo.enable(true);

  fauxmo.addDevice(COMPUTER);

  fauxmo.onSetState([](unsigned char device_id, const char *device_name, bool state, unsigned char value)
                    {
        
    Serial.printf("[MAIN] Device #%d (%s) state: %s value: %d\n", device_id, device_name, state ? "ON" : "OFF", value);
    if ( (strcmp(device_name, COMPUTER) == 0) ) {
      if (state) {
        digitalWrite(RELAY_PIN_1, LOW);
        LAST = millis();
        COMPUTER_STATE = true;
        fauxmo.setState(COMPUTER, false, 0);
        Serial.printf("[MAIN] Closing relay\n");
      }
    } });
}

void loop()
{
  fauxmo.handle();

  if (millis() - LAST > 1000 && COMPUTER_STATE == true)
  {
    digitalWrite(RELAY_PIN_1, HIGH);
    LAST = millis();
    COMPUTER_STATE = false;
    Serial.printf("[MAIN] Opening relay\n");
  }
}