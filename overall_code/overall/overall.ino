//'FORWARDS' IN CODE = 'FORWARD' ON AGV
//remember to set D10 high while driving, low when stopped (contorls amber LED)

#include <Wire.h>
#include <Adafruit_MotorShield.h>

#define left_sensor_pin0 A3
#define left_sensor_pin1 A2
#define right_sensor_pin0 A1
#define right_sensor_pin1 A0
#define hall_pin A4

int left_sensor_value0;      // Left line sensor value-  higher number => lighter
int left_sensor_value1;
int right_sensor_value0;     // Right line sensor value
int right_sensor_value1;
int hall_value; //hall sensor return value

int delta_threshold = 100;// Cut-off for sensor reading being over the line or not
int line_line_threshold = 700;
#define motor_speed 255     // Standard speed of motor
int both_option = 1;
int both_happening = 0;
int left0;
int left1;
int right0;
int right1;

void forwards ();
void halt ();
void left ();
void right ();

unsigned long prev_increment_time_0 = 0;
unsigned long prev_increment_time_1 = 0;
const long min_increment_interval = 1000;

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

// Select motor ports
Adafruit_DCMotor *LeftMotor = AFMS.getMotor(3);
Adafruit_DCMotor *RightMotor = AFMS.getMotor(4);

void setup() {
  // Set up serial communication
  Serial.begin(9600);
  AFMS.begin();
}

void loop() {
  // Read line sensors and output values
  left_sensor_value0  = analogRead(left_sensor_pin0);
  left_sensor_value1  = analogRead(left_sensor_pin1);
  right_sensor_value0 = analogRead(right_sensor_pin0);
  right_sensor_value1 = analogRead(right_sensor_pin1);
  /*Serial.print(left_sensor_value0);
  Serial.print(left_sensor_value1);
  Serial.print(right_sensor_value0);
  Serial.print();

  Serial.println(both_option);
  Serial.print("Left: ");
  Serial.print(left_sensor_value);
  Serial.print("     Right: ");
  Serial.println(right_sensor_value);*/
  // Left sensor over line
  
  if (left_sensor_value1>line_threshold && right_sensor_value0>line_threshold && left_sensor_value0>line_threshold && right_sensor_value1 > line_threshold) {

    forwards();
  }
  // Right sensor over line
  /*else if (left_sensor_value1<line_threshold && right_sensor_value0<line_threshold && left_sensor_value0<line_threshold && right_sensor_value1 < line_threshold) {

    halt();
  }*/
  else if (left_sensor_value1<line_threshold && right_sensor_value0<line_threshold && left_sensor_value0 > line_threshold && right_sensor_value1 < line_threshold) {
    left();
  }
    else if (left_sensor_value1>line_threshold && right_sensor_value0>line_threshold && left_sensor_value0 < line_threshold && right_sensor_value1 > line_threshold) {
    right();
  }
  // Neither sensor over a line
  
 
  // Both sensors over a line
  else {
  ;
    }
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

void both(int option){  //what to do when both sensors hit line. each option is in the sequence of what is expected to happen
  if (option == 1){ //option 1: Coming out of my cage
    forwards();
  }
  else if (option == 2){ //option 2: line merge from base to arena
    forwards();
  }
  else if (option == 3){ //option 3: stop at end of track
    halt();
  }
  //break for program in arean (ie not following lines)
  else if (option == 4){ //option 4: returning from arena to track
    forwards();
  }
  else if (option == 5){ //option 5: line merge from arena to service area
    right();
  }
  else if (option == 6){ //option 6: enter service area
    halt();  //AND DROP ROBOT
  }
  else if (option == 7){ //option 7: 180 degree turn
    //180 DEGREEE TURN, IGNORE FOR NOW
  }
  else if (option == 8){ //option 8: line merge from service area to arena
    left();
  }
  //here, return to option 3 for next robot. if final robot, stop before option 5, and do option 9 instead
  else if (option == 9){ //option 9: line merge from arena to base
    left();
  }
  else if (option == 10){ //option 10: going back into my cage
    halt();
    //ADJUST SO COMES INTO BASE FULLY
  }
}

void increment_option(){
  if ((both_happening == 1) && ((millis() - prev_increment_time_0) >= min_increment_interval)){
      both_happening = 0;
      both_option += 1;
      prev_increment_time_0 = millis();
    }
}
