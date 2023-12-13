#include <SoftwareSerial.h> //Permite la comunicación serie en otros pines digitales además del 0 y el 1 (pines de comunicación serie por defecto)
#include <NewPing.h> //Librería para facilitar el uso del sensor ultrasónico
#include <Servo.h> //Librería para facilitar el uso del servo motor
#define TRIG_PIN A0//Define el pin A0 para vincularlo al pin Trigger del sensor ultrasónico
#define ECHO_PIN A1//Define el pin A1 para vincularlo al pin Trigger del sensor ultrasónico
#define MAX_DISTANCE 300//Define la distancia máxima medible por el sensor (en el caso de no especificarlo son 500cm por defecto)
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE); //Mediante este codigo asociamos los pines definidos previamente al sensor y la distancia máxima de sensado
Servo myservo;//Codigo para usar el servomotor 
int distance; //Variable para medir distancias
int motorDer1=7; //El pin 7 a In1 del L298N
int motorDer2=6; //El pin 6 a In2 del L298N
int motorIzq1=5; //El pin 5 a In3 del L298N
int motorIzq2=10; //El pin 10 a In10 del L298N
int PWM_Derecho=11; //El pin 11 de Arduino se conecta con el pin EnA el L298N
int PWM_Izquierdo=3; //El pin 3 de Arduino se conecta con el pin EnB el L298N
int luces=13; //El pin13 se conecta a la alimentación de las luces de posición
int velocidad = 255;

int readPing() { //Declaración de función para llevar a cabo el sensado
 delay(70);
 int cm = sonar.ping_cm(); //Devuelve la distancia en centímetros
if(cm==0)
 { cm = 250; }
 return cm; }
 
 int lookRight() //Función para medir la distancia a la derecha
{ myservo.write(12); //Servomotor a 12º
 delay(300);
int distance = readPing(); //Calcula la distancia en centímetros
delay(100);
 myservo.write(90); //Servomotor a 90º
return distance;}//Devuelve el valor de la distancia medida

int lookLeft() //Función para medir la distancia a la izquierda
{ myservo.write(160); //Servomotor a 160º
 delay(300);
int distance = readPing(); //Calcula la distancia en centímetros
delay(100);
myservo.write(90); //Servomotor a 90º
return distance; //Devuelve el valor de la distancia medida
 delay(100);}

 void setup(){
//Serial_2.begin(9600);
Serial.begin(9600);

 noInterrupts(); // deshabilitamos las interrupciones
  CLKPR = 1<<CLKPCE; // empezamos la secuencia de escritura
  CLKPR = 1; // seleccionamos el divisor desado, en nuestro caso el 1
  interrupts(); // habilitamos las interrupciones

  
pinMode(motorDer1, OUTPUT); //Configuración de los como pines de salida
pinMode(motorDer2, OUTPUT); 
pinMode(motorIzq1, OUTPUT); 
pinMode(motorIzq2, OUTPUT); 
pinMode(PWM_Derecho, OUTPUT);
pinMode(PWM_Izquierdo, OUTPUT);
pinMode(luces,OUTPUT);

myservo.attach(9); //Asigna el pin 9 de Arduino para el control de la posición del servomotor
myservo.write(90); //Servomotor a 90º

delay(2000);
distance = readPing(); //Mide y almacena el valor de la medida en la variable
delay(100);

}



//Definición de las funciones auxiliares que serán llamadas desde el bucle principal Modo de operación: Avanzar
void Avance(){ 
digitalWrite(motorDer1,HIGH);
digitalWrite(motorDer2,LOW);
digitalWrite(motorIzq1,HIGH);
digitalWrite(motorIzq2,LOW);
analogWrite(PWM_Derecho,220); //Velocidad motor derecho 220
analogWrite(PWM_Izquierdo,220); //Velocidad motor izquierdo 220
}
//Modo de operación: atras
void atras(){ 
digitalWrite(motorDer1,LOW);
digitalWrite(motorDer2,HIGH);
digitalWrite(motorIzq1,LOW);
digitalWrite(motorIzq2,HIGH);

analogWrite(PWM_Derecho,200); //Velocidad motor derecho 200
analogWrite(PWM_Izquierdo,200); //Velocidad motor izquierdo 200
}
//Modo de operación: Giro en sentido horario.
void giraDerecha(){
  digitalWrite(motorDer1,LOW);
digitalWrite(motorDer2,HIGH);
digitalWrite(motorIzq1,HIGH);
digitalWrite(motorIzq2,LOW);

analogWrite(PWM_Derecho,255); //Velocidad motor derecho 255
analogWrite(PWM_Izquierdo,255); //Velocidad motor izquierdo 255
}
//Modo de operación: Giro en sentido antihorario.

