#include <Servo.h>

#define IN1 8
#define IN2 9
#define IN3 10
#define IN4 11
#define ENA 5
#define ENB 6

#define IR_LEFT 2
#define IR_MID 3
#define IR_RIGHT 4

#define PUMP 7
#define SERVO_PIN 12

Servo sprayer;

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  pinMode(IR_LEFT, INPUT);
  pinMode(IR_MID, INPUT);
  pinMode(IR_RIGHT, INPUT);

  pinMode(PUMP, OUTPUT);
  digitalWrite(PUMP, LOW);

  sprayer.attach(SERVO_PIN);
  sprayer.write(90);

  Serial.begin(9600);
  Serial.println("IR Autonomous Water-Spraying Robot Ready!");
}

void loop() {
  int leftIR = digitalRead(IR_LEFT);
  int midIR = digitalRead(IR_MID);
  int rightIR = digitalRead(IR_RIGHT);

  Serial.print("L: "); Serial.print(leftIR);
  Serial.print(" M: "); Serial.print(midIR);
  Serial.print(" R: "); Serial.println(rightIR);

  // LOW means obstacle detected
  if (midIR == LOW) {
    stopMotors();
    digitalWrite(PUMP, HIGH);
    sprayWater();
    digitalWrite(PUMP, LOW);
    moveBackward();
    delay(600);
    turnRight();
    delay(400);
  } 
  else if (leftIR == LOW) {
    turnRight();
  } 
  else if (rightIR == LOW) {
    turnLeft();
  } 
  else {
    moveForward();
  }
}

// === Motor Movement Functions ===
void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 180);
  analogWrite(ENB, 180);
}

void moveBackward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, 180);
  analogWrite(ENB, 180);
}

void turnLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 180);
  analogWrite(ENB, 180);
}

void turnRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, 180);
  analogWrite(ENB, 180);
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void sprayWater() {
  sprayer.write(45);
  delay(400);
  sprayer.write(135);
  delay(400);
  sprayer.write(90);
}

