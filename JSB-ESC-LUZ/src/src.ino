#include <JsbIotSensorTouchCapacitive.h>
#include <JsbIotSensorRadioRF24L01.h>

const byte pinLed = 3;
const byte pinRele = 2;
const short luzMinimaParaLedDesligado = 10;
const long sensibilidade = 50;
const byte pinSensorCapacitivo1 = 5;
const byte pinSensorCapacitivo2 = 6;

const byte _pinRadioEntrada = 9;
const byte _pinRadioSaida = 10;

const uint64_t _pipeEscrita = 0x4a534245;
const uint64_t _pipeLeitura = 0x4a53424c;

JsbIotSensorRadioRF24L01 sensorRadio = JsbIotSensorRadioRF24L01(_pinRadioEntrada,
	_pinRadioSaida, _pipeEscrita, _pipeLeitura);

JsbIotSensorTouchCapacitive sensorTouch = JsbIotSensorTouchCapacitive(
  pinSensorCapacitivo1, pinSensorCapacitivo2, pinRele, pinLed, sensibilidade);

void enviarDados(char valor){
  char dados[1];
  dados[0] = valor;
  sensorRadio.enviarDados(dados);

  delay(300);
}

//Sempre vai receber um array de no máximo 32 posições pois a lib RF24 só envia
//no máximo 32 bytes por vez
void onReceberDados(char dados[]){
	//Serial.println("onReceberDados");

  if(dados[0] == 'L'){
    sensorTouch.acionarRele();
  } else if(dados[0] == 'D'){
    sensorTouch.desligarRele();
  } else if(dados[0] == 'N'){
      sensorTouch.ativaOuDesativaRele();
  } else if(dados[0] == 'N'){
    Serial.println("Informando situação do relé");
    Serial.print("Situação ");
    Serial.println(sensorTouch.isReleAtivado() ? "L" : "D");

    enviarDados(sensorTouch.isReleAtivado() ? 'L' : 'D');
  }
}

void setup() {
  //Serial.begin(9600);
  Serial.begin(57600);
	
  sensorRadio.ativarLog();
  sensorRadio.begin();
	sensorRadio.getRadio().setDataRate(RF24_250KBPS);
  sensorRadio.getRadio().setPALevel(RF24_PA_MIN);

	sensorTouch.ativarLog();
	sensorTouch.begin();
	sensorRadio.onDadosRetornados(onReceberDados);
}

void loop(){
  sensorRadio.iniciarRecepcaoDeDados();
  sensorTouch.executar();
  delay(100);
}
