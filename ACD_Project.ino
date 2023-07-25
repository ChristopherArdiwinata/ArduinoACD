#include <AFMotor.h>

#define voltNotDetected 0
#define voltDetected 1

AF_DCMotor motor1(1); // left wheels
AF_DCMotor motor2(2); // right wheels
AF_DCMotor motor3(3); // claw for egg
AF_DCMotor motor4(4); // pulley but error wheels
//int infraRed = A3;
int currentPhase = -1;
int claw = 0;
void setup() {
  motor1.setSpeed(200);
  motor1.run(RELEASE);
  motor2.setSpeed(200);
  motor2.run(RELEASE);
  motor3.setSpeed(200);
  motor3.run(RELEASE);
  motor4.setSpeed(200);
  motor4.run(RELEASE);
  pinMode(A5,INPUT);
  //A5 = THE photo trnasistor that detects
  //pinMode(A3,OUTPUT);
  Serial.begin(9600);
  currentPhase = -1;
}
/* MOTOR 4 IN ARDUINO IS MOTOR2 IN HERE*/
void loop() {  
  if (currentPhase == -1) {
    // Beginning Phase, the ACD moves until an infrared is detected
    delay(1000);
    moveForward();
    digitalWrite(infraRed,HIGH);
    currentPhase++;
    
  }
  if (currentPhase == 0 && infraRed() == voltDetected) {
    // an infrared is detected , the ACD collects the egg
    // moves again untill infrared is detected
    stopMoving();
    delay(500);
    dropClaw(14);
    delay(300);
    getEgg(5);
    delay(200);
    liftClaw(19);
    moveForward();
    currentPhase++;
  }
  if (infraRed()== voltDetected) {
    stopMoving();
    if(currentPhase == 1) {
      // when infrared is detected, drop the egg 
      // and move backward to starting point
      dropClaw(15); 
      dropEgg(5);
      liftClaw(18);
      moveBackward();
    } 
    currentPhase++;
  }
}
/* --------------------------------------------------------------------------------------------------------------------------------*/
int infraRed() {
  if (analogRead(A5)* (5./1023.) > 0 ) {
    Serial.println("THERE IS VOLTS"); 
    return 1;
  } else {
    Serial.println("no VOLTS");
    return 0;
  }
}
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
    // lift the claw n seconds
  motor3.run(FORWARD);                               
  delay(n*1000);
  motor3.run(RELEASE);
  delay(500);
}
void dropClaw(float n) {
    // drop the claw n seconds
  motor3.run(BACKWARD);                               
  delay(n*1000);
  motor3.run(RELEASE);
  delay(500);
}

void getEgg(float n) {
    // close the pickup claw n seconds
  motor4.run(BACKWARD);                               
  delay(n*1000);
  motor4.run(RELEASE);
  delay(500);
}

void dropEgg(float n) {
    // open the pickup claw n seconds
  motor4.run(FORWARD);                               
  delay(n*1000);
  motor4.run(RELEASE);
  delay(500);
}
 
  
  
  
