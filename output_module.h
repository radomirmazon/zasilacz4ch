#ifndef Output_Module_h
#define Output_Module_h

#include <stdlib.h>
#include "config.h"
#include "shared/base_device.h"
#include "shared/mqtt_module.h"

class OutputModule :public BaseDevice {
  private:
    uint8_t pin; 
    Config* pConfig;
    uint8_t value = 0;
    uint8_t prevalue = 0;
    uint8_t onoff = 0;
    long time = -1;

  public:
    OutputModule(uint8_t pin, const char* channel, const char* deviceName, MqttModule* pMqtt, Config* pConfig) 
      : BaseDevice(pMqtt, channel, deviceName, pConfig->mqtt_topic_template) {
      this->pConfig = pConfig;
      this->pin = pin;
    }

    void begin() {
      BaseDevice::begin();
      pinMode(pin, OUTPUT);
      updatePort();
      time = millis();
    }

    void loop() {
      long lastLoop = millis() - time;
      if (lastLoop > 5) {
        time = millis();
        tick();
      } 
    }

    bool needPower() {
      return getValue() != 0;
    }

  private:
    void updatePort() {
      analogWrite(pin, getValue());
    }

    uint8_t getValue() {
      return value * onoff;
    }

    void on() {
      onoff = 1;
    }

    void off() {
      onoff = 0;
    }

    void tick() {
        if (prevalue > value) {
          value++;
          updatePort();
        }
        if (prevalue < value) {
          value--;
          updatePort();
        }
    }

    bool setState(String state) {
        if(state == "off") {
          off();
        } else if(state == "on") {
          on();
        } else {
          int v = atoi(state.c_str());
          if (v >= 0) {
            prevalue = v;
          }
        }
        updatePort();
        return true;
    }
};


#endif
