#include "ServoMotor.hpp"

/*
   Constructor de la clase servoMotor
*/
ServoMotor::ServoMotor(int controlPin) : _controlPin(controlPin), _angulo(0)
{
  //posicionamos el servo a 90 grados, para tener 90 grados de giro para cada lado
  pinMode(controlPin, OUTPUT);
  float pausa = (90 - 0) * 1800.0 / 180.0 + 580;
  for (int i = 0; i < 100; i++)
  {
    float pausa;
    pausa = (90 - 0) * 1800.0 / 180.0 + 580;
    digitalWrite(_controlPin, HIGH);
    delayMicroseconds(pausa);
    digitalWrite(_controlPin, LOW);
    delayMicroseconds(25000 - pausa);
  }
}

/*
   Devuelve el pin De Control
*/
int ServoMotor::getControlPin() {
  return _controlPin;
}

/*
   Devuelve el angulo en el que esta el servo
*/
float ServoMotor::getAngulo() {
  return _angulo;
}


/*
   Gira el servo hacia un angulo destino entre -90 y 90, teniendo en cuenta que 0 es al frente
*/
void ServoMotor::giro(float anguloDestino)
{
  if (90 + anguloDestino <= 180 && 90 + anguloDestino >= 0)
  {
    while (_angulo != anguloDestino)
    {
      float pausa;
      pausa = (90 - anguloDestino) * 1800.0 / 180.0 + 580;
      digitalWrite(_controlPin, HIGH);
      delayMicroseconds(pausa);
      digitalWrite(_controlPin, LOW);
      delayMicroseconds(25000 - pausa);

      if (_angulo < anguloDestino)
        _angulo++;
      else
        _angulo--;
    }

  }

}

/*
   Realiza un giro suave hacía un angulo destino, determinado por un retardo que cuando mayor sea mas suave será
*/
void ServoMotor::giroSuave(float anguloDestino, float retardo)
{
  if (anguloDestino >= 0)
    for (float i = _angulo; i <= anguloDestino ; i++)
    {
      giro(i);
      delay(retardo);
    }
  else
    for (float i = _angulo; i >= anguloDestino ; i--)
    {
      giro(i);
      delay(retardo);
    }
}
