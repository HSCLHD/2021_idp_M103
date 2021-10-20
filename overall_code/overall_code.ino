#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <Servo.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

// Select which 'port' M1, M2, rightMotor or leftMotor. In this case, rightMotor and leftMotor
Adafruit_DCMotor *rightMotor = AFMS.getMotor(3);
Adafruit_DCMotor *leftMotor = AFMS.getMotor(4);

// Initialise servo
Servo front;
Servo back;


void setup() {
  // put your setup code here, to run once:

}

int getDistance(int trigPin, int echoPin){
  // returns the distance between the wall and the ultrasonic sensor
  
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  long duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  int distance= duration*0.034/2;
  // Prints the distance on the Serial Monitor
  return distance;
}


void forwards(){
  LeftMotor->setSpeed(motor_speed); 
  RightMotor->setSpeed(motor_speed);
  LeftMotor->run(FORWARD);
  RightMotor->run(FORWARD);
}

void right(){
  Serial.println("turning right ");
  LeftMotor->setSpeed(motor_speed); 
  RightMotor->setSpeed(0.1*motor_speed);
  LeftMotor->run(FORWARD);
  RightMotor->run(FORWARD);
}

void left(){
  Serial.println("turning left ");
  LeftMotor->setSpeed(0.1*motor_speed); 
  RightMotor->setSpeed(motor_speed);
  LeftMotor->run(FORWARD);
  RightMotor->run(FORWARD);
}

void halt(){
  // halts motors
  leftMotor->setSpeed(0);
  rightMotor->setSpeed(0);
  digitalWrite(movePin, LOW);
}
