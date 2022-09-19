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
    const char index_html[] PROGMEM = R"====(
      <html>
        <head>
          <meta charset='utf-8'/>
        </head>
        <body>
          <h1>
            Arduino
          </h1>
          
          <p>
            Arduino é uma plataforma de prototipagem eletrônica de hardware livre e de placa única,
            projetada com um microcontrolador Atmel AVR com suporte de entrada/saída embutido, uma 
            linguagem de programação padrão, a qual tem origem em Wiring, e é essencialmente C/C++. 
            O objetivo do projeto é criar ferramentas que são acessíveis, com baixo custo, 
            flexíveis e fáceis de se usar por principiantes e profissionais. Principalmente para 
            aqueles que não teriam alcance aos controladores mais sofisticados e ferramentas mais 
            complicadas.
          </p>
          <p>
            Pode ser usado para o desenvolvimento de objetos interativos independentes, 
            ou ainda para ser conectado a um computador hospedeiro. 
            Uma típica placa Arduino é composta por um controlador, algumas linhas de E/S digital e analógica, 
            além de uma interface serial ou USB, para interligar-se ao hospedeiro, que é usado para programá-la 
            e interagi-la em tempo real. A placa em si não possui qualquer recurso de rede, porém é comum combinar 
            um ou mais Arduinos deste modo, usando extensões apropriadas chamadas de shields. 
            A interface do hospedeiro é simples, podendo ser escrita em várias linguagens. 
            A mais popular é a Processing, mas outras que podem comunicar-se com a conexão serial são: Max/MSP, 
            Pure Data, SuperCollider, ActionScript e Java. 
            Em 2010 foi realizado um documentário sobre a plataforma chamado Arduino: The Documentary.
          </p>
          <figure>
            <img src='https://upload.wikimedia.org/wikipedia/commons/thumb/7/71/Arduino-uno-perspective-transparent.png/681px-Arduino-uno-perspective-transparent.png' width='300px'>
            <figcaption>
              Arduino versão Uno. Créditos: Wikipedia
            </figcaption>
          </figure>
          
          <p>
            O nome Arduino vem de um bar em Ivrea, Itália, onde alguns dos fundadores do projeto costumavam se reunir. 
            O bar foi nomeado após Arduíno de Ivrea, que foi o marquês da Marca de Ivrea e Rei da Itália de 1002 a 1014.
          </p>
          <p>
            Fonte: <a href='https://pt.wikipedia.org/wiki/Arduino' target='_blank'>https://pt.wikipedia.org/wiki/Arduino</a>
          </p>
        </body>
      <html>
    )===="; // grande matriz de caracteres
    request->send_P(200, "text/html", index_html); // Envia a resposta
  });

  // Servidor começa à ouvir os clientes
  server.begin();
}

void loop() {}