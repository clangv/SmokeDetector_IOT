#include <ESP8266WiFi.h>

const char* ssid = "STARLINK";        // Replace with your WiFi name
const char* password = "legazpi2025"; // Replace with your WiFi password

void setup() {
  Serial.begin(115200);  // Open Serial Monitor at 9600 baud
  delay(100);         // Give time for Serial to start

  Serial.print("Connecting to WiFi: ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  int counter = 0;

  // Wait until connected or timeout
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    counter++;

    if (counter > 40) { // ~20 seconds timeout
      Serial.println();
      Serial.println("Failed to connect to WiFi. Check SSID/password or WiFi network.");
      break;
    }
  }

  // Check if connected
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println();
    Serial.println("WiFi connected successfully!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("Not connected to WiFi.");
  }
}

void loop() {
  // Nothing needed here
}
