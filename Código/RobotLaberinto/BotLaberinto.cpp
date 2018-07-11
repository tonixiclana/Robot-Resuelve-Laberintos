/*
   1 -> movimiento hacia delante
   2 -> movimiento hacia izquierda
   3 -> movimiento hacia derecha
*/

#include "BotLaberinto.hpp"

/*
   Función constructura de BotLaberinto, inicializa todas las variables de la clase y el pin 13 para usar el led
*/
BotLaberinto::BotLaberinto(Motor *motorDer, Motor *motorIzq, Giro *giro, Cny *cnyDelDer, Cny *cnyTraIzq, Cny *cnyTraDer,
                           SensorDistanciaMovil *sensorDistanciaMovil, Bateria *bateria, float longitudCelda, int numeroCeldas )
  : _motorIzq(motorIzq), _motorDer(motorDer), _giro(giro), _cnyDelDer(cnyDelDer), _cnyTraIzq(cnyTraIzq), _cnyTraDer(cnyTraDer)
  , _sensorDistanciaMovil(sensorDistanciaMovil), _longitudCelda(longitudCelda), _numeroCeldas(numeroCeldas), _bateria(bateria)
  , _numeroCeldasRecorridas(0), _distanciaRecorrida(0), _tiempoInicio(millis())
{
  pinMode(13, OUTPUT);
}

/*
   En esta función se avanza el robot una determinada distancia midiendo los encoders de los motores
   Es una función bloqueante, eso quiere decir que bloquea el flujo principal hasta que no se termine
*/
void BotLaberinto::avanzarFrente(int distancia)
{
  int contadorIzq = 0, contadorDer = 0; //contadores de los pulsos de cada encoder
  bool lecturaEncoderIzq, lecturaEncoderDer, anteriorLecturaEncoderIzq, anteriorLecturaEncoderDer ;

  //hacemos una lectura de cada encoder
  anteriorLecturaEncoderIzq = _motorIzq->getEncoder();
  anteriorLecturaEncoderDer = _motorDer->getEncoder();

  // Aceleramos ambas ruedas a 175
  _motorIzq->acelerar(175);
  _motorDer->acelerar(175);

  //Bucle que ira leyendo los encoder y parar cada rueda cuando se haya llegado a la distancia requerida
  while (contadorIzq < distancia || contadorDer < distancia)
  {
    lecturaEncoderIzq = _motorIzq->getEncoder();
    lecturaEncoderDer = _motorDer->getEncoder();

    if (lecturaEncoderIzq != anteriorLecturaEncoderIzq)
      contadorIzq++;
    if (lecturaEncoderDer != anteriorLecturaEncoderDer)
      contadorDer++;

    if (contadorIzq == distancia || contadorIzq > contadorDer)
      _motorIzq->acelerar(0);
    else
      _motorIzq->acelerar(175);

    if (contadorDer == distancia || contadorDer > contadorIzq  )
      _motorDer->acelerar(0);
    else
      _motorDer->acelerar(175);

    anteriorLecturaEncoderIzq = lecturaEncoderIzq;
    anteriorLecturaEncoderDer = lecturaEncoderDer;
  }
}

/*
   Función provista para retroceder durante un tiempo y luego parar
*/
void BotLaberinto::retroceder(int tiempo)
{
  _motorIzq->acelerar(-175);
  _motorDer->acelerar(-175);
  stop(tiempo);
}

/*
   Funcíon que para las 2 ruedad pasado un tiempo indicado
*/
void BotLaberinto::stop(int retardo)
{
  delay(retardo);
  _motorIzq->acelerar(0);
  _motorDer->acelerar(0);
}

/*
   Función que determina si hay una pared justo enfrente a menos de una distancia dada, devuelve true en casa afirmativo
*/
bool BotLaberinto::hayParedFrente(int distanciaPared)
{
  float medida;

  medida = _sensorDistanciaMovil->getDistancia(0);
  if (medida <= (float)distanciaPared)
    return true;
  return false;
}

/*
   Función que determina si hay una pared a la izquierda a menos de una distancia dada, devuelve true en casa afirmativo
*/
bool BotLaberinto::hayParedIzquierda(int distanciaPared)
{
  float medida;

  medida = _sensorDistanciaMovil->getDistancia(-90);


  //Serial1.println((String)medidas[i]);
  if (medida <= (float)distanciaPared)
    return true;
  return false;
}

/*
   Función que determina si hay una pared a la Derecha a menos de una distancia dada, devuelve true en casa afirmativo
*/
bool BotLaberinto::hayParedDerecha(int distanciaPared)
{
  float medida;

  medida = _sensorDistanciaMovil->getDistancia(90);


  //Serial1.println((String)medidas[i]);
  if (medida <= (float)distanciaPared)
    return true;
  return false;
}

