#include <SoftwareSerial.h>

// VC-02 ka TX (Pin 8) -> Arduino Pin 2
// VC-02 ka RX (Pin 7) -> Arduino Pin 3
SoftwareSerial voiceSerial(2, 3);

const int light1Pin = 4;
const int fanPin    = 5;
const int tvPin     = 6;
const int light2Pin = 7;

void setup() {
  Serial.begin(9600);
  voiceSerial.begin(9600);

  pinMode(light1Pin, OUTPUT);
  pinMode(fanPin, OUTPUT);
  pinMode(tvPin, OUTPUT);
  pinMode(light2Pin, OUTPUT);

  // Active-LOW Relays: Shuru mein sab OFF (HIGH) rakho
  digitalWrite(light1Pin, HIGH);
  digitalWrite(fanPin, HIGH);
  digitalWrite(tvPin, HIGH);
  digitalWrite(light2Pin, HIGH);

  Serial.println("Voice Control System Ready!");
}

void loop() {
  if (voiceSerial.available() > 0) {
    byte cmd = voiceSerial.read(); // Seedha Hex byte padho

    Serial.print("Received Hex: 0x");
    if (cmd < 16) Serial.print("0");
    Serial.println(cmd, HEX);

    switch (cmd) {
      case 0xA0:
        Serial.println("System Wake Up (Saksham)!");
        break;

      case 0xA1: // TurnOn (Light 1 ON)
        digitalWrite(light1Pin, LOW);
        Serial.println("Action: Light 1 ON");
        break;

      case 0xA2: // Turnoff (Light 1 OFF)
        digitalWrite(light1Pin, HIGH);
        Serial.println("Action: Light 1 OFF");
        break;

      case 0xA3: // Fanon
        digitalWrite(fanPin, LOW);
        Serial.println("Action: Fan ON");
        break;

      case 0xA4: // Fanoff
        digitalWrite(fanPin, HIGH);
        Serial.println("Action: Fan OFF");
        break;

      case 0xA5: // TVon
        digitalWrite(tvPin, LOW);
        Serial.println("Action: TV ON");
        break;

      case 0xA6: // TVoff
        digitalWrite(tvPin, HIGH);
        Serial.println("Action: TV OFF");
        break;

      case 0xA7: // Secondlighton (Light 2 ON)
        digitalWrite(light2Pin, LOW);
        Serial.println("Action: Light 2 ON");
        break;

      case 0xA8: // Secondlightoff (Light 2 OFF)
        digitalWrite(light2Pin, HIGH);
        Serial.println("Action: Light 2 OFF");
        break;

      case 0xA9: // All devices ON
        digitalWrite(light1Pin, LOW);
        digitalWrite(fanPin, LOW);
        digitalWrite(tvPin, LOW);
        digitalWrite(light2Pin, LOW);
        Serial.println("Action: All Devices ON");
        break;

      case 0xAA: // All devices OFF
        digitalWrite(light1Pin, HIGH);
        digitalWrite(fanPin, HIGH);
        digitalWrite(tvPin, HIGH);
        digitalWrite(light2Pin, HIGH);
        Serial.println("Action: All Devices OFF");
        break;
    }
  }
}