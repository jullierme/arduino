#include "JsbSensorPresenca/JsbSensorPresenca.h"

short PINO_SENSOR_PRESENSA = 7;
short PINO_RELE = 6;
int TEMPO = 17000;

JsbSensorPresenca sensorPresenca(PINO_SENSOR_PRESENSA, PINO_RELE);

void setup(){
  sensorPresenca.setTempoMinimoLuzAcesa(13000);
  sensorPresenca.ativarLog();
  //sensorPresenca.ativarDelayDe1Segundo();
  Serial.begin(115200);
}

void loop() {
  sensorPresenca.executar();
}
