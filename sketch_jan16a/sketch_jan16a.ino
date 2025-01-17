#include <WiFi.h>
#include <HTTPClient.h>

const char* wifiSSID = "MeshNet";
const char* wifiPassword = "Guest@Home271";

const char* serverIP = "http://192.168.4.80:3000";

HTTPClient http;

const int buttonPIN = 0; // set to actual button pin
const int ledPIN = 2;

void setup() {
  Serial.begin(115200);

  pinMode(buttonPIN, INPUT_PULLUP);
  pinMode(ledPIN, OUTPUT);

  Serial.print("Connecting to Wi-Fi");
  WiFi.begin(wifiSSID, wifiPassword);
  
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    attempts++;

    if(attempts == 20) {
      Serial.println("Connection Timed Out.");
    }
  }
  Serial.println("\nConnected to Wi-Fi");

  http.begin(serverIP);
  http.addHeader("Content-Type", "application/json");

  // sendButtonPress();
}

void sendButtonPress() {
  int httpResponseCode = http.POST("secretMessage");

  if (httpResponseCode > 0) {
    Serial.print("HTTP POST Response Code: ");
    Serial.println(httpResponseCode);
    String payload = http.getString();
    Serial.println("Response:");
    Serial.println(payload);
    if(payload == "win") {
      for(int i = 0; i < 10; i++) {
        digitalWrite(ledPIN, HIGH);
        delay(500);
        digitalWrite(ledPIN, LOW);
        delay(500); 
      }
    } else {
      digitalWrite(ledPIN, HIGH);
      delay(10000);
      digitalWrite(ledPIN, LOW);
    }
  } else {
    Serial.println("POST request failed, error: " + String(httpResponseCode));
    Serial.println(http.errorToString(httpResponseCode).c_str());
  }
}

void loop() {
  int buttonState = digitalRead(buttonPIN);
  if(buttonState == LOW) {
    sendButtonPress();
    delay(200);
  }
}
