#include "Arduino.h"

void setup() {
  Serial.begin(9600);
  // Define o pino 13 como saida
  pinMode(D7, OUTPUT);
}

void loop() {
  digitalWrite(D7, HIGH);   // Acende o Led
  delay(1000);              // Aguarda 1 segundo
  digitalWrite(D7, LOW);    // Apaga o Led
  delay(1000);
}
