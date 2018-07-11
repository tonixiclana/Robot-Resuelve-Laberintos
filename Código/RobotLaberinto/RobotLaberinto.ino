#include "Motor.hpp"
#include "Giro.hpp"
#include "ServoMotor.hpp"
#include "SensorDistancia.hpp"
#include "SensorDistanciaMovil.hpp"
#include "Cny.hpp"
#include "BotLaberinto.hpp"
#include "Bateria.hpp"

//###################### DEFINICION DE PINES ######################
#define PINMOTORDER0 5
#define PINMOTORDER1 6
#define PINMOTORIZQ0 10
#define PINMOTORIZQ1 9
#define PINSERVO 11
#define PINSENSORDISTANCIAECHO A4
#define PINSENSORDISTANCIATRIGGER 2
#define PINCNYDELDER A0
#define PINCNYTRAIZQ A2
#define PINCNYTRADER A5
#define PINBATERIA A6
#define PINENCODERDER 7
#define PINENCODERIZQ 3

//####################  DEFINICION DE VARIABLES GLOBALES #################3

//###################### DEFINICION DE ELEMENTOS DEL ROBOT ######################
Motor *motorDer;
Motor *motorIzq;
Giro *giro;
ServoMotor *servo;
SensorDistancia *sensorDistancia;
SensorDistanciaMovil *sensorDistanciaMovil;
Cny *cnyDelDer, *cnyTraDer, *cnyTraIzq;
Bateria *bateria;

//######################  DEFINICION DEL LABERINTO  #############################
BotLaberinto *botLaberinto;

//###################### FUNCIONES ############################

void testDeComponentes();


//###################### FUNCIÓN SETUP  ##############################3
void setup() {

  //######## INICIALIZACION DE ELEMENTOS DEL ROBOT ###############
  Serial1.begin(9600);
  motorDer = new Motor(PINMOTORDER1, PINMOTORDER0, PINENCODERDER); // creamos motor, pasandole pines de movimiento y pin del encoder
  motorIzq = new Motor(PINMOTORIZQ1, PINMOTORIZQ0, PINENCODERIZQ);
  giro = new Giro(motorIzq, motorDer);                            // pasamos los dos motores que participan en el giro
  servo = new ServoMotor(PINSERVO);                               //pasamos el pin del servo
  sensorDistancia = new SensorDistancia(PINSENSORDISTANCIAECHO, PINSENSORDISTANCIATRIGGER); //creamos el sensor de distancia y le pasamos los 2 pines de trabajo
  sensorDistanciaMovil = new SensorDistanciaMovil(servo, sensorDistancia);  //el sensor de distancia movil es una combinación de servo y sensor de distancia, les pasamos los 2
  cnyDelDer = new Cny(PINCNYDELDER);  // le pasamos el pin del cny correspondiente
  cnyTraIzq = new Cny(PINCNYTRAIZQ);
  cnyTraDer = new Cny(PINCNYTRADER);
  bateria = new Bateria(PINBATERIA);  //le pasamos el pin de la bateria

  //####### INICIALIZACION DEL LABERINTO  ##############
  delay(5000);  //pausa de 5 segundos antes de empezar la ejecución del programa
  botLaberinto = new BotLaberinto(motorDer, motorIzq, giro, cnyDelDer, cnyTraIzq, cnyTraDer,
                                  sensorDistanciaMovil, bateria); // le pasamos todo lo necesario para resolver el laberinto
}



//##################### BUCLE PRINCIPAL ##########################
void loop() {
  botLaberinto->rutinaLaberinto();  // se llama a la rutina de resolución de laberintos
  //testDeComponentes();      // se llama a la rutina de test
}


