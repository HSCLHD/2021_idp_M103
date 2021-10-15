#include <Wire.h>
#include <Adafruit_MotorShield.h>

int left_sensor_pin0 =10;
int left_sensor_pin1 =11;
int right_sensor_pin0 =12;
int right_sensor_pin1 =14; // don't use pin 13 sincw built in LED and resistor
int count = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(left_sensor_pin0, INPUT); 
  pinMode(left_sensor_pin1, INPUT);
  pinMode(right_sensor_pin0, INPUT); 
  pinMode(right_sensor_pin1, INPUT);

}

void loop() {
  // read the input pin:
  int leftState0 = digitalRead(left_sensor_pin0);
  int leftState1 = digitalRead(left_sensor_pin0);
  int rightState0 = digitalRead(right_sensor_pin0);  
  int rightState1 = digitalRead(right_sensor_pin1);    

  
  // print out the states of the sensors: test
  Serial.println(leftState0);
  Serial.println(leftState1);
  Serial.println(rightState0);  
  Serial.println(rightState1);    
  
  if (leftState1 == HIGH && rightState0 == HIGH){
      if (leftState0 == LOW && rightState1 == LOW){
        forwards();
      }
      else if (leftState0 == HIGH && rightState1 == HIGH){
        halt();
      }
  }
  else if (leftState1 == LOW && rightState0 == HIGH){
    left();
  }
  else if (leftState1 == HIGH && rightState0 == LOW){
    right();
  }
  else {
    //check increments if reached 100 break out loop and start ultrasonic sensing
    if (cout <= 100){
      forwards();
      }
      else{
        halt(); //for now just stop will add ultrasonic later                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        
      }
    }
    cout += 1;
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
  Serial.println("stopping ");
  LeftMotor->run(RELEASE);
  RightMotor->run(RELEASE);
}
