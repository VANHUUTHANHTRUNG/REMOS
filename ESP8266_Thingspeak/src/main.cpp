#include <Arduino.h>
#include "ThingSpeak.h"
#include "secrets.h"
unsigned long myChannelNumber = SECRET_CH_ID;
const char *myWriteAPIKey = SECRET_WRITE_APIKEY;

#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;
WiFiClient client;
IPAddress ip(10,100,5,62);   
IPAddress gateway(10,100,0,1);   
IPAddress subnet(255,255,192,0);
IPAddress dns(130, 233, 224, 141);

void setup()
{
  Serial.begin(115200);
  delay(100);
  ThingSpeak.begin(client);
  WiFi.mode(WIFI_STA);
  Serial.printf("\nWi-Fi mode set to WIFI_STA %s\n", WiFi.mode(WIFI_STA) ? "" : "Failed!");
}

void loop()
{
  WiFi.disconnect();
  delay(100);
  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.print("\nAttempting to connect to SSID: ");
    Serial.println(SECRET_SSID);
    while (WiFi.status() != WL_CONNECTED)
    {
      if(WiFi.config(ip, gateway, subnet, dns) == false){
        Serial.println("Failed to configure");
      }
      WiFi.begin(ssid,pass);
      Serial.print(".");
      delay(5000);
    }
    // Serial.println(WiFi.localIP());
    // Serial.println(WiFi.subnetMask());
    // Serial.println(WiFi.gatewayIP());
    // Serial.println(WiFi.dnsIP(0));
    // Serial.println(WiFi.dnsIP(1));
    Serial.println("\nConnected.");
  }

    int valueA0 = 100;

    // Write value to Field 1 of a ThingSpeak Channel
    ThingSpeak.setField(1,valueA0);
    ThingSpeak.setField(2,valueA0 + 1);
    int httpCode = ThingSpeak.writeFields(myChannelNumber,myWriteAPIKey);

    if (httpCode == 200)
    {
      Serial.println("Channel write successful.");
    }
    else
    {
      Serial.println("Problem writing to channel. HTTP error code " + String(httpCode));
    }

    // Wait 20 seconds to update the channel again
    delay(20000);
  }