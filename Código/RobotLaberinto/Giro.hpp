#ifndef GIRO
#define GIRO
#include <Arduino.h>
#include "Motor.hpp"

class Giro
{

  public:
    Giro(Motor *motorIzq, Motor *motorDer);
    void giroBiMotor(int grados, int potenciaGiro = 175);
  private:
    Motor *_motorIzq;
    Motor *_motorDer;
};

#endif
