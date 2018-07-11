#include "SensorDistancia.hpp"

SensorDistancia::SensorDistancia(int pinEcho, int pinTrigger) : _pinEcho(pinEcho), _pinTrigger(pinTrigger)
{
  pinMode(pinEcho, INPUT);
  pinMode(pinTrigger, OUTPUT);
}

/*
   Realiza una medición con el sensor de ultrasonido y devuelve la distancia, si sobrepasa los 100cm devuelve 0
*/
float SensorDistancia::getDistancia()
{
  float distancia = 0;
  digitalWrite(_pinTrigger, LOW);
  delayMicroseconds(2);
  digitalWrite(_pinTrigger, HIGH);
  delayMicroseconds(10);
  // limitacion de 6000 ms, equivale a una medida maxima de 100 cm
  distancia += pulseIn(_pinEcho, HIGH, 30000);
  delay(100);
  //convertimos el retardo del pulso en centimetros
  return distancia * 0.017175;
}
