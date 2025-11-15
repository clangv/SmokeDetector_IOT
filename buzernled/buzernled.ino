int mq2Pin = A0;
int ledPin = D5;
int buzzerPin = D7;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  int sensorValue = analogRead(mq2Pin);
  Serial.print("MQ2 = ");
  Serial.println(sensorValue);

  // Adjust this threshold based on your readings
  int threshold = 60;

  if (sensorValue > threshold) {
    digitalWrite(ledPin, HIGH);
    digitalWrite(buzzerPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
    digitalWrite(buzzerPin, LOW);
  }

  delay(500);
}
