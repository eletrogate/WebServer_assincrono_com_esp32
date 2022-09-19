// Inclusão das bibliotecas
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <FS.h>
#include <SPIFFS.h>

// Instanciação do objeto da classe AsyncWebServer
AsyncWebServer server(80);

// Constantes das credenciais do WiFi
const char* ssid = "<SSID>";
const char* password = "<SENHA>";

void setup() {

  // Conecta-se ao Ponto de acesso com as credenciais fornecidas
  WiFi.begin(ssid, password);

  Serial.begin(115200);

  if(!SPIFFS.begin(true)){
    Serial.println("Ocorreu um erro ao montar SPIFFS");
    return;
  }

  // disponibiliza o url "/"
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    // Disponibiliza a página /index.html
    request->send(SPIFFS, "/index.html");

  });

  // Servidor começa à ouvir os clientes
  server.begin();
}

void loop() {}