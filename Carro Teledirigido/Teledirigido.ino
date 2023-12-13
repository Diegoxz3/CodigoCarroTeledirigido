#include <SoftwareSerial.h>
//SoftwareSerial Serial_2 (2, 3); // Crea una nueva conexión serie- Pin2(RX) a TX y Pin3(TX)  a RX
String  Mensaje="" ;// Variable de cadena de caracteres para almacenar el mensaje
int motorDer1=7; //El pin 7 a In1 del L298N
int motorDer2=6; //El pin 6 a In2 del L298N
int motorIzq1=5; //El pin 5 a In3 del L298N
int motorIzq2=10; //El pin 10 a In10 del L298N
int PWM_Derecho=11; //El pin 11 de Arduino se conecta con el pin EnA el L298N
int PWM_Izquierdo=3; //El pin 3 de Arduino se conecta con el pin EnB el L298N
int luces=13; //El pin13 se conecta a la alimentación de las luces de posición
int velocidad = 255;

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

void loop() {
 // Leemos los datos recibidos 
  while(Serial.available()>0){
    Mensaje+=(char)Serial.read();
    Serial.println(Mensaje);
  }
  

  
  if(Mensaje!=""){
    Mensaje = Mensaje[0];
    if(Mensaje == "S"){
       parar();
    }else
    if(Mensaje == "F"){
      Avance();
    }else
    if(Mensaje == "I"){
     giraDerechaAvanza ();
    }else
    if(Mensaje == "B"){
      atras();
    }else
    if(Mensaje == "H"){
      giraIzquierdaRetrocede();
    }else
    if(Mensaje == "J"){
      giraDerechaRetrocede ();
    }else
    if(Mensaje == "L"){
     giraIzquierda();
    }else
     if(Mensaje == "G"){
    giraIzquierdaAvanza();
    }else
    if(Mensaje == "R"){
      giraDerecha();
    }
    
    if(Mensaje == "W"){
      digitalWrite(luces, HIGH);
      
    }else
        if (Mensaje == "w"){
      digitalWrite(luces, LOW);
     
    }
    

    // Damos la orden como ejecutada y esperamos la siguiente
    Mensaje=""; 
  }
}
  
