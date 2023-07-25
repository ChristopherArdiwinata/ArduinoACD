#include <AFMotor.h>

#define voltNotDetected 0
#define voltDetected 1

AF_DCMotor motor1(1); // left wheels
AF_DCMotor motor2(2); // right wheels
AF_DCMotor motor3(3); // claw for egg
AF_DCMotor motor4(4); // pulley but error wheels
int bandPassFilter = A4;
int infraRed = A3;
int currentPhase = -1;
int claw = 0;
void setup() {
  pinMode(bandPassFilter, INPUT);
  pinMode(infraRed, OUTPUT);
  motor1.setSpeed(200);
  motor1.run(RELEASE);
  motor2.setSpeed(200);
  motor2.run(RELEASE);
  motor3.setSpeed(200);
  motor3.run(RELEASE);
  motor4.setSpeed(200);
  motor4.run(RELEASE);
  Serial.begin(9600);
  currentPhase = -1;
}
/* MOTOR 4 IN ARDUINO IS MOTOR2 IN HERE*/
void loop() { 
   
  if (currentPhase == -1) {
    digitalWrite(infraRed, HIGH);
    moveForward();
    currentPhase++;
  }
  if (currentPhase == 0 && bandPass() == voltDetected) {
    digitalWrite(infraRed,LOW);
    stopMoving();
    delay(500);
    dropClaw(14);
    delay(300);
    getEgg(5);
    delay(200);
    liftClaw(19);
    moveForward();
    delay(500);
    digitalWrite(infraRed,HIGH);
    currentPhase++;
  }
  if (bandPass()== voltDetected) {
    digitalWrite(infraRed,LOW);
    stopMoving();
    
    if(currentPhase == 1) {
      dropClaw(15);
      dropEgg(5);
      liftClaw(19);
      moveBackward();
      delay(500);
      digitalWrite(infraRed,HIGH);
    } 
    currentPhase++;
  }
}
/* --------------------------------------------------------------------------------------------------------------------------------*/
void moveForward() {
    // Move the ACD forward n seconds
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  delay(100);
}

void moveBackward() {
    // Move the ACD backwards n seconds
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  delay(100);
}
void stopMoving() {
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  delay(100);
}
void liftClaw(float n) {
    // Move the ACD backwards n seconds
  motor3.run(FORWARD);                               
  delay(n*1000);
  motor3.run(RELEASE);
  delay(500);
}
void dropClaw(float n) {
    // Move the ACD backwards n seconds
  motor3.run(BACKWARD);                               
  delay(n*1000);
  motor3.run(RELEASE);
  delay(500);
}

void getEgg(float n) {
    // Move the ACD backwards n seconds
  motor4.run(BACKWARD);                               
  delay(n*1000);
  motor4.run(RELEASE);
  delay(500);
}

void dropEgg(float n) {
    // Move the ACD backwards n seconds
  motor4.run(FORWARD);                               
  delay(n*1000);
  motor4.run(RELEASE);
  delay(500);
}
int bandPass() {
  float num = analogRead(bandPassFilter)* (5./1023.);
  Serial.print("Volts in State zero is ");
  Serial.println(num);
  delay(200);
  if (num > 0) {
    return voltDetected;
  }
  return voltNotDetected;
}
  
  
  
