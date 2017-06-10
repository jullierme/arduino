#include <JsbIotSensorTouchCapacitive.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

const char* SSID = "JSBEsc";
const char* PASSWORD = "jj1234567890";

ESP8266WebServer server(80);

const byte pinLed = D7;//10;
const byte pinRele = D8;//6;
const short luzMinimaParaLedDesligado = 10;
const long sensibilidade = 50;
const byte pinSensorCapacitivo1 = D2;
const byte pinSensorCapacitivo2 = D4;

JsbIotSensorTouchCapacitive sensorTouch = JsbIotSensorTouchCapacitive(
	pinSensorCapacitivo1, pinSensorCapacitivo2, pinRele, pinLed, sensibilidade);

String getHtml(String title, String texto){
	String html = "";
	html += "<!doctype html>";
	html += "<html lang=\"pt-BR\" xmlns=\"http://www.w3.org/1999/html\">";
	html += "<head>";
	html += "<meta charset=\"UTF-8\">";
	html += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
	html += "<title>"+title+"</title>";
	html += "</head><body>";
	html += texto;
	html += "</body></html>";

	return html;
}

void paginaNaoEncontrada(){
	server.send(404, "text/html", getHtml("404", "Página não encontrada: "));
}

void statusRele(){
	server.send(200, "text/html", getHtml("Luz escritório",
		sensorTouch.isReleAtivado() ? "Ativado" : "Desativado"));
}

void acionarRele(){
	sensorTouch.acionarRele();
	server.send(200, "text/html", getHtml("Luz escritório", "Relé acionado!"));
}

void desligarRele(){
	sensorTouch.desligarRele();
	server.send(200, "text/html", getHtml("Luz escritório", "Relé desligado!"));
}

void setup(){
  //sensor.ativarLog();
  Serial.begin(115200);

	sensorTouch.ativarLog();
	sensorTouch.begin();
	sensorTouch.setResolucaoSensor(30);
	sensorTouch.getSensor().set_CS_Timeout_Millis(610000);

	Serial.println("Iniciar configuração wifi");
	WiFi.begin(SSID, PASSWORD);

  IPAddress ip = IPAddress(192,168,1,150);
	IPAddress dns = IPAddress(192,168,1,1);
	IPAddress gateway = IPAddress(192, 168, 1, 1);
	IPAddress subnet = IPAddress(255,255,255,1);

  WiFi.config(ip, dns, gateway, subnet);

	Serial.println("");
	  // Wait for connection
  while (WiFi.status() != WL_CONNECTED)
  {
		delay(500);
    Serial.print(".");
  }

  // Mostrando IP
  Serial.println("");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

	if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  // Atribuindo urls para funções
  // Quando não especificado método, uma função trata todos
	server.on("/", statusRele);
	server.on("/ligar", acionarRele);
	server.on("/status", statusRele);
  server.on("/desligar", desligarRele);
  server.onNotFound(paginaNaoEncontrada);

  // Iniciando servidor
  server.begin();

  // Apenas informando que servidor iniciou
  Serial.println("HTTP server started");
}

void loop(void){
  delay(100);
	server.handleClient();
	sensorTouch.executar();
}
