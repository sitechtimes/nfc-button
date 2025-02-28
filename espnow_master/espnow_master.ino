/*
  Rui Santos & Sara Santos - Random Nerd Tutorials
  Complete project details at https://RandomNerdTutorials.com/esp-now-esp32-arduino-ide/
  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files.
  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
*/
#include <esp_now.h>
#include <WiFi.h>

// REPLACE WITH YOUR RECEIVER MAC Address A0:B7:65:25:34:C0
// 08:A6:F7:B1:C4:34

uint8_t broadcastAddress[] = {0xA0, 0xB7, 0x65, 0x25, 0x34, 0xC0};
// uint8_t broadcastAddress[] = {0x08, 0xA6, 0xF7, 0xB1, 0xC4, 0x34};


// Structure example to send data
// Must match the receiver structure

// Create a struct_message called myData
esp_now_peer_info_t peerInfo;

const int buttonPin = 21;
int lastState = LOW;  // the previous state from the input pin
int currentState;     // the current reading from the input pin

// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}
 
void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  // Init Serial Monitor
  Serial.begin(115200);
 
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
  // WiFi.begin();

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  // Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
}
 
void loop() {
  // Set values to send
  String macAddress = WiFi.macAddress();

  currentState = digitalRead(buttonPin);

  if (lastState == HIGH && currentState == LOW) {
    Serial.println("The button is pressed");
    // sendMessage(broadcastAddress, myData);

    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) macAddress.c_str(), sizeof(macAddress));
    if (result == ESP_OK) {
    Serial.println("Sent with success");
    }
    else {
      Serial.println("Error sending the data");
    }
    delay(1000);
    }
  else if (lastState == LOW && currentState == HIGH) {
    Serial.println("The button is released");
  }
  // save the the last state
  lastState = currentState;
}

