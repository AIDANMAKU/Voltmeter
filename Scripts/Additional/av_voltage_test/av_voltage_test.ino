const int numReadings = 10;
int readings[numReadings];
int total = 0;
int average = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  for (int i = 0; i < numReadings; i++) {
    readings[i] = analogRead(A0);
    total += readings[i];
    delay(10);
  }
  average = total / numReadings;
  float voltage = (average / 1024.0)* 5.0; // Calculate the voltage
  Serial.print(voltage);
  Serial.println("V");
  total = 0;
  delay(100);
}
