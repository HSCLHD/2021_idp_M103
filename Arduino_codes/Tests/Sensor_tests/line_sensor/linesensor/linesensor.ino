#include <Wire.h>

#define left_sensor_pin0 A3
#define left_sensor_pin1 A2
#define right_sensor_pin0 A1
#define right_sensor_pin1 A0

int left_sensor_value0;      // Left line sensor value-  higher number => lighter
int left_sensor_value1;
int right_sensor_value0;     // Right line sensor value
int right_sensor_value1;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
// Read line sensors and output values
  left_sensor_value0  = analogRead(left_sensor_pin0);
  left_sensor_value1  = analogRead(left_sensor_pin1);
  right_sensor_value0 = analogRead(right_sensor_pin0);
  right_sensor_value1 = analogRead(right_sensor_pin1);
  Serial.print("1: ");
  Serial.println( left_sensor_value0);
    Serial.print("2: ");
  Serial.println(left_sensor_value1);
    Serial.print("3: ");
  Serial.println(right_sensor_value0);
    Serial.print("4: ");
  Serial.println(right_sensor_value1);
  delay(1000);

}
