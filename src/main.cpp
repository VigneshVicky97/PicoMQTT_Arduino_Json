#include <PicoMQTT.h>
#include "WiFiAP1.h"

// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
// uncomment the below line
#include "WebServer_WT32_ETH01.h"         //https://github.com/khoih-prog/WebServer_WT32_ETH01

#include "LAN8720.h"

// Select the IP address according to your local network
// IPAddress myIP(192, 168, 1, 232);
// IPAddress myGW(192, 168, 1, 1);
// IPAddress mySN(255, 255, 255, 0);

IPAddress myIP(172, 54, 4, 232);
IPAddress myGW(172, 54, 16, 201);
IPAddress mySN(255, 255, 0, 0);
// Google DNS Server IP
IPAddress myDNS(8, 8, 8, 8);

LAN8720 lan8720;

#if __has_include("config.h")
#include "config.h"
#endif

#define WIFI_SSID "Vicky"
#define WIFI_PASSWORD "vicky12345"

WiFiAP1 wifiAP1(WIFI_SSID, WIFI_PASSWORD);

#include <ArduinoJson.h>

PicoMQTT::Client mqtt("172.54.4.158");

unsigned long last_publish_time = 0;
int greeting_number = 1;

void mqttCallBack(const char * topic, Stream & stream)
{
  Serial.printf("Received message in topic '%s':\n", topic);
  StaticJsonDocument<1024> json;
  if (deserializeJson(json, stream)) {
      Serial.println("Json parsing failed.");
      return;
  }
  serializeJsonPretty(json, Serial);
  Serial.println();
}


void setup() {
    // Setup serial
    Serial.begin(115200);

    // Connect to WiFi
    // wifiAP1.init();
    // wifiAP1.connect();

    // Connect to LAN8720
    lan8720.init();
    lan8720.config(myIP, myGW, mySN, myDNS);
    lan8720.connect();

    // Subscribe to a topic and attach a callback
    mqtt.subscribe("picomqtt/json/#", mqttCallBack);

    mqtt.begin();
}

void loop() {
    mqtt.loop();

    // Publish a greeting message every 3 seconds.
    if (millis() - last_publish_time >= 3000) {
        String topic = "picomqtt/json/esp-" + WiFi.macAddress();
        Serial.printf("Publishing in topic '%s'...\n", topic.c_str());

        // build JSON document
        StaticJsonDocument<1024> json;
        json["foo"] = "bar";
        json["millis"] = millis();

        // publish using begin_publish()/send() API
        auto publish = mqtt.begin_publish(topic, measureJson(json));
        serializeJson(json, publish);
        publish.send();

        last_publish_time = millis();
    }
}