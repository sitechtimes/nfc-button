// Define the LED pin
const int ledPin = 2; // Use GPIO 2 for the onboard LED

void setup() {
  // Set the LED pin as an output
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Turn the LED on
  digitalWrite(ledPin, HIGH);
  delay(200);  // Wait 1 second

  // Turn the LED off
  digitalWrite(ledPin, LOW);
  delay(200);  // Wait 1 second
}