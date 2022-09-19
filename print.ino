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
    AsyncResponseStream* response = request->beginResponseStream("text/html");
    response->print("<html>");
    response->print("<head> ");
    response->print("<meta charset='utf-8'/>");
    response->print("</head>");
    response->print("<body>");
    response->print("<h1>");
    response->printf("Olá %s",request->client()->remoteIP().toString().c_str());
    response->print("</h1>");
    response->print("<p>");
    response->print("Parágrafo aqui.");
    response->print("</p>");
    response->print("</body>");
    response->print("<html>");

    //envie a resposta por último
    request->send(response);
  });

  // Servidor começa à ouvir os clientes
  server.begin();
}

void loop() {}