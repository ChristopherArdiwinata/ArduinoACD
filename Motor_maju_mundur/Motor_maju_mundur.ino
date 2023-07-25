#include <AFMotor.h>
AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
void setup() {
  // put your setup code here, to run once:
  motor1.setSpeed(400);
  motor1.run(RELEASE);
  motor2.setSpeed(400);
  motor2.run(RELEASE);
  motor3.setSpeed(4n00);
  motor3.run(RELEASE);
  //motor4.setSpeed(200);
  //motor4.run(RELEASE);
 
}

void loop() {
  // put your main code here, to run repeatedly:
  motor1.run(FORWARD);
  delay(3000);
  motor1.run(RELEASE);
  motor2.run(FORWARD);
  delay(3000);
  motor2.run(RELEASE);
  delay(3000);
  //motor3.run(FORWARD);
  //motor2.run(FORWARD);
    //motor4.run(FORWARD);
   // delay(10000);
 //motor3.run(BACKWARD);
// motor2.run(BACKWARD); 
 //motor1.run(BACKWARD);
 //motor2.run(BACKWARD); 
 //delay(5000); 
 //  motor4.run(BACKWARD);  
}
