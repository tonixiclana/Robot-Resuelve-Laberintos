#include "Giro.hpp"

Giro::Giro(Motor *motorIzq, Motor *motorDer) : _motorIzq(motorIzq), _motorDer(motorDer)
{
}

/*
   Aplica las velocidades necesarias a las ruedas para girar unos grados determinadas a una potencia dada
   Utiliza los encoders de las ruedas para hacer el giro mas preciso
*/
void Giro::giroBiMotor(int grados, int potenciaGiro)
{
  //guardamos la velocidad a la que estan los motores antes de ejecutar el giro
  int potenciaIzq = _motorIzq->getPotencia();
  int potenciaDer = _motorDer->getPotencia();
  // Ponemos a 0 los contadores y las lecturas de los encoders
  int contadorIzq = 0, contadorDer = 0;
  int lecturaEncoderIzq, lecturaAnteriorEncoderIzq, lecturaEncoderDer, lecturaAnteriorEncoderDer;

  //22 cambios de señal del encoder (con una pila llena) son equivalentes a aproximadamente 180 grados
  //calculamos con regla de 3 el numero de señales tenemos que recibir y obtenemos el valor absoluto
  int numeroDePulsosPorGrado = abs(grados * 22 / 180);

  //hacemos un lectura previa de los encoders de las ruedas
  lecturaAnteriorEncoderIzq = _motorIzq->getEncoder();
  lecturaAnteriorEncoderDer = _motorDer->getEncoder();

  //Si quiero girar hacía la derecha
  if (grados > 0)
  {
    //aplicamos las potencias de giro inversas correspondientes
    _motorIzq->acelerar(potenciaGiro);
    _motorDer->acelerar(-potenciaGiro);

    //mediante los encoders paramos los motores cuando hayamos llegado al numero de pulsos calculado
    while (contadorIzq < numeroDePulsosPorGrado || contadorDer < numeroDePulsosPorGrado)
    {
      lecturaEncoderIzq = _motorIzq->getEncoder();
      lecturaEncoderDer = _motorDer->getEncoder();

      if (lecturaEncoderIzq != lecturaAnteriorEncoderIzq)
        contadorIzq++;
      if (lecturaEncoderDer != lecturaAnteriorEncoderDer)
        contadorDer++;

      if (contadorIzq == numeroDePulsosPorGrado || contadorIzq > contadorDer)
        _motorIzq->acelerar(0);
      else
        _motorIzq->acelerar(potenciaGiro);

      if (contadorDer == numeroDePulsosPorGrado || contadorDer > contadorIzq  )
        _motorDer->acelerar(0);
      else
        _motorDer->acelerar(-potenciaGiro);

      lecturaAnteriorEncoderIzq = lecturaEncoderIzq;
      lecturaAnteriorEncoderDer = lecturaEncoderDer;
    }
    //paramos los 2 motores
    _motorIzq->acelerar(0);
    _motorDer->acelerar(0);
  }
  //analogamente hacemos lo mismo si queremos girar hacía la izquierda
  else
  {
    _motorIzq->acelerar(-potenciaGiro);
    _motorDer->acelerar(potenciaGiro);

    while (contadorIzq < numeroDePulsosPorGrado || contadorDer < numeroDePulsosPorGrado)
    {
      lecturaEncoderIzq = _motorIzq->getEncoder();
      lecturaEncoderDer = _motorDer->getEncoder();

      if (lecturaEncoderIzq != lecturaAnteriorEncoderIzq)
        contadorIzq++;
      if (lecturaEncoderDer != lecturaAnteriorEncoderDer)
        contadorDer++;

      if (contadorIzq == numeroDePulsosPorGrado || contadorIzq > contadorDer)
        _motorIzq->acelerar(0);
      else
        _motorIzq->acelerar(-potenciaGiro);

      if (contadorDer == numeroDePulsosPorGrado || contadorDer > contadorIzq  )
        _motorDer->acelerar(0);
      else
        _motorDer->acelerar(potenciaGiro);

      lecturaAnteriorEncoderIzq = lecturaEncoderIzq;
      lecturaAnteriorEncoderDer = lecturaEncoderDer;
    }
    _motorIzq->acelerar(0);
    _motorDer->acelerar(0);
  }
}
