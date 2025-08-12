#include "AFMotor.h"
#include <Servo.h>

#define echopin A0 // echo pin
#define trigpin A1 // Trigger pin1

Servo myservo;

const int MOTOR_1 = 2; 
const int MOTOR_2 = 1; 
const int MOTOR_3 = 3; 
const int MOTOR_4 = 4; 

int i = 0;

AF_DCMotor motor1(MOTOR_1, MOTOR12_64KHZ); // create motor object, 64KHz pwm
AF_DCMotor motor2(MOTOR_2, MOTOR12_64KHZ); // create motor object, 64KHz pwm
AF_DCMotor motor3(MOTOR_3, MOTOR12_64KHZ); // create motor object, 64KHz pwm
AF_DCMotor motor4(MOTOR_4, MOTOR12_64KHZ); // create motor object, 64KHz pwm

int distance_L, distance_F, distance_R;
long distance;

int set = 30;
 
void setup() {
  myservo.attach(10);
  myservo.write(115);

  pinMode (trigpin, OUTPUT);
  pinMode (echopin, INPUT );
  
  delay(300);
  motor1.setSpeed(120);          // set the motor speed to 0-255
  motor2.setSpeed(120);
  motor3.setSpeed(120);
  motor4.setSpeed(120);

//  distance_F = data();
}

void loop() {
  distance_F = data();
  if (distance_F > set){
    motor1.run(FORWARD);         // turn it on going forward
    motor2.run(FORWARD); 
    motor3.run(FORWARD); 
    motor4.run(FORWARD);

//  checkMap();
    }
    else{hc_sr4();}
}


long data(){
  digitalWrite(trigpin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigpin, HIGH);
  delayMicroseconds(10);
  distance = pulseIn (echopin, HIGH);
  return distance / 29 / 2;
}


void compareDistance(){
  if (distance_R > distance_L){
  motor1.run(BACKWARD);   // turn it on going right
  motor2.run(BACKWARD);
  motor3.run(FORWARD); 
  motor4.run(FORWARD); 
    delay(400);
  }
  else if (distance_L > distance_R){
  motor1.run(FORWARD);  // the other left
  motor2.run(FORWARD); 
  motor3.run(BACKWARD); 
  motor4.run(BACKWARD);
    delay(400);
  }
  else{
  motor1.run(BACKWARD);  // the other way
  motor2.run(BACKWARD);
  motor3.run(BACKWARD); 
  motor4.run(BACKWARD); 
   delay(300);
  motor1.run(BACKWARD);   // turn it on going right
  motor2.run(BACKWARD);
  motor3.run(FORWARD); 
  motor4.run(FORWARD); 
    delay(500);
  }
}

void hc_sr4(){
    motor1.run(RELEASE);         // stopped
    motor2.run(RELEASE);
    motor3.run(RELEASE);
    motor4.run(RELEASE);
   
    myservo.write(50);
    delay(300);
    distance_R = data();
    delay(100);
    myservo.write(180);
    delay(300);
    distance_L = data();
    delay(100);
    myservo.write(115);
    delay(300);
    compareDistance();
}


