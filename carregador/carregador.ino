#include <WiFi.h>
#include <WebServer.h>
#include <Wire.h>
#include <Adafruit_INA219.h>
#include <LittleFS.h>

// Upload via LittleFS = Ctrl + Shift + P

Adafruit_INA219 ina219;

const char* REDE_SSID = "SSID_DA_REDE";
const char* REDE_SENHA = "SENHA_DA_REDE";

float tensaoNoShunt = 0.0;       // em mV
float tensaoNoBarramento = 0.0;  // em V
float correnteDaCarga = 0.0;     // em mA
float tesaoNaCarga = 0.0;        // em V
float potenciaDaCarga = 0.0;     // em mW

WebServer server(80);

void arquivoHTML() {
  File file = LittleFS.open("/index.html", "r");
  if (!file) {
    server.send(500, "text/plain", "Erro ao carregar a página");
    return;
  }

  String html = file.readString();
  file.close();
  server.send(200, "text/html", html);
}

void arquivoCSS() {
  File file = LittleFS.open("/styles.css", "r");
  if (!file) {
    server.send(500, "text/plain", "Erro ao carregar o CSS");
    return;
  }
  String css = file.readString();
  file.close();
  server.send(200, "text/css", css);
}

void arquivoJS() {
  File file = LittleFS.open("/script.js", "r");
  if (!file) {
    server.send(500, "text/plain", "Erro ao carregar o JS");
    return;
  }
  String js = file.readString();
  file.close();
  server.send(200, "application/javascript", js);
}

void dadosDoSensor() {
  String json = "{";
  json += "\"tensaoNoBarramento\":" + String(tensaoNoBarramento) + ",";
  json += "\"tensaoNoShunt\":" + String(tensaoNoShunt) + ",";
  json += "\"tesaoNaCarga\":" + String(tesaoNaCarga) + ",";
  json += "\"correnteDaCarga\":" + String(correnteDaCarga) + ",";
  json += "\"potenciaDaCarga\":" + String(potenciaDaCarga);
  json += "}";

  server.send(200, "application/json", json);
}

void setup() {
  Serial.begin(115200);

  if (!LittleFS.begin(true)) {
    Serial.println("Erro ao montar LITTLEFS");
    return;
  }

  WiFi.begin(REDE_SSID, REDE_SENHA);
  Serial.println("Conectando-se ao Wi-Fi...");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("Conectado ao Wi-Fi!");
  Serial.println("Endereço IP: " + WiFi.localIP().toString());

  if (!ina219.begin()) {
    Serial.println("Falha ao encontrar INA219");
    while (1) { delay(10); }
  }

  server.on("/", arquivoHTML);
  server.on("/styles.css", arquivoCSS);
  server.on("/script.js", arquivoJS);
  server.on("/data", dadosDoSensor);
  server.begin();
  Serial.println("Servidor web iniciado!");
}

void loop() {
  server.handleClient();

  tensaoNoShunt = ina219.getShuntVoltage_mV();
  tensaoNoBarramento = ina219.getBusVoltage_V();
  correnteDaCarga = ina219.getCurrent_mA();
  potenciaDaCarga = ina219.getPower_mW();
  tesaoNaCarga = tensaoNoBarramento + (tensaoNoShunt / 1000);

  delay(100);
}