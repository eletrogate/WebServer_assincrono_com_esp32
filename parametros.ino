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
  server.on("/", HTTP_ANY, [](AsyncWebServerRequest* request) {
    // Listar todos os parâmetros
    int params = request->params(); // parâmetros
    int i; // índice
    for (i = 0; i < params; i++){
      AsyncWebParameter* p = request->getParam(i); // pega o cabeçalho do índice informado
      if (p->isFile()) // se parâmetro for um arquivo, ...
      {
        Serial.printf("FILE[%s]: %s, size: %u\n", p->name().c_str(), p->value().c_str(), p->size());
      } else if (p->isPost()) // senão, se parâmetro for do tipo POST, ...
      {
        Serial.printf("POST[%s]: %s\n", p->name().c_str(), p->value().c_str());
      } else // senão, parâmetro é do tipo GET, ...
      {
        Serial.printf("GET[%s]: %s\n", p->name().c_str(), p->value().c_str());
      }
    }
    String html = R"====(
    <html>
  <head>
    <meta charset = "utf-8">
    <script>
      function imprimeNaSerial()
      {
        var xhr = new XMLHttpRequest();
        xhr.open("POST", '/', true); // inicializa uma nova requisição, ou reinicializa uma requisição já existente.
        xhr.setRequestHeader("Content-Type", "application/x-www-form-urlencoded"); // define o valor do cabeçalho de uma requisição HTTP
        xhr.onreadystatechange = function() {
          if (this.readyState == 4 && this.status == 200) {
             // Typical action to be performed when the document is ready:
            alert("Requisição enviada com sucesso");
          }else if(this.readyState == 4 && this.status != 200){
          alert("Requisição não foi enviada, pois houve alguma falha");
          }
        };
        xhr.send("parametro1=123&outro-paramentro=xyz"); // envia uma requisição para o servidor.
      }
    </script>
  </head>
  <body>
    <h1>Teste com ESP32</h1>
    <p> Clique no botão abaixo e imprima na Serial dois Parâmetros POST (parametro1 com valor 123 e outro-parametro com valor xyz): </p>
    <button onclick="imprimeNaSerial()"> Imprimir Parâmetros POST na Serial</button>
  </body>
</html>
    )====";
    request->send(200,"text/html",html);
  });

  // Servidor começa à ouvir os clientes
  server.begin();
}

void loop() {}