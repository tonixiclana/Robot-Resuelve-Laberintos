#include "SensorDistanciaMovil.hpp"

SensorDistanciaMovil::SensorDistanciaMovil(ServoMotor *servoMotor, SensorDistancia *sensorDistancia) :
  _servoMotor(servoMotor), _sensorDistancia(sensorDistancia) {}

/*
   Orienta el servo a un determinado grado de giro, y devuelve la medida que toma el sensor ultrasonido
*/
float SensorDistanciaMovil::getDistancia(int grados)
{
  float distancia;
  if (_servoMotor->getAngulo() != grados)
  {
    _servoMotor->giro(grados);
    distancia = _sensorDistancia->getDistancia();
  } else
    distancia = _sensorDistancia->getDistancia();

  return distancia;
}

/*
   Realiza un barrido desde un grado origen a uno destino y guarda las medidas en un vector,
   se puede proporcionar la velocidad de barrido y el incremento en grados por cada medida,
   devuelve el numero de medidas que se han realizado
*/
int SensorDistanciaMovil::barrido(int gradoInicio, int gradoFin, float medidas[360], float velocidad, int incremento)
{
  int contador = 0;

  if (gradoInicio < gradoFin)
    for (int i = gradoInicio; i <= gradoFin; i += incremento)
      medidas[contador++] = getDistancia(i);
  else
    for (int i = gradoInicio; i >= gradoFin; i -= incremento)
      medidas[contador++] = getDistancia(i);

  return contador;
}

/*
   Realiza un barrido de 180 grados y guarda las medidas
*/
void SensorDistanciaMovil::get180GradosDistancia(float medidas[360], float velocidad)
{
  barrido(-90, 90, medidas, velocidad, 1);
}