//##################### TEST DISPONIBLES #####################
void testDeComponentes()
{
  //PRUEBAS  DE LA CLASE BOTLABERINTO
  /*botLaberinto->avanzarFrente(2000);
    botLaberinto->avanzarIzquierda(2000);
    botLaberinto->avanzarDerecha(2000);
    botLaberinto->avanzarAtras(2000);*/
  /*Serial1.println("Hay pared izquierda?:");
    Serial1.println(botLaberinto->hayParedIzquierda());
    delay(250);
    Serial1.println("Hay pared Derecha?:");
    Serial1.println(botLaberinto->hayParedDerecha());
    delay(250);*/
  //Serial1.println("Hay pared Frente?:");
  //Serial1.println(botLaberinto->hayParedFrente(15));
  // botLaberinto->avanzarFrente(150);
  //delay(10000);

  /*while(!cnyTraIzq->esNegro(4))
    {

    float medidas[360];
    int distanciaMax = 0, gradoDistanciaMax = 90;
    int numeroMedidas;
    numeroMedidas = sensorDistanciaMovil->barrido(-90, 90, medidas, 500, 15);
    for(int i = 0; i < numeroMedidas; i++)
    {
      if(medidas[i] > distanciaMax)
      {
        distanciaMax = medidas[i];
        gradoDistanciaMax = i;

      }
    Serial1.prinln("Grado: ");
    Serial1.prinln((String)(i * 15));
    Serial1.prinln("distancia: ");
    Serial1.prinln((String)medidas[i]);
    }

    Serial1.prinln("Grado distancia max: ");
    Serial1.prinln((String)gradoDistanciaMax);
    Serial1.prinln("distancia max: ");
    Serial1.prinln((String)distanciaMax);
    Serial1.prinln("--------------------------------");
    //giro->giroBiMotor(gradoDistanciaMax - 90, botLaberinto->reguladorDeGiro());
    delay(10000);*/
  /*motorIzq->acelerar(175);
    motorDer->acelerar(175);
    delay(1500);
    motorIzq->acelerar(0);
    motorDer->acelerar(0);*/
  //}

  //Serial1.prinln((String)botLaberinto->reguladorDeGiro());



  //PRUEBA DE ACELERACION CON CLASE MOTOR
  //motorIzq->acelerar(175);
  //motorDer->acelerar(175);

  //PRUEBA DE GIRO BIMOTOR
  //Girar 90º con bateria a 8.55V, retardo 7.9
  //Girar 90º con bateria a 7.86V, retardo 8.9
  //Girar 90º con bateria a 7.48V, retardo 10.1
  //delay(5000);
  // giro->giroBiMotor(90);
  /*delay(5000);
    giro->giroBiMotor(-90);
    delay(5000);
    giro->giroBiMotor(-180);*/

  //PRUEBA DE SERVO
  /*servo->giro(-90);
    delay(1000);*/
  //servo->giro(90);
  /*delay(1000);
    servo->giro(90);
    delay(1000);
    servo->giro(0);
    delay(1000);
    servo->giro(-90);
    delay(1000);
    servo->giro(90);
    delay(1000);
    servo->giro(0);
    delay(1000);*/

  /* servo->giroSuave(-90, 10);
    servo->giroSuave(0, 10);
    servo->giroSuave(90, 10);*/

  //PRUEBA DE SENSOR DE DISTANCIA
  //Serial1.println(sensorDistancia->getDistancia());

  //PRUEBA DE SENSOR DE DISTANCIA MOVIL
  /* Serial1.println("Distancia al frente:");
    Serial1.println(sensorDistanciaMovil->getDistancia(0));
    delay(250);
    Serial1.println("Distancia a la izquierda:");
    Serial1.println(sensorDistanciaMovil->getDistancia(-90));
    delay(250);
    Serial1.println("Distancia al frente:");
    Serial1.println(sensorDistanciaMovil->getDistancia(0));
    delay(250);
    Serial1.println("Distancia a la derecha:");
    Serial1.println(sensorDistanciaMovil->getDistancia(90));
    delay(250);*/
  /*float medidas[360];
    int numeroMedidas;
    numeroMedidas = sensorDistanciaMovil->getDistancia(-90, 90, medidas, 10);
    for(int i = 0; i < numeroMedidas; i++)
    {
    telemetria->enviar("Grado: ");
    telemetria->enviar((String)i);
    telemetria->enviar("distancia: ");
    telemetria->enviar((String)medidas[i]);
    }
  */

  //TEST LECTURAS DE CNY (FAlla el trasero derecho)
  //delay(250);
  /*Serial1.println("-----------------------");
    Serial1.println("Cny delantero derecho");
    Serial1.println(cnyDelDer->esNegro(4));
    Serial1.println(cnyDelDer->getVoltaje());*/
  /*Serial1.println("Cny trasero derecho");
    Serial1.println(cnyTraDer->esNegro(4.99));
    Serial1.println(cnyTraDer->getVoltaje());
    Serial1.println("Cny trasero izquierdo");
    Serial1.println(cnyTraIzq->esNegro(4));
    Serial1.println(cnyTraIzq->getVoltaje());*/

  //TEST DE CLASE BATERIA
  //telemetria->enviar((String)bateria->getVoltaje());
  //telemetria->enviar((String)botLaberinto->reguladorDeGiro());
  //delay(15000);
}

