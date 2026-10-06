#include <SoftwareSerial.h>

SoftwareSerial bt(2, 3);

const int ENA = 5, IN1 = 6, IN2 = 7;
const int ENB = 10, IN3 = 8, IN4 = 9;
const int TRIG = 11, ECHO = 12;

const int STOP_DISTANCE_CM = 30;
int speedPWM = 180;
char lastCmd = 'S';

void setup() {
  Serial.begin(9600);
  bt.begin(9600);

  pinMode(ENA, OUTPUT); pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT); pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);
  pinMode(TRIG, OUTPUT); pinMode(ECHO, INPUT);

  stopMotors();
}

void loop() {
  if (bt.available()) {
    char c = toupper(bt.read());
    if (c >= '0' && c <= '9') {
      speedPWM = map(c - '0', 0, 9, 100, 255);
      applyCommand(lastCmd);
    } else if (c == 'F' || c == 'B' || c == 'L' || c == 'R' || c == 'S') {
      lastCmd = c;
      applyCommand(c);
    }
  }

  if (lastCmd == 'F' && getDistanceCM() < STOP_DISTANCE_CM) {
    stopMotors();
    lastCmd = 'S';
    bt.println("Obstacle! Stopped.");
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

void turnLeft() {
  setSpeed();
  digitalWrite(IN1, LOW);  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
}

void turnRight() {
  setSpeed();
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);  digitalWrite(IN4, HIGH);
}

void stopMotors() {
  analogWrite(ENA, 0); analogWrite(ENB, 0);
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
}

long getDistanceCM() {
  digitalWrite(TRIG, LOW);  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH); delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  long duration = pulseIn(ECHO, HIGH, 30000);
  if (duration == 0) return 999;
  return duration * 0.034 / 2;
}
