#ifndef irda_module_h
#define irda_module_h

#include "config.h"
#include "base_device.h"
#include "mqtt_module.h"
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include "timer.h"

class IrdaModule  :public BaseDevice {
  private:
    Config* pConfig;
    IRsend* pIRsend;
    Timer timer;
    int pin;

  public:
  IrdaModule(uint16_t pinIrda, MqttModule* pMqtt, Config* pConfig) 
    : BaseDevice(pMqtt, pConfig->mgtt_topic_irda, pConfig->mgtt_topic_irda, pConfig->mqtt_topic_template) {
    this->pConfig = pConfig;
    pin = pinIrda;
    pIRsend = new IRsend(pinIrda);
  }

  void begin() {
    BaseDevice::begin();
    pIRsend->begin();
    //pinMode(pin, OUTPUT);
    //digitalWrite(pin, LOW);
  }

  void loop() {
    pIRsend->sendNEC(0x00F78877UL);
    delay(2000);
  }

  bool setState(String sState) {
    return true;
  }
};
#endif