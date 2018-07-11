#ifndef SERVOMOTOR
#define SERVOMOTOR

#include <Arduino.h>

class ServoMotor
{
  public:
    ServoMotor(int controlPin);
    int getControlPin();
    float getAngulo();
    void giro(float anguloDestino);
    void giroSuave(float anguloDestino, float retardo);
  private:
    int _controlPin;    //El pin que manda señales al servo
    float _angulo;  //El actual ángulo del servo
};

#endif
