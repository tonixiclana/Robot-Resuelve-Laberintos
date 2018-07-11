#ifndef SENSORDISTANCIAMOVIL
#define SENSORDISTANCIAMOVIL
#include <arduino.h>
#include "SensorDistancia.hpp"
#include "ServoMotor.hpp"

class SensorDistanciaMovil
{
  public:
    SensorDistanciaMovil(ServoMotor *servoMotor, SensorDistancia *sensorDistancia);
    float getDistancia(int grados);
    int barrido(int gradoInicio, int gradoFin, float medidas[360], float velocidad = 5, int incremento = 5);
    void get180GradosDistancia(float medidas[360], float velocidad);
  private:
    ServoMotor *_servoMotor;
    SensorDistancia *_sensorDistancia;
};
#endif
