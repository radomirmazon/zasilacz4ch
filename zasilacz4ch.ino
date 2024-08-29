#include <ESP8266WiFi.h>
#include "config.h"
#include "shared/mqtt_module.h"
#include "output_module.h"
#include "power_manager.h"
#include "curtain_module.h"
#include "irda_module.h"

#define PIN_CURTAIN_UP 12
#define PIN_CURTAIN_DOWN 15

Config config;
WiFiClient espClient;
PowerManager powerManager;
MqttModule* pMqtt = new MqttModule(&espClient, 
    config.mqtt_broker,
    config.mqtt_port,
    config.mqtt_username,
    config.mqtt_password);

CurtainModule curtainModule(PIN_CURTAIN_DOWN, PIN_CURTAIN_UP, pMqtt, &config);
OutputModule output0(5, config.mgtt_topic_ch0, "led", pMqtt, &config);
OutputModule output1(4, config.mgtt_topic_ch1, "led", pMqtt, &config);
OutputModule output2(16, config.mgtt_topic_ch2, "led", pMqtt, &config);
OutputModule output3(14, config.mgtt_topic_ch3, "led", pMqtt, &config);
IrdaModule irdaModule(2, pMqtt, &config);

void setup() {
  Serial.begin(9600);
  Serial.println("\nHello\n");
  powerManager.begin();
  powerManager.registerOutput(&output0);
  powerManager.registerOutput(&output1);
  powerManager.registerOutput(&output2);
  powerManager.registerOutput(&output3);
  setup_wifi();
  pMqtt->begin();
  output0.begin();
  output1.begin();
  output2.begin();
  output3.begin();
  curtainModule.begin();
  irdaModule.begin();
}

void loop() {
  pMqtt->loop();
  powerManager.loop();
  output0.loop();
  output1.loop();
  output2.loop();
  output3.loop();
  curtainModule.loop();
  irdaModule.loop();
}

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(config.ssid);

  WiFi.begin(config.ssid, config.password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}