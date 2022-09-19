// Inclusão das bibliotecas
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

// Instanciação do objeto da classe AsyncWebServer
AsyncWebServer server(80);

// Constantes das credenciais do WiFi
const char* ssid = "<SSID>";
const char* password = "<SENHA>";

void setup() {

  // Conecta-se ao Ponto de acesso com as credenciais fornecidas
  WiFi.begin(ssid, password);

  // disponibiliza o url "/"
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->redirect("/page2"); // redireciona para page2
  });

  // disponibiliza o url "/page2"
  server.on("/page2", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(200, "text/plain", "Voce esta na page2!");
  });

  // Servidor começa à ouvir os clientes
  server.begin();
}

void loop() {}