#include <ArduinoWebsockets.h>
#include <WiFi.h>

const char* ssid = "DOEGuest"; //Enter SSID
const char* password = "NYC$itevent"; //Enter Password
// const char* websockets_server = "ws://100.101.78.168:8080/"; //server adress and port
const char* websockets_server = "ws://echo.websocket.org";

using namespace websockets;

void onMessageCallback(WebsocketsMessage message) {
    Serial.print("Got Message: ");
    Serial.println(message.data());
}

void onEventsCallback(WebsocketsEvent event, String data) {
    if(event == WebsocketsEvent::ConnectionOpened) {
        Serial.println("Connnection Opened");
    } else if(event == WebsocketsEvent::ConnectionClosed) {
        Serial.println("Connnection Closed");
    } else if(event == WebsocketsEvent::GotPing) {
        Serial.println("Got a Ping!");
    } else if(event == WebsocketsEvent::GotPong) {
        Serial.println("Got a Pong!");
    }
}

WebsocketsClient client;
void setup() {
    Serial.begin(115200);

    Serial.println("Scanning for Wi-Fi networks...");
    int numNetworks = WiFi.scanNetworks();

    if (numNetworks == 0) {
        Serial.println("No networks found.");
    } else {
        Serial.println("Networks found:");
        for (int i = 0; i < numNetworks; i++) {
            Serial.printf("%d: %s, Signal Strength (RSSI): %d dBm, Encryption: %s\n", 
                i + 1, 
                WiFi.SSID(i).c_str(), 
                WiFi.RSSI(i),
                WiFi.encryptionType(i) == WIFI_AUTH_OPEN ? "Open" : "Secured");
        }
    }
    WiFi.scanDelete(); // Free memory

    // Connect to wifi
    Serial.print("Connecting to WiFi...");
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(1000);
    }

    Serial.println("\nWiFi Connected!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    // Setup Callbacks
    client.onMessage(onMessageCallback);
    client.onEvent(onEventsCallback);
    
    // Connect to server
    bool connected = client.connect(websockets_server);
    client.setInsecure();
    if (connected) {
        Serial.println("WebSocket Connected!");
        client.send("Hello WebSocket Server!");
        client.ping();
    } else {
        Serial.println("WebSocket Connection Failed!");
    }

    // Send a message
    client.send("Hi Server!");
    // Send a ping
    client.ping();
}

void loop() {
    client.poll();
}