#ifndef CNY
#define CNY
#include <arduino.h>

class Cny
{
  public:
    Cny(int pin);
    bool esNegro(float umbral);
    float getVoltaje() {
      return analogRead(_pin) * _resolucionADC;
    }

  private:
    int _pin;
    float _voltaje;
    const float _resolucionADC = 0.00488;
};
#endif
