#include "Bateria.hpp"
Bateria::Bateria(int pin) : _pin(pin)
{
  pinMode(pin, INPUT);
}


