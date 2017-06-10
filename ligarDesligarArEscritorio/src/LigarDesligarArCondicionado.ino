/*
 * IRremote: IRsendRawDemo - demonstrates sending IR codes with sendRaw
 * An IR LED must be connected to Arduino PWM pin 3.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 *
 * IRsendRawDemo - added by AnalysIR (via www.AnalysIR.com), 24 August 2015
 *
 * This example shows how to send a RAW signal using the IRremote library.
 * The example signal is actually a 32 bit NEC signal.
 * Remote Control button: LGTV Power On/Off.
 * Hex Value: 0x20DF10EF, 32 bits
 *
 * It is more efficient to use the sendNEC function to send NEC signals.
 * Use of sendRaw here, serves only as an example of using the function.
 *
 */

// PWM pin 3
#include <IRremote.h>

IRsend irsend;

int khz = 38; // 38kHz carrier frequency for the NEC protocol

//liga em 23 graus
unsigned int irSinalLigar[] = {4508,4424,572,1624,568,528,572,1620,572,1624,572,524,572,528,568,1624,572,524,572,528,572,1624,568,528,596,500,572,1624,572,1620,572,528,572,1624,568,528,568,1624,572,524,576,1620,572,1624,572,1620,572,1624,572,1624,572,1624,568,528,572,1624,572,524,568,528,572,528,568,528,568,532,568,524,572,1628,568,528,568,1628,568,528,568,528,572,528,568,528,568,1628,568,524,572,1624,572,528,568,1624,572,1620,576,1624,568,1624,572,5276,4520,4416,572,1628,568,524,596,1600,596,1600,572,528,568,528,568,1624,596,500,572,528,592,1600,600,496,576,524,572,1624,572,1620,576,524,572,1620,572,528,572,1624,568,524,596,1600,596,1596,576,1620,596,1600,572,1620,572,1624,572,528,592,1600,596,504,596,500,596,504,572,520,600,500,572,524,596,1600,572,524,596,1600,596,500,600,496,596,504,572,524,596,1600,596,500,596,1600,596,500,596,1600,572,1620,600,1596,580,1616,596};

unsigned int irSinalDesligar[] = {4460,4448,568,1628,568,532,564,1628,568,1624,572,528,568,532,564,1632,560,532,568,532,564,1628,568,532,568,528,568,1628,568,1624,568,532,568,1624,568,532,568,1624,568,1628,564,1628,572,1624,572,552,540,1628,572,1624,568,1652,568,504,592,504,568,532,564,532,568,1648,548,528,568,528,568,1628,568,1624,568,1628,568,528,568,532,568,528,568,532,564,532,568,528,568,528,568,532,568,1624,568,1628,568,1624,572,1624,568,1628,568,5284,4488,4444,572,1624,568,532,568,1624,568,1628,568,528,568,532,568,1624,572,528,568,528,564,1628,572,528,568,528,568,1624,572,1624,568,532,568,1624,568,532,568,1624,568,1628,568,1624,572,1624,568,532,568,1624,568,1628,568,1628,564,532,568,528,568,532,564,532,568,1624,572,528,568,528,568,1628,568,1648,544,1628,568,528,568,528,572,552,544,528,568,556,544,528,568,528,568,532,568,1624,572,1624,568,1628,568,1624,568,1624,572};

void setup(){
  Serial.begin(115200);
}

void loop() {
  Serial.println("Ligando ar condicionado");
  Serial.println(sizeof(irSinalLigar) / sizeof(irSinalLigar[0]));

  irsend.sendRaw(irSinalLigar, sizeof(irSinalLigar) / sizeof(irSinalLigar[0]), khz); //Note the approach used to automatically calculate the size of the array.
  delay(5000); //In this example, the signal will be repeated every 5 seconds, approximately.

  Serial.println("Desligando ar condicionado");
  Serial.println(sizeof(irSinalDesligar) / sizeof(irSinalDesligar[0]));

  irsend.sendRaw(irSinalDesligar, sizeof(irSinalDesligar) / sizeof(irSinalDesligar[0]), khz);
  delay(5000);
}
