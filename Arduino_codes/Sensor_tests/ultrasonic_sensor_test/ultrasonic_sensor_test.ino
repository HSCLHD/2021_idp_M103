// Ultrasonic Sensor testing code. Written by a 13 year old.
#include <NewPing.h> // Imports the NewPing Library.
int ledPin = 13; // Add the onboard LED on pin 13.
int trigPin = 10; // Add the Trig pin on pin 10.
int echoPin = 9; // Add the ECHO pin on pin 9.
int duration, distance; // Add types 'duration' and 'distance'.

void setup()
{

pinMode (ledPin, OUTPUT); // The LED must be controlled by Arduino, it means it is an output type.
pinMode (trigPin, OUTPUT);// Same as above, the TRIG pin will send the ultrasonic wave.
pinMode (echoPin, INPUT); // The ECHO pin will recieve the rebounded wave, so it must be an input type.

}

void loop()
{

digitalWrite (ledPin, LOW); // Here, LOW means off and HIGH means on.
digitalWrite (trigPin, HIGH);
delay(50);
digitalWrite (trigPin, LOW);
duration=pulseIn(echoPin,HIGH);
distance=(duration/2)/29.1;

if(distance <=30) // If the sensor detects an obstacle less than 30 cm in distance, the LED will start to blink.
  digitalWrite (ledPin, HIGH);
  delay(50);
if(distance >=30)// If no obstacle is there within 30 cm, the Led should turn off.
  digitalWrite (ledPin, LOW);
  delay(50);

Serial.print("cm");
Serial.println(distance);
}
