// Inclusão das bibliotecas
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

// Instanciação do objeto da classe AsyncWebServer
AsyncWebServer server(80);

// Constantes das credenciais do WiFi
const char* ssid = "<SSID>";
const char* password = "<SENHA>";

String processor(const String& var)
{
  if(var == "OLA_PARA_MODELO")
    return "Olá mundo!";
  return String();
}

void setup() {

  // Conecta-se ao Ponto de acesso com as credenciais fornecidas
  WiFi.begin(ssid, password);

  // disponibiliza o url "/"
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    const char index_html[] PROGMEM = R"====(
      <html>
        <head>
          <meta charset='utf-8'/>
        </head>
        <body>
          <h1>
            Teste
          </h1>          
          <p>
            Mensagem %OLA_PARA_MODELO% recebida.
          </p>          
        </body>
      <html>
    )===="; // grande matriz de caracteres
    request->send_P(200, "text/html", index_html, processor); // Envia a resposta
  });

  // Servidor começa à ouvir os clientes
  server.begin();
}

void loop() {}