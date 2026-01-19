#include <ESP8266WiFi.h>

const char* ssid = "STARLINK";
const char* password = "legazpi2025";

WiFiServer server(80);

// Pins
#define LIGHT_PIN D5
#define FAN_PIN D6
#define BUZZER_PIN D7
#define STATUS_LED D2
#define MQ2_PIN A0

int smokeThreshold = 80;  // Adjust as needed
bool alarmTriggered = false;

void setup() {
  Serial.begin(9600);  // PlatformIO Serial Monitor baud

  pinMode(LIGHT_PIN, OUTPUT);
  pinMode(FAN_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(STATUS_LED, OUTPUT);

  digitalWrite(LIGHT_PIN, LOW);
  digitalWrite(FAN_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(STATUS_LED, LOW);

  // Connect to WiFi
  Serial.print("Connecting to WiFi: ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  int counter = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    counter++;

    // Timeout after 20 seconds
    if (counter > 40) {
      Serial.println();
      Serial.println("Failed to connect to WiFi. Check SSID/password.");
      break;
    }
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println();
    Serial.print("Connected! IP Address: ");
    Serial.println(WiFi.localIP());
  }

  server.begin();
}

void loop() {
  // ===================== MQ2 READING =====================
  int smokeValue = analogRead(MQ2_PIN);
  bool smokeDetected = smokeValue > smokeThreshold;

  Serial.print("MQ2 Value: ");
  Serial.println(smokeValue);

  // ===================== ALARM LOGIC =====================
  if (smokeDetected && !alarmTriggered) {
    tone(BUZZER_PIN, 1000);
    digitalWrite(STATUS_LED, HIGH);
    alarmTriggered = true;
  }

  if (!smokeDetected && alarmTriggered) {
    noTone(BUZZER_PIN);
    digitalWrite(STATUS_LED, LOW);
    alarmTriggered = false;
  }

  // ===================== HTTP SERVER =====================
  WiFiClient client = server.available();
  if (!client) return;

  String req = client.readStringUntil('\r');
  client.flush();

  // Light control
  if (req.indexOf("/light/on") != -1) digitalWrite(LIGHT_PIN, HIGH);
  if (req.indexOf("/light/off") != -1) digitalWrite(LIGHT_PIN, LOW);

  // Fan control
  if (req.indexOf("/fan/on") != -1) digitalWrite(FAN_PIN, HIGH);
  if (req.indexOf("/fan/off") != -1) digitalWrite(FAN_PIN, LOW);

  // Manual alarm off
  if (req.indexOf("/alarm/off") != -1) {
    noTone(BUZZER_PIN);
    digitalWrite(STATUS_LED, LOW);
    alarmTriggered = false;
  }

  // Response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/plain");
  client.println();

  if (req.indexOf("/status") != -1) {
    client.print(smokeDetected ? "SMOKE" : "NORMAL");
  } else {
    client.print("OK");
  }
}
