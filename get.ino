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

  Serial.begin(115200);

  // disponibiliza o url "/"
  server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
    // Verifique se o parâmetro GET existe ou não
    if (request->hasParam("nome-qualquer")) {
      AsyncWebParameter* p = request->getParam("nome-qualquer");
      Serial.printf("O parâmetro GET %s existe e possui o valor %s\n", p->name().c_str(), p->value().c_str());
    }else{
      Serial.print("O parâmetro GET nome-qualquer não existe nesta requisição\n");
    }
  });

  // Servidor começa à ouvir os clientes
  server.begin();
}

void loop() {}