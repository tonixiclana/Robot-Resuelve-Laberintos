#ifndef MOTOR
#define MOTOR
#include <Arduino.h>

class Motor
{

  public:
    Motor(int pinAvanzar, int pinRetroceder, int pinEncoder);
    void acelerar(int potencia);
    int getPotencia();
    int getEncoder();
  private:
    int _pinAvanzar, _pinRetroceder, _pinEncoder;
    int _potencia;
};
#endif

