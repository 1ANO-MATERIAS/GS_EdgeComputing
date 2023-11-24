#include "ArduinoJson.h"
#include "EspMQTTClient.h"
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"

// MQTT Configuracoes
EspMQTTClient client{
  "Wokwi-GUEST", //SSID do WiFi
  "",     // Senha do wifi
  "mqtt.tago.io",  // Endereço do servidor
  "Default",       // Usuario
  "81ad26f3-d9a3-4b7b-b56b-89360e69be12",         // Token do device
  "esp",           // Nome do device
  1883             // Porta de comunicação
};

int state;
int previous_state;

#define PIN_RED    23 // GPIO23
#define PIN_GREEN  19 // GPIO22
#define PIN_BLUE   18 // GPIO21

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define BTN_1 32
#define BTN_2 17
int button_1_state;
int button_2_state;

String problema;
String crise;

int exec_semanal;

void setup() {

  Serial.begin(9600);
  Serial.println("Conectando WiFi");
  while (!client.isWifiConnected()) {
    Serial.print('.'); client.loop(); delay(1000);
  }
  Serial.println("WiFi Conectado");
  Serial.println("Conectando com Servidor MQTT");
  while (!client.isMqttConnected()) {
    Serial.print('.'); client.loop(); delay(1000);
  }
  Serial.println("MQTT Conectado");

  pinMode(12, INPUT);

  pinMode(PIN_RED,   OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);
  pinMode(PIN_BLUE,  OUTPUT);

  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("failed to start SSD1306 OLED"));
    while (1);
  }
  oled.setCursor(0, 0);

  pinMode(BTN_1, INPUT_PULLUP);
  pinMode(BTN_2, INPUT_PULLUP);

  button_1_state = digitalRead(BTN_1);
  button_2_state = digitalRead(BTN_2);

  problema == "";
  crise == "";

  exec_semanal = 0;

}
// Callback da EspMQTTClient
void onConnectionEstablished()
{}
char bufferJson[100];

void loop() {
  
  state = digitalRead(12);
  button_1_state = digitalRead(BTN_1);
  button_2_state = digitalRead(BTN_2);

  if(state == 1 && previous_state == 0) {
    previous_state = state;
    Serial.println("Switch state 1");
    oled.clearDisplay();
    oled.setTextSize(1);         // set text size
    oled.setTextColor(WHITE);    // set text color
    oled.setCursor(0, 10);       // set position to display
    oled.println("Voce esta sentindo depressao ou ansiedade?"); // set text
    oled.setCursor(0, 40);       // set position to display
    oled.println("Depressao   Ansiedade"); // set text
    oled.display();

    while (button_1_state == HIGH && button_2_state == HIGH) {
      button_1_state = digitalRead(BTN_1);
      button_2_state = digitalRead(BTN_2);
      Serial.println(button_1_state);
      Serial.println(button_2_state);
      delay(500);
    }

    if (button_1_state == LOW) {
      problema = "depressao";
    }
    else{
      problema = "ansiedade";
    }
    oled.clearDisplay();
    oled.setTextSize(1);         // set text size
    oled.setTextColor(WHITE);    // set text color
    oled.setCursor(0, 10);       // set position to display
    oled.println("Voce esta tendo uma  crise?"); // set text
    oled.setCursor(0, 40);       // set position to display
    oled.println("   Sim         Nao"); // set text
    oled.display();
    delay(2000);
    button_1_state = digitalRead(BTN_1);
    button_2_state = digitalRead(BTN_2);

    while (button_1_state == HIGH && button_2_state == HIGH) {
      button_1_state = digitalRead(BTN_1);
      button_2_state = digitalRead(BTN_2);
      delay(500);
    }

    if (button_1_state == LOW) {
      crise = "sim";
    }
    else{
      crise = "não";
    }

    if (problema == "depressao"){
      oled.clearDisplay();
      oled.setTextSize(1);         // set text size
      oled.setTextColor(WHITE);    // set text color
      oled.setCursor(0, 10);       // set position to display
      oled.println("Uma dica - assistir  um desenho que goste muito!"); // set text
      oled.display();
    }
    else {
      oled.clearDisplay();
      oled.setTextSize(1);         // set text size
      oled.setTextColor(WHITE);    // set text color
      oled.setCursor(0, 10);       // set position to display
      oled.println("Uma dica - ouvir uma musica calma que     goste muito!"); // set text
      oled.display();
    }

    if(problema == "depressao"){
    analogWrite(PIN_RED,   255);
    analogWrite(PIN_GREEN, 234);
    analogWrite(PIN_BLUE,  108);
    }

    if(problema == "ansiedade"){
    analogWrite(PIN_RED,   0);
    analogWrite(PIN_GREEN, 201);
    analogWrite(PIN_BLUE,  204);
    }

    exec_semanal++;

    StaticJsonDocument<300> doc;
    doc["variable"] = "Problema";
    doc["value"] = problema;
    serializeJson(doc, bufferJson);
    client.publish("topicoEngSoft", bufferJson);
    client.loop();
    delay(3000);

    doc["variable"] = "Crise";
    doc["value"] = crise;
    serializeJson(doc, bufferJson);
    client.publish("topicoEngSoft", bufferJson);
    client.loop();
    delay(3000);

    doc["variable"] = "ExecucoesSemanais";
    doc["value"] = exec_semanal;
    serializeJson(doc, bufferJson);
    client.publish("topicoEngSoft", bufferJson);
    client.loop();
    delay(3000);

    Serial.println(problema);
    Serial.println(crise);
    Serial.println(exec_semanal);

  }
  else if (state == 0){
  Serial.println("Switch state 2");
  previous_state = state;
  oled.clearDisplay();
  oled.display();
  analogWrite(PIN_RED,   0);
  analogWrite(PIN_GREEN, 0);
  analogWrite(PIN_BLUE,  0);
  }


  delay(2000);

}