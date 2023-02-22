#include <Servo.h>

int pos = 0;

const int trigPin = 11;
const int echoPin = 12;

Servo servo_9;

long duration;
int distance;

void setup()
{
  servo_9.attach(9, 500, 2500);
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  digitalWrite(trigPin, LOW);
  Serial.begin(9600); 
}

void loop()
{
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);
  
  if(distance < 100)
  {
    for (pos = 0; pos <= 180; pos += 1) {
    	// tell servo to go to position in variable 'pos'
    	servo_9.write(pos);
    	// wait 15 ms for servo to reach the position
    	delay(15); // Wait for 15 millisecond(s)
 	}
  	for (pos = 180; pos >= 0; pos -= 1) {
    	// tell servo to go to position in variable 'pos'
    	servo_9.write(pos);
    	// wait 15 ms for servo to reach the position
    	delay(15); // Wait for 15 millisecond(s)
 	}
  }
  if(distance > 100)
  {
    servo_9.write(0);
  }
}