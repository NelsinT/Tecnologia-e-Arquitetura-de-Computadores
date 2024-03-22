const int ledVermelho = 7;
const int ledVerde = 6;
const int ledVermelho_2 = 5;
const int ledVerde_2 = 4;
const int ledVerde_estacionamento = 3;
const int ledVermelho_estacionamento = 2;
const int trigPin = 13;
const int trigPin_2 = 11;
const int echoPin_2 = 10;
const int echoPin = 12;
const int buzzerPin = 9;
const int buzzerPin_2 = A4;
const int butao = 8;
const int light = A0;
int utilizador = 0;
int total_lugarVerde = 0;
int total_lugarVermelho = 0;
int total_lugarVerde_2 = 0;
int total_lugarVermelho_2 = 0;
int lugares_disponiveis = 2;
int button_State = 0;
int total_carros_entram_estacionamento1 = 0;
int total_carros_saem_estacionamento1 = 0;
int total_carros_entram_estacionamento2 = 0;
int total_carros_saem_estacionamento2 = 0;
int carro_status = 1; // 1 = entrar estacionamento 2 = sair
int carro_status2 = 1; // 1 = entrar estacionamento 2 = sair
int luz;
int ocupado_estacionamento2 = 0;
int ocupado_estacionamento1 = 0;
int distancia_carrosair = 100;
int distancia_carroentrar = 50;
int distancia_buzzer = 20;
int delay_buzzer = 3000;
void setup() {
  Serial.begin(9600);
  pinMode(ledVermelho, OUTPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledVermelho_2, OUTPUT);
  pinMode(ledVerde_2, OUTPUT);
  pinMode(ledVermelho_estacionamento, OUTPUT);
  pinMode(ledVerde_estacionamento, OUTPUT);
  pinMode(trigPin_2, OUTPUT);
  pinMode(echoPin_2, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(buzzerPin_2, OUTPUT);
  pinMode(butao, INPUT_PULLUP);
}

void loop() {
  int button_State = digitalRead(butao);
  int luz = analogRead(light);
  if (luz < 600) {
    digitalWrite(ledVermelho_estacionamento, LOW);
    digitalWrite(ledVerde_estacionamento, LOW);
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledVermelho, LOW);
    digitalWrite(ledVermelho_2, LOW);
    digitalWrite(ledVerde_2, LOW);
  } else {
    if (button_State == LOW) {
      if (lugares_disponiveis == 0) {
        Serial.println("Sem lugares de estacionamento");
      } else {
        Serial.print("Utilizador: ");
        Serial.print(++utilizador);
        Serial.print(", existe ");
        Serial.print(lugares_disponiveis);
        Serial.println(" lugar disponivel");
      }
    }
    
    delay(1000);
    
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    float duration = pulseIn(echoPin, HIGH);
    float distancia = (duration * 0.0343) / 2;
    delay(500);
    
    digitalWrite(trigPin_2, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin_2, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin_2, LOW);
    float duration_2 = pulseIn(echoPin_2, HIGH);
    float distancia_2 = (duration_2 * 0.0343) / 2;
    delay(500);
    
    if (distancia < distancia_buzzer) {
      digitalWrite(buzzerPin, HIGH);
      delay(delay_buzzer);
      digitalWrite(buzzerPin, LOW);
    }
   
    if (distancia_2 < distancia_buzzer) {
      digitalWrite(buzzerPin_2, HIGH);
      delay(delay_buzzer);
      digitalWrite(buzzerPin_2, LOW);
    }
    
    
    if (distancia > distancia_carrosair && carro_status == 1) {
      
      total_carros_saem_estacionamento1++;
      carro_status = 2;
      digitalWrite(ledVerde,HIGH);
      digitalWrite(ledVermelho,LOW);
      ocupado_estacionamento1 = 0;
      delay(1000);
    }

    if (distancia_2 > distancia_carrosair && carro_status2 == 1) {
      total_carros_saem_estacionamento2++;
      carro_status2 = 2;
      digitalWrite(ledVerde_2,HIGH);
      digitalWrite(ledVermelho_2,LOW);
      ocupado_estacionamento2 = 0;
      delay(1000);
    }    
    if (distancia < distancia_carroentrar && carro_status == 2) {
      digitalWrite(ledVermelho, HIGH);
      digitalWrite(ledVerde, LOW);
      carro_status = 1;
      total_carros_entram_estacionamento1++;
      ocupado_estacionamento1 = 1;
    }
    
    if (distancia_2 < distancia_carroentrar && carro_status2 == 2) {
      digitalWrite(ledVermelho_2, HIGH);
      digitalWrite(ledVerde_2, LOW);
      carro_status2 = 1;
      ocupado_estacionamento2 = 1 ;
      total_carros_entram_estacionamento2++;
    } 
    
    lugares_disponiveis = 2 - ocupado_estacionamento1  - ocupado_estacionamento2 ;
    
    if (lugares_disponiveis > 0) {
      digitalWrite(ledVerde_estacionamento, HIGH);
      digitalWrite(ledVermelho_estacionamento, LOW);
    } else {
      digitalWrite(ledVerde_estacionamento, LOW);
      digitalWrite(ledVermelho_estacionamento, HIGH);
    }
    
    Serial.print("Carros que entraram estacionamento 1: ");
    Serial.println(total_carros_entram_estacionamento1);
    Serial.print("Carros que sairam estacionamento 1: ");
    Serial.println(total_carros_saem_estacionamento1);
    Serial.print("Carros que entraram estacionamento 2: ");
    Serial.println(total_carros_entram_estacionamento2);
    Serial.print("Carros que sairam estacionamento 2: ");
    Serial.println(total_carros_saem_estacionamento2);
  }
}

