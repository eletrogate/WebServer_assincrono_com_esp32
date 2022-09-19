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

  // disponibiliza o url "/" por acesso somente via POST
  server.on("/", HTTP_POST, [](AsyncWebServerRequest * request) {
    // Verifique se o parâmetro POST existe ou não
    if (request->hasParam("nome-qualquer", true)) {
      AsyncWebParameter* p = request->getParam("nome-qualquer", true);
      Serial.printf("O parâmetro POST %s existe e possui o valor %s\n", p->name().c_str(), p->value().c_str());
    } else {
      Serial.print("O parâmetro POST nome-qualquer não existe nesta requisição\n");
    }
    request->send(200);
  });

  // disponibiliza o url "/" por acesso somente via GET
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    String html = R"====(
    <html>
  <head>
    <meta charset = "utf-8">
    <script>
      function imprimeNaSerial() // função, que quando clicar no botão, será enviado uma requisição POST para o server
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
        xhr.send("nome-qualquer=valor-qualquer"); // envia uma requisição para o servidor.
      }
    </script>
  </head>
  <body>
    <h1>Teste com ESP32</h1>
    <p> Clique no botão abaixo e imprima na Serial a verificação se um Parâmetro POST (nome-qualquer com valor valor-qualquer) existe ou não: </p>
    <button onclick="imprimeNaSerial()"> Imprimir Parâmetros POST na Serial</button>
  </body>
</html>
    )====";
    request->send(200, "text/html", html);
  });

  // Servidor começa à ouvir os clientes
  server.begin();
}

void loop() {}