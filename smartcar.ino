/*

*/
// We will need the Servo soon...
#include <Servo.h>
// And the sonar board
#include <ST_HW_HC_SR04.h>

const int led=13;

const int trigPin = 12; //For the sonar 
const int echoPin = 8;   // For the sonar
const int servoPin = 9; 
const int bin2Pin = 3;
const int bin1Pin = 10;
const int ain1Pin = 5;
const int ain2Pin = 6;

void setup() {
    pinMode(led,OUTPUT);
    pinMode(ain1Pin,OUTPUT);
    pinMode(ain2Pin,OUTPUT);
    pinMode(bin1Pin,OUTPUT);
    pinMode(bin2Pin,OUTPUT);
}

void doMotor(int in1, int in2, float speed) {
  if ( speed > 0.0 ) {
    analogWrite(in1,int(255.0*speed));
    digitalWrite(in2,0);
  } else {
    analogWrite(in2,-int(255.0*speed));
    digitalWrite(in1,0);
  }
}
void doMotors(float left, float right) {
    doMotor(bin1Pin,bin2Pin,left);
    doMotor(ain1Pin,ain2Pin,right);
}
void loop() {
  int i;
  for(i=0; i<5; i++) {
    doMotors(0.7,0.7); // Go straight ahead
    digitalWrite(led,HIGH);
    delay(600);
    doMotors(0.7,0.0);
    digitalWrite(led,LOW);
    delay(600);
  }
  doMotors(0.0,0.0);
  delay(100);
  for(i=0;i<5;i++) {
    doMotors(-0.7,-0.7);
    delay(600);
    doMotors(0.0,-0.7);
    delay(600);
  }
  doMotors(0.0,0.0);
  delay(100);
}
