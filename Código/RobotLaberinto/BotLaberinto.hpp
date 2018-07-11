#ifndef BOTLABERINTO
#define BOTLABERINTO
#include <arduino.h>
#include "Motor.hpp"
#include "Giro.hpp"
#include "Cny.hpp"
#include "SensorDistanciaMovil.hpp"
#include "Bateria.hpp"

class BotLaberinto
{
  public:
    BotLaberinto(Motor *motorDer, Motor *motorIzq, Giro *giro, Cny *cnyDelDer, Cny *cnyTraIzq, Cny *cnyTraDer,
                 SensorDistanciaMovil *sensorDistanciaMovil, Bateria *bateria, float longitudCelda = 20, int _numeroCeldas = 25 );
    void avanzarFrente(int distancia);
    void retroceder(int tiempo);
    void stop(int retardo);
    bool hayParedFrente(int distanciaPared);
    bool hayParedIzquierda(int distanciaPared);
    bool hayParedDerecha(int distanciaPared);
    void rutinaLaberinto();
    bool estaEnFinalLaberinto();

  private:
    Motor *_motorIzq, *_motorDer;
    Giro *_giro;
    Cny *_cnyDelDer, *_cnyTraIzq, *_cnyTraDer;
    SensorDistanciaMovil *_sensorDistanciaMovil;
    Bateria *_bateria;
    float _longitudCelda;
    int _numeroCeldas, _numeroCeldasRecorridas;
    int _distanciaRecorrida;
    unsigned long _tiempoInicio;
    int _posX; //coordenada x POSICIONES EN EL MAPA (HORIZONTAL)
    int _posY; //coordenada y POSICIONES EN EL MAPA (VERTICAL)
    int _posCoche = 0; //  1 si esta de frente, 2 si esta mirando a la izquierda, 3 si esta mirando a la derecha y 4 si esta mirando hacia atras
};
#endif
