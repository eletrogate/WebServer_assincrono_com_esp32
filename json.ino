// Inclusão das bibliotecas
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "AsyncJson.h"
#include "ArduinoJson.h"

// Instanciação do objeto da classe AsyncWebServer
AsyncWebServer server(80);

// Constantes das credenciais do WiFi
const char* ssid = "<SSID>";
const char* password = "<SENHA>";

void setup() {

  // Conecta-se ao Ponto de acesso com as credenciais fornecidas
  WiFi.begin(ssid, password);

  Serial.begin(115200);

  // disponibiliza o url "/"
  server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
    AsyncResponseStream* response = request->beginResponseStream("application/json");
    DynamicJsonDocument doc(1024);
    doc["heap"] = ESP.getFreeHeap();
    doc["ssid"] = "Rede_De_Testes";
    serializeJson(doc, *response);
    request->send(response);
  });

  // Servidor começa à ouvir os clientes
  server.begin();
}

void loop() {}