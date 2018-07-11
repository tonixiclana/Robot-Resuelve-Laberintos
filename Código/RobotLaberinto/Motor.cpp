#include "Motor.hpp"

/*
   Constructor de la clase motor
*/
Motor::Motor(int pinAvanzar, int pinRetroceder, int pinEncoder) : _pinAvanzar(pinAvanzar), _pinRetroceder(pinRetroceder), _potencia(0), _pinEncoder(pinEncoder)
{
  pinMode(pinAvanzar, OUTPUT);
  pinMode(pinRetroceder, OUTPUT);
  pinMode(pinEncoder, INPUT);
}

/*
   Método destinado a acelerar o decelerar el motor
*/
void Motor::acelerar(int potencia)
{
  if (potencia >= -255 && potencia <= 255)
  {
    if (potencia >= 0)
    {
      analogWrite(_pinAvanzar, potencia);
      analogWrite(_pinRetroceder, 0);
    }
    else
    {
      analogWrite(_pinAvanzar, 0);
      analogWrite(_pinRetroceder, abs(potencia));
    }
    _potencia = potencia;
  }
}

/*
   Utilizado para hacer una medida del encoder del motor
*/
int Motor::getEncoder()
{
  return digitalRead(_pinEncoder);
}

/*
   Devuelve la potencia actual del motor
*/
int Motor::getPotencia()
{
  return _potencia;
}