void giraIzquierda(){
digitalWrite(motorDer1,HIGH);
digitalWrite(motorDer2,LOW);
digitalWrite(motorIzq1,LOW);
digitalWrite(motorIzq2,HIGH);
analogWrite(PWM_Derecho,255); //Velocidad motor derecho 255
analogWrite(PWM_Izquierdo,255); //Velocidad motor izquierdo 255
}
//Modo de operación: Pararse
void parar(){
digitalWrite(motorDer1,LOW);
digitalWrite(motorDer2,LOW);
digitalWrite(motorIzq1,LOW);
digitalWrite(motorIzq2,LOW);
}

void giraDerechaAvanza (){
  
analogWrite(PWM_Derecho,velocidad+100 ); //Velocidad motor derecho 150
  
digitalWrite(motorDer1,HIGH);
digitalWrite(motorDer2,LOW);
digitalWrite(motorIzq1,HIGH);
digitalWrite(motorIzq2,LOW);

delay(30);

analogWrite(PWM_Izquierdo,velocidad); //Velocidad motor izquierdo 150

}

void giraIzquierdaAvanza (){
  
analogWrite(PWM_Izquierdo ,velocidad+100 ); //Velocidad motor derecho 255+100

  digitalWrite(motorDer1,HIGH);
digitalWrite(motorDer2,LOW);
digitalWrite(motorIzq1,HIGH);
digitalWrite(motorIzq2,LOW);


delay(30);

analogWrite(PWM_Derecho,velocidad); //Velocidad motor izquierdo 255

}

void giraIzquierdaRetrocede (){
  
analogWrite(PWM_Izquierdo ,velocidad+100 ); //Velocidad motor derecho 255+100

  digitalWrite(motorDer1,LOW);
digitalWrite(motorDer2,HIGH);
digitalWrite(motorIzq1,LOW);
digitalWrite(motorIzq2,HIGH);


delay(30);

analogWrite(PWM_Derecho,velocidad); //Velocidad motor izquierdo 255

}

void giraDerechaRetrocede (){
  
analogWrite(PWM_Derecho,velocidad+100 ); //Velocidad motor derecho 150
  
digitalWrite(motorDer1,LOW);
digitalWrite(motorDer2,HIGH);
digitalWrite(motorIzq1,LOW);
digitalWrite(motorIzq2,HIGH);

delay(30);

analogWrite(PWM_Izquierdo,velocidad); //Velocidad motor izquierdo 150

}

//Modo de operación: luces On/Off
void lucesOn(){
digitalWrite(luces,HIGH);
}
void lucesOFF(){
digitalWrite(luces,LOW);
}


//Modo de operación: Esquiva obstáculos
void EsquivaObstaculos() {
int distanceR = 0; //Variable para almacenar distancia a la derecha
int distanceL = 0; //Variable para almacenar distancia a la izquierda
distance = readPing(); //Mide y almacena el valor de la medida en la variable
delay(40);
if(distance<=20)
{ parar();
 delay(100);
atras();
 delay(650);
parar();
 delay(100);
 distanceR = lookRight(); //Mide y almacena el valor de la distancia a la derecha
 delay(200);

 distanceL = lookLeft(); //Mide y almacena el valor de la distancia a la izquierda
 delay(100);
 if(distanceR>=distanceL)
 {
giraDerecha();
delay (650);
parar(); 
}
else
 {
giraIzquierda();
delay (650);
parar(); 
}
}
else
{
Avance(); 
}
distance = readPing();
}

void loop() {

   EsquivaObstaculos() ;

}
