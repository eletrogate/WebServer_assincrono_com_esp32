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
    request->send(503); // Envia código 503 (O servidor não está pronto para manipular a requisição)
  });

  // Servidor começa à ouvir os clientes
  server.begin();
}

void loop() {}