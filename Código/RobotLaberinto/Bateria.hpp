#ifndef BATERIA
#define BATERIA
#include <arduino.h>

class Bateria
{
  public:
    Bateria(int pin);
    float getVoltaje() {
      return analogRead(_pin) * _resolucionADC + 0.75;
    }
    float correctorDeGiro();

  private:
    int _pin;
    const float _resolucionADC = 0.0049;
};
#endif
