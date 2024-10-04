#include <Wire.h>
#include <TimerOne.h>

unsigned long total_viagens = 0;
unsigned int viagens_ultimo_minuto = 0;
unsigned long minutos_total = 0;

void setup() {
  Wire.begin(25);
  Wire.onReceive(receberEvento);
  Serial.begin(9600);

  Timer1.initialize(60000);  
  Timer1.attachInterrupt(enviarMetricasParaComputador);  
}

void loop() {

}

void receberEvento(int quantos) {
  while (Wire.available()) {
    char c = Wire.read();
    if (c == 'x') {
      total_viagens++;
      viagens_ultimo_minuto++;
    }
  }
}

void enviarMetricasParaComputador() {
  float media_viagens_minuto;
  minutos_total++;

  if (minutos_total > 0) {
    media_viagens_minuto = (float)total_viagens / minutos_total;
  } else {
    media_viagens_minuto = 0;
  }

  Serial.print("Total de viagens: ");
  Serial.println(total_viagens);
  Serial.print("Viagens no último minuto: ");
  Serial.println(viagens_ultimo_minuto);
  Serial.print("Média de viagens por minuto: ");
  Serial.println(media_viagens_minuto);

  viagens_ultimo_minuto = 0;
}
