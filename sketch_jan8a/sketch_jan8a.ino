#include <PubSubClient.h>

#include <WiFi.h>
#include <PubSubClient.h>

// Wi-Fi credentials
const char* ssid = "DOEGuest";
const char* password = "NYC$itevent";

// MQTT broker details
const char* mqttServer = "70ae867d15a74e699cbf5e0c0306eda4.s1.eu.hivemq.cloud";
const int mqttPort = 8883;
const char* mqttUser = "admin";
const char* mqttPassword = "Adminpassword1";

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);

  Serial.print("Connecting to Wifi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to Wifi");

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

      // Subscribe to a topic
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
