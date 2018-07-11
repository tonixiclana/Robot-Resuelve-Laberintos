#include "Cny.hpp"
Cny::Cny(int pin) : _pin(pin)
{
  pinMode(pin, INPUT);
}

/*
   Comprueba haciendo una lectura del cny si su lectura es mayor o igual al umbral pasado
*/
bool Cny::esNegro(float umbral)
{
  return (analogRead(_pin) * _resolucionADC >= umbral) ? true : false;
}