/*
   Función en la que se ejecuta el algoritmo de resolución de laberinto, mediante la detección de celdas y paredes, usando la estrategía de la mano izq
*/
void BotLaberinto::rutinaLaberinto()
{
  bool choquePared = hayParedFrente(8);       //comprobamos si va a ver un choque, con una pared
  bool hayParedIzq, hayParedFren, hayParedDer;
  //leemos los CNY traseros
  bool esNegroTraIzq = _cnyTraIzq->esNegro(4);
  bool esNegroTraDer = _cnyTraDer->esNegro(4);

  //Si algunos de los cny traseros a detectado la entrada en una celda o hay hay una pared muy cerca
  if ( (esNegroTraIzq || esNegroTraDer) || choquePared)
  {
    // si había choque con pared retrocedemos
    if (choquePared)
    {
      Serial1.println("[BotLaberinto]\tHay un obstaculo frontal, retrocediendo...");
      retroceder(500);
    }
    else
    {
      //si no había choque con pared es que hemos llegado a una celda, por lo que paramos el motor
      stop(0);

      // alineamos el robot con la linea encontrada mediante los cny
      if (esNegroTraIzq && !esNegroTraDer)
      {
        while (!_cnyTraDer->esNegro(4))
        {
          _motorDer->acelerar(175);
        }
        _motorDer->acelerar(0);
      }

      if (!esNegroTraIzq && esNegroTraDer)
      {
        while (!_cnyTraIzq->esNegro(4))
        {
          _motorIzq->acelerar(175);
        }
        _motorIzq->acelerar(0);
      }

      // Comprobamos las distancia por cada lateral, para compensar con un giro si estamos muy cerca de una pared
      hayParedIzq = hayParedIzquierda(8);
      if (hayParedIzq)
        if (_sensorDistanciaMovil->getDistancia(-90) < 7)
          _giro->giroBiMotor(20);

      hayParedDer = hayParedDerecha(8);
      if (hayParedDer)
        if (_sensorDistanciaMovil->getDistancia(90) < 7)
          _giro->giroBiMotor(-20);

      //Avanzamos 8 cm para colocarnos en el centro de la celda
      avanzarFrente(8);

      //incrementamos en uno el numero de celdas recorridas y le añadimos longitudCelda a distancia recorrida
      _numeroCeldasRecorridas++;
      _distanciaRecorrida += _longitudCelda;

    }

    // Si no estamos en el final del laberinto, decidiremos a que celda ir, mediante la comprobación de las paredes
    if (!estaEnFinalLaberinto())
    {
      stop(0);
      //comprobamos si hay paredes a menos de 20 centimtros a la izq, frente y der
      hayParedDer = hayParedDerecha(20);
      hayParedFren = hayParedFrente(20);
      hayParedIzq = hayParedIzquierda(20);

      // Se manda información sobre la casilla y el progreso de resolución del laberinto

      Serial1.print("[BotLaberinto] Celdas recorridas: ");
      Serial1.println(_numeroCeldasRecorridas);
      Serial1.print("[BotLaberinto] Distancia recorrida: ");
      Serial1.print(_distanciaRecorrida);
      Serial1.println(" cms");
      Serial1.print("[BotLaberinto] Tiempo transcurrido: ");
      Serial1.print((millis() - _tiempoInicio) / 1000);
      Serial1.println(" seg");
      (hayParedIzq) ? Serial1.println("[BotLaberinto] Hay pared en la izquierda") : Serial1.println("[BotLaberinto] No hay pared en la izquierda");
      (hayParedFren) ? Serial1.println("[BotLaberinto] Hay pared al frente") : Serial1.println("[BotLaberinto] No hay pared al frente");
      (hayParedDer) ? Serial1.println("[BotLaberinto] Hay pared en la derecha") : Serial1.println("[BotLaberinto] No hay pared en la derecha");



      //Aquí se lleva a cabo la regla de la mano izquierda
      if (!hayParedIzq)
      {
        Serial1.println("[BotLaberinto] Girando hacia izquierda");
        _giro->giroBiMotor(-90);
      }
      else if (!hayParedFren)
      {
        Serial1.println("[BotLaberinto] Avanzando al frente");
        avanzarFrente(10);
      }
      else if (!hayParedDer)
      {
        Serial1.println("[BotLaberinto] Girando hacia la derecha");
        _giro->giroBiMotor(90);
      }
      else
      {
        Serial1.println("[BotLaberinto] Girando hacia atras");
        _giro->giroBiMotor(-180);
      }
      //salto de linea para visualizar mejor
      Serial1.println("");
    }
    //Si se ha detectado que estamos en el final del laberinto
    else
    {
      Serial1.println("[BotLaberinto] Final del laberinto encontrada");
      Serial1.print("[BotLaberinto] Tiempo transcurrido: ");
      Serial1.print((millis() - _tiempoInicio) / 1000);
      Serial1.println(" seg");
      Serial1.print("[BotLaberinto] Celdas recorridas: ");
      Serial1.println(_numeroCeldasRecorridas);
      Serial1.print("[BotLaberinto] Distancia recorrida: ");
      Serial1.print(_distanciaRecorrida);
      Serial1.println(" cms");
      stop(0);

      //encendemos el led 13 para indicar el fin de la rutina
      for (int i = 0; i < 600; i++)
      {
        digitalWrite(13, HIGH);
        delay(500);
        digitalWrite(13, LOW);
        delay(500);
      }
    }
  }
  //si no se ha detectado ninguna celda ni hay obstaculo frontal aceleramos 3 cms
  else
  {
    avanzarFrente(2);
    /*_motorDer->acelerar(175);
      _motorIzq->acelerar(175);*/
  }
}

/*
   Se realiza mediciones con el cny del der durante 250 ms para comprobar si esta sobre algo negro
*/
bool BotLaberinto::estaEnFinalLaberinto()
{
  bool lectura, lecturaAnterior = true, resultado = true;
  for (int i = 0; i < 5 ; i++)
  {
    lectura = _cnyDelDer->esNegro(4);
    if (lectura != lecturaAnterior)
      resultado = false;
    lecturaAnterior = lectura;
    delay(50);
  }
  return resultado;
}
