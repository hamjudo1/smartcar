/*
*/
// We will need the Servo soon...
#include <Servo.h>
// And the sonar board
#include <ST_HW_HC_SR04.h>

int rgtSensor = A0;  
int lftSensor = A1;  
const float leftForward = 0.4;
const float rightForward = 0.4;

const int led=13;
const int triggerPin = 11;
const int echoPin = 12;
const int bin2Pin = 3;
const int bin1Pin = 10;
const int ain1Pin = 5;
const int ain2Pin = 6;

ST_HW_HC_SR04 ultrasonicSensor(triggerPin, echoPin); // ST_HW_HC_SR04(TRIG, ECHO)
const float speedOfSoundInMetersPerSecond = 343.0;
const float speedOfSoundInCMPerMicroSecond = 100.0*speedOfSoundInMetersPerSecond/1000000.0;
int distanceInCM() {
  int hitTime = ultrasonicSensor.getHitTime(); // In microseconds
  if ( hitTime == 0) {
    hitTime = ultrasonicSensor.getTimeout();
  }
  return(int) (speedOfSoundInCMPerMicroSecond * hitTime);
  
}
void setup() {
  Serial.begin(9600);
  Serial.println("Hello Universe.");
  pinMode(led,OUTPUT);
  pinMode(triggerPin,OUTPUT);
  pinMode(echoPin,INPUT);
  ultrasonicSensor.setTimeout(2900); //Makes the maximum range be 50cm.
 
  pinMode(ain1Pin,OUTPUT);
  pinMode(ain2Pin,OUTPUT);
  pinMode(bin1Pin,OUTPUT);
  pinMode(bin2Pin,OUTPUT);
  delay(1000);  // One second delay so you can click "SEND" in the Serial Monitor after seeing "Hello Universe"
  if (Serial.available() ) { // was "SEND" clicked?
    while(true) {                    // If so loop forever
      int rgtValue = analogRead(A0); // Reading the sensors
      int lftValue = analogRead(A1); 
   
      Serial.print(lftValue);       // and printing the values  
      Serial.print(", ");
      Serial.print(rgtValue);
      Serial.print(", cm: ");
      Serial.println(distanceInCM());
      delay(500);
    }
  }
}

void doMotor(int in1, int in2, float speed) {
  speed = constrain(speed,-1.0,1.0);
  if ( speed > 0.0 ) {
    analogWrite(in1,int(255.0*speed));
    analogWrite(in2,0);
  } else {
    analogWrite(in2,-int(255.0*speed));
    analogWrite(in1,0);
  }
}
void doMotors(float left, float right) {
    doMotor(bin1Pin,bin2Pin,left);
    doMotor(ain1Pin,ain2Pin,right);
}
void loop() {
  int rightValue = analogRead(A0); // Reading the sensors
  int leftValue = analogRead(A1); // higher numbers are darker.
  int delta = rightValue - leftValue;
  delta = constrain(delta,-50,50);
  int distance = constrain(distanceInCM(),10,35);

 
  float accel = (float)map(distance,10,35,0,1000)/1000.0;

  float leftSpeed = accel *(leftForward+float(delta)/200.0);
  float rightSpeed = accel * (rightForward-float(delta)/200.0);
  doMotors(leftSpeed,rightSpeed);
  if ( false ) {
    Serial.print(leftValue);       // and printing the values  
    Serial.print(", ");
    Serial.print(rightValue);
    Serial.print(", cm: ");
    Serial.print(distance);
    Serial.print(", ");
    Serial.print(accel);  
    Serial.print(leftSpeed);
    Serial.print(", ");
    Serial.println(rightSpeed);
  }
}
