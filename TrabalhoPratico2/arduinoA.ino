#include <Servo.h>
#include <Wire.h>

const int butao_elevador_1 = 2;
const int butao_elevador_2 = 3;
const int led_elevador = 4;
const int alarme = 5;
const int porta_elevador = 6;
const int porta_elevador2 = A0;
const int segA = 7;
const int segB = 8;
const int segC = 9;
const int segD = 10;
const int segE = 11;
const int segF = 12;
const int segG = 13;

volatile bool chamarAndar1 = false;
volatile bool chamarAndar2 = false;
int andarAtual = 1;  
int viagens = 0;

Servo portaServo;
Servo porta2Servo; 

void setup() {
  pinMode(butao_elevador_1, INPUT_PULLUP);
  pinMode(butao_elevador_2, INPUT_PULLUP);
  pinMode(led_elevador, OUTPUT);
  pinMode(alarme, OUTPUT);
  portaServo.attach(porta_elevador);
  portaServo.write(0); 
  porta2Servo.attach(porta_elevador2); 
  porta2Servo.write(0); 
  pinMode(segA, OUTPUT);
  pinMode(segB, OUTPUT);
  pinMode(segC, OUTPUT);
  pinMode(segD, OUTPUT);
  pinMode(segE, OUTPUT);
  pinMode(segF, OUTPUT);
  pinMode(segG, OUTPUT);
  Serial.begin(9600);
  Serial.println("Sistema de controle do elevador iniciado.");
  Wire.begin();

  attachInterrupt(digitalPinToInterrupt(butao_elevador_1), chamarAndar1Handler, FALLING);
  attachInterrupt(digitalPinToInterrupt(butao_elevador_2), chamarAndar2Handler, FALLING);

  exibirAndar();
}

void loop() {
    if (chamarAndar1) {
      chamarAndar1 = false;
      moverParaAndar(1);
    }

  if (chamarAndar2) {
    chamarAndar2 = false;
    moverParaAndar(2);
  }
}

void chamarAndar1Handler() {
  chamarAndar1 = true;
}

void chamarAndar2Handler() {
  chamarAndar2 = true;
}

void moverParaAndar(int andar) {
  if (andarAtual == andar) {
    digitalWrite(alarme, HIGH);
    abrirPorta();
    delay(1000);  
    digitalWrite(alarme, LOW);
    delay(4000); 
    fecharPorta();
    Serial.print("Elevador parou no andar ");
    Serial.println(andarAtual);
  } else {
    abrirPorta();
    delay(5000); 
    fecharPorta();

    Serial.print("Elevador iniciando deslocamento para o andar ");
    Serial.println(andar);
    
    digitalWrite(led_elevador, HIGH); 
    Wire.beginTransmission(25);
  	Wire.write('x');
  	Wire.endTransmission();
    delay(5000);  
    digitalWrite(led_elevador, LOW);  
    
    andarAtual = andar;
    abrirPorta();
    Serial.print("Elevador parou no andar ");
    Serial.println(andarAtual);
    delay(5000);  
    fecharPorta();
    
     
  
  }
  exibirAndar();
}

void abrirPorta() {
  if (andarAtual == 1) {
    for (int pos = 0; pos <= 90; pos += 1) {
      portaServo.write(pos);
      delay(15);  
    }
  } else if (andarAtual == 2) {
    for (int pos = 0; pos <= 90; pos += 1) {
      porta2Servo.write(pos);
      delay(15);  
    }
  }
}

void fecharPorta() {
  if (andarAtual == 1) {
    for (int pos = 90; pos >= 0; pos -= 1) {
      portaServo.write(pos);
      delay(15);  
    }
  } else if (andarAtual == 2) {
    for (int pos = 90; pos >= 0; pos -= 1) {
      porta2Servo.write(pos);
      delay(15);  
    }
  }
} 

void exibirAndar() {
  if (andarAtual == 1) {
    digitalWrite(segA, LOW);
    digitalWrite(segB, HIGH);
    digitalWrite(segC, HIGH);
    digitalWrite(segD, LOW);
    digitalWrite(segE, LOW);
    digitalWrite(segF, LOW);
    digitalWrite(segG, LOW);
  } else if (andarAtual == 2) {
    digitalWrite(segA, HIGH);
    digitalWrite(segB, HIGH);
    digitalWrite(segC, LOW);
    digitalWrite(segD, HIGH);
    digitalWrite(segE, HIGH);
    digitalWrite(segF, LOW);
    digitalWrite(segG, HIGH);
  }
}


