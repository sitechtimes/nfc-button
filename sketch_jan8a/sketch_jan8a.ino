#include <PubSubClient.h>

#include <WiFi.h>
#include <PubSubClient.h>

// Wi-Fi credentials
const char* ssid = "DOEGuest";
const char* password = "NYC$itevent";

// MQTT broker details

// const char* mqttServer = "70ae867d15a74e699cbf5e0c0306eda4.s1.eu.hivemq.cloud";
// const int mqttPort = 8883;
// const char* mqttUser = "admin";
// const char* mqttPassword = "Adminpassword1";

// const char* mqttServer = "b37.mqtt.one";
// const int mqttPort = 8083;
// const char* mqttUser = "deltuy8445";
// const char* mqttPassword = "30dinoqrtx";

const char* mqttServer = "kef90981.ala.us-east-1.emqxsl.com";
const int mqttPort = 8883;
const char* mqttUser = "admin";
const char* mqttPassword = "adminpassword";

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);

  bool connected = connectWiFi();
  if(!connected) {
    Serial.println('WiFi not connected');
  } else {
    Serial.println('WiFi connected');
  }

  // Configure MQTT client
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback); // Set callback called when receiving a message
}

bool connectWiFi() {
  Serial.print("Connecting to Wifi...");
  WiFi.begin(ssid, password);
  int attempts = 0;

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    attempts++;

    if(attempts >= 10) {
      return false;
    }
  }
  Serial.println("\nConnected to Wifi");
  Serial.println(WiFi.localIP());
  return true;
}

bool configMQTTClient() {
  // Configure MQTT client
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback); // Set callback called when receiving a message
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  String message = "test";
  Serial.print("Publishing: ");
  Serial.println(message);

  // Send a message to a topic
  client.publish("buttonPresses", message.c_str());
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Connecting to MQTT broker...");
    if (client.connect("ESP32Client",  mqttUser, mqttPassword)) {
      Serial.println("connected");
      client.subscribe("buttonPresses");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      delay(5000);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message received on topic: ");
  Serial.println(topic);

  Serial.print("Payload: ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}
