#ifndef curtain_module_h
#define curtain_module_h

#include <stdlib.h>
#include "config.h"
#include "shared/base_device.h"
#include "shared/mqtt_module.h"
#include "shared/timer.h"

#define STATE_OFF 0
#define STATE_PRE_ON_1 1
#define STATE_PRE_ON_2 2
#define STATE_PRE_ON_3 3
#define STATE_ON 4
#define STATE_PRE_OFF_1 5
#define STATE_PRE_OFF_2 6
#define STATE_PRE_OFF_3 7


class CurtainModule :public BaseDevice {
  private:
    uint8_t pinUp; 
    uint8_t pinDown;
    Config* pConfig;
    Timer timer;
    int internalState = 0;

  public:
  CurtainModule(uint8_t pinUp, uint8_t pinDown, MqttModule* pMqtt, Config* pConfig) 
    : BaseDevice(pMqtt, pConfig->mgtt_topic_curtain, pConfig->mgtt_topic_curtain, pConfig->mqtt_topic_template) {
    this->pConfig = pConfig;
    this->pinUp = pinUp;
    this->pinDown = pinDown;
  }

  void begin() {
    BaseDevice::begin();
    pinMode(pinUp, OUTPUT);
    pinMode(pinDown, OUTPUT);
    digitalWrite(pinUp, false);
    digitalWrite(pinDown, false);
    internalState = STATE_OFF;
  }

  bool setState(String state) {
    if (state == "UP") {
      internalState = STATE_PRE_ON_1;
      tick();
    }

    if (state == "DOWN") {
      internalState = STATE_PRE_OFF_1;
      tick();
    }
    return true;
  }

  void loop() {
    timer.loop();
    if (timer.isAlarm()) {
      tick();
    }
  }

  void tick() {
    digitalWrite(pinUp, false);
    digitalWrite(pinDown, false);

    switch(internalState) {
      case STATE_OFF:   
        Serial.println("pin down off STATE_OFF"); 
      break;
      case STATE_PRE_ON_1:
        digitalWrite(pinUp, true);
        Serial.println("pin up on STATE_PRE_ON_1");
        timer.start(100);
        internalState = STATE_PRE_ON_2;
      break;
      case STATE_PRE_ON_2:
        digitalWrite(pinUp, false);
        Serial.println("pin up off STATE_PRE_ON_2");
        timer.start(100);
        internalState = STATE_PRE_ON_3;
      break;
      case STATE_PRE_ON_3:
        digitalWrite(pinUp, true);
        Serial.println("pin up on STATE_PRE_ON_3");
        timer.start(100);
        internalState = STATE_ON;
      break;
      case STATE_ON:
        Serial.println("pin up off STATE_ON");
      break;
      case STATE_PRE_OFF_1:
        digitalWrite(pinDown, true);
        Serial.println("pin down on STATE_PRE_OFF_1");
        timer.start(100);
        internalState = STATE_PRE_OFF_2;
      break;
      case STATE_PRE_OFF_2:
        digitalWrite(pinDown, false);
        Serial.println("pin down off STATE_PRE_OFF_2");
        timer.start(100);
        internalState = STATE_PRE_OFF_3;
      break;
      case STATE_PRE_OFF_3:
        digitalWrite(pinDown, true);
        Serial.println("pin down on STATE_PRE_OFF_3");
        timer.start(100);
        internalState = STATE_OFF;
      break;
    }
  }
    
};

#endif