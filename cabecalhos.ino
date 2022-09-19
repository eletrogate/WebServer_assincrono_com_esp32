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
    //Listar todos os cabeçalhos coletados
    int headers = request->headers();  // cabeçalhos
    int i;                             // índice
    for (i = 0; i < headers; i++) {
      AsyncWebHeader* h = request->getHeader(i);  // pega o cabeçalho do índice informado
      Serial.printf("Cabeçalho[%s]: %s\n",
                    h->name().c_str(),    // O nome do cabeçalho
                    h->value().c_str());  // O valor do cabeçalho
    }
  });

  // Servidor começa à ouvir os clientes
  server.begin();
}

void loop() {}