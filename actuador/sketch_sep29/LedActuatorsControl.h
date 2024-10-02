#include "Led.h"

class LedActuatorsControl{
    private:
      unsigned char beforeState;
      Led leds[4];
    public:
      LedActuatorsControl(unsigned char pinLed1, unsigned char pinLed2, unsigned char pinLed3, unsigned char pinLed4)
              : leds{(pinLed1),(pinLed2),(pinLed3),(pinLed4)} {
      }

      void checkState(unsigned char actualState){
        Serial.println(actualState);
        if(beforeState != actualState && actualState != 0){
          for(int i = 0; i<4; i++)
              (actualState == i+1) ? leds[i].turnOn(): leds[i].turnOff();
          if(actualState == 5){
            for(int i = 0; i<4; i++)
              leds[i].turnOff();
          }
          beforeState = actualState;
        }
      }
};