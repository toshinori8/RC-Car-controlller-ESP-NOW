#include <Arduino.h>
//#include <main.h>
#include <ESP8266WiFi.h>
#if (defined(WIFI_) || defined(ESPNOW_))

#endif

#if (defined(WIFI_))
#define STASSID "oooooio"
#define STAPSK "pmgana921"
const char *ssid_ = STASSID;
const char *password_ = STAPSK;

void wifiStart()
{

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid_, password_);
  while (WiFi.waitForConnectResult() != WL_CONNECTED)
  {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}
#endif

#if (defined(OTA_))

#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

void otaStart()
{

  ArduinoOTA.setHostname("RC Car Controller");

  ArduinoOTA.onStart([]()
                     {
                           String type;
                           if (ArduinoOTA.getCommand() == U_FLASH)
                           {
                               type = "sketch";
                           }
                           else
                           { // U_FS
                               type = "filesystem";
                           }
                           // NOTE: if updating FS this would be the place to unmount FS using FS.end()
                           Serial.println("Start updating " + type); });

  ArduinoOTA.onEnd([]()
                   { Serial.println("\nEnd"); });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total)
                        {
                              Serial.printf("Progress: %u%%\r", (progress / (total / 100)));

                              String textt = "Progress: %u%%\r" + String((progress / (total / 100))); });
  ArduinoOTA.onError([](ota_error_t error)
                     {
   Serial.printf("Error[%u]: ", error);
   if (error == OTA_AUTH_ERROR) {
     Serial.println("Auth Failed");
   } else if (error == OTA_BEGIN_ERROR) {
     Serial.println("Begin Failed");
   } else if (error == OTA_CONNECT_ERROR) {
     Serial.println("Connect Failed");
   } else if (error == OTA_RECEIVE_ERROR) {
     Serial.println("Receive Failed");
   } else if (error == OTA_END_ERROR) {
     Serial.println("End Failed");
   } });
  ArduinoOTA.begin();
}
#endif

