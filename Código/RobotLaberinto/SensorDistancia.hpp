#ifndef SENSORDISTANCIA
#define SENSORDISTANCIA
#include <arduino.h>

class SensorDistancia
{
  public:
    SensorDistancia(int pinEcho, int pinTrigger);
    float getDistancia();
  private:
    int _pinEcho, _pinTrigger;
};
#endif
