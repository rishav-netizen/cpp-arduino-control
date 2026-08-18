#include <Arduino.h>

const int R = 2;
const int G = 4;
const int B = 6;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);
  digitalWrite(R, LOW);
  digitalWrite(G, LOW);
  digitalWrite(B, LOW);

}

void loop() {
  // Serial.println("Hello from Arduino!\n");
  if (Serial.available() > 0)
  {
    char input = Serial.read();
    switch (input)
    {
    case 'R':
      digitalWrite(R, HIGH);
      digitalWrite(G, LOW);
      digitalWrite(B, LOW);
      Serial.println("RED LIGHT ON");
      break;

    case 'G':
      digitalWrite(R, LOW);
      digitalWrite(G, HIGH);
      digitalWrite(B, LOW);
      Serial.println("GREEN LIGHT ON");
      break;

    case 'B':
      digitalWrite(R, LOW);
      digitalWrite(G, LOW);
      digitalWrite(B, HIGH);
      Serial.println("BLUE LIGHT ON");
      break;
      
    default:
      digitalWrite(R, LOW);
      digitalWrite(G, LOW);
      digitalWrite(B, LOW);
      break;
    }
  }
  // put your main code here, to run repeatedly:
}