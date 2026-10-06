/*
  VOICECHAIR - Voice-controlled wheelchair prototype
  Board : Arduino Uno
  Input : HC-05 Bluetooth (smartphone voice app sends 1 character)
  Drive : L298N motor driver + 2 DC geared motors
  Safety: HC-SR04 ultrasonic sensor (auto-stop when obstacle is close)

  WIRING
  HC-05  TX -> D2 (Arduino RX via SoftwareSerial)
  HC-05  RX -> D3 (use a voltage divider: 1k + 2k, since HC-05 RX is 3.3V)
  HC-05  VCC -> 5V, GND -> GND

  L298N  ENA -> D5 (PWM)   IN1 -> D6   IN2 -> D7   (Left motor)
  L298N  ENB -> D10 (PWM)  IN3 -> D8   IN4 -> D9   (Right motor)
  L298N  12V -> battery +, GND -> battery - AND Arduino GND (common ground!)

  HC-SR04 TRIG -> D11, ECHO -> D12, VCC -> 5V, GND -> GND

  COMMANDS (one character from the phone app)
  F = Forward, B = Backward, L = Left, R = Right, S = Stop
  0-9 = speed level (optional)
*/

#include <SoftwareSerial.h>

SoftwareSerial bt(2, 3);  // RX, TX

// Motor driver pins
const int ENA = 5, IN1 = 6, IN2 = 7;
const int ENB = 10, IN3 = 8, IN4 = 9;

// Ultrasonic pins
const int TRIG = 11, ECHO = 12;

const int STOP_DISTANCE_CM = 30;   // stop if obstacle closer than this
int speedPWM = 180;                // 0-255
char lastCmd = 'S';

void setup() {
  Serial.begin(9600);
  bt.begin(9600);                  // HC-05 default baud rate

  pinMode(ENA, OUTPUT); pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT); pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);
  pinMode(TRIG, OUTPUT); pinMode(ECHO, INPUT);

  stopMotors();
  Serial.println("VOICECHAIR ready");
}

void loop() {
  // 1. Read command from Bluetooth
  if (bt.available()) {
    char c = toupper(bt.read());
    if (c >= '0' && c <= '9') {
      speedPWM = map(c - '0', 0, 9, 100, 255);   // speed levels
      applyCommand(lastCmd);
    } else if (c == 'F' || c == 'B' || c == 'L' || c == 'R' || c == 'S') {
      lastCmd = c;
      applyCommand(c);
    }
  }

  // 2. Safety: block forward motion if obstacle is near
  if (lastCmd == 'F' && getDistanceCM() < STOP_DISTANCE_CM) {
    stopMotors();
    lastCmd = 'S';
    bt.println("Obstacle! Stopped.");
    Serial.println("Obstacle detected - stopped");
  }

  delay(50);
}

void applyCommand(char c) {
  switch (c) {
    case 'F':
      if (getDistanceCM() >= STOP_DISTANCE_CM) forward();
      else stopMotors();
      break;
    case 'B': backward(); break;
    case 'L': turnLeft(); break;
    case 'R': turnRight(); break;
    default:  stopMotors(); break;
  }
}

// ---------- Motor functions ----------
void setSpeed() {
  analogWrite(ENA, speedPWM);
  analogWrite(ENB, speedPWM);
}

void forward() {
  setSpeed();
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
}

void backward() {
  setSpeed();
  digitalWrite(IN1, LOW);  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);  digitalWrite(IN4, HIGH);
}

void turnLeft() {                 // left motor back, right motor forward
  setSpeed();
  digitalWrite(IN1, LOW);  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
}

void turnRight() {                // left motor forward, right motor back
  setSpeed();
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);  digitalWrite(IN4, HIGH);
}

void stopMotors() {
  analogWrite(ENA, 0); analogWrite(ENB, 0);
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
}

// ---------- Ultrasonic ----------
long getDistanceCM() {
  digitalWrite(TRIG, LOW);  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH); delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  long duration = pulseIn(ECHO, HIGH, 30000);   // 30 ms timeout
  if (duration == 0) return 999;                // no echo = clear
  return duration * 0.034 / 2;
}
