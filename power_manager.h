#ifndef Power_Manager_h
#define Power_Manager_h

#include "output_module.h"
#define POWER_UP_PIN 13

class PowerManager {
  private:
    int index = 0;
    OutputModule* outputs[10];
    bool lastState = false;

  public:
    void begin() {
      pinMode(POWER_UP_PIN, OUTPUT);
      digitalWrite(POWER_UP_PIN, true);
    }

    void registerOutput(OutputModule* pOutputModule){
      outputs[index++] = pOutputModule;
    }

    void loop() {
      bool needPower = false;
      for(int i=0; i<index; i++) {
        needPower = needPower || outputs[i]->needPower();
      }
      if (lastState != needPower) {
        digitalWrite(POWER_UP_PIN, !needPower);
      } 

      lastState = needPower;
    }


};

#endif