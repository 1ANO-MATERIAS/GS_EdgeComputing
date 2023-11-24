#include "ArduinoJson.h"
#include "EspMQTTClient.h"
#include "DHT.h"

// MQTT Configuracoes
EspMQTTClient client{
  "Wokwi-GUEST", //SSID do WiFi
  "",     // Senha do wifi
  "mqtt.tago.io",  // Endereço do servidor
  "Default",       // Usuario
  "85899ab0-3cbd-4bf4-b74a-3d49d0b17c05",         // Token do device
  "esp",           // Nome do device
  1883             // Porta de comunicação
};

#define DHT_SENSOR_PIN  22 // ESP32 pin GPIO22 connected to DHT22 sensor
#define DHT_SENSOR_TYPE DHT22
DHT dht_sensor(DHT_SENSOR_PIN, DHT_SENSOR_TYPE);

const int buzzerPin = 21;  // ESP32 GPIO21 pin connected to Buzzer's pin


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

  dht_sensor.begin(); // initialize the DHT sensor

  pinMode(buzzerPin, OUTPUT);       // set ESP32 pin to output mode

}
// Callback da EspMQTTClient
void onConnectionEstablished()
{}
char bufferJson[100];

void loop() {

  // read humidity
  float humi  = dht_sensor.readHumidity();
  // read temperature in Celsius
  float tempC = dht_sensor.readTemperature();

  StaticJsonDocument<300> documentoJson;
  documentoJson["variable"] = "Temperatura";
  documentoJson["value"] = tempC;
  documentoJson["unit"] = "°c";
  serializeJson(documentoJson, bufferJson);
  Serial.println(bufferJson);
  client.publish("topicoSaudeUnica", bufferJson);
  client.loop();

  documentoJson["variable"] = "Umidade";
  documentoJson["value"] = humi;
  documentoJson["unit"] = "%";
  serializeJson(documentoJson, bufferJson);
  Serial.println(bufferJson);
  client.publish("topicoSaudeUnica", bufferJson);
  client.loop();

  if (tempC > 15 && tempC < 30 && humi > 40 && humi < 70) {
    Serial.println("Buzina desligada");
    tone(buzzerPin, 0);  // turn on
  }
  else {
    tone(buzzerPin, 1000);  // turn on
    Serial.println("Buzina ligada");
  }

  delay(5000);

}