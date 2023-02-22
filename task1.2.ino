#include <Servo.h>
int pos = 0;
const int trigPin = 11;
const int echoPin = 12;
Servo servo_9;

const int buttonPin = 2;

int distanceCm, distanceInch;
long duration;
int distance;

void setup()
{
  Serial.begin(9600);
    servo_9.attach(9, 0, 0);

  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  pinMode(buttonPin, INPUT);
  digitalWrite(trigPin, LOW);
  attachInterrupt(digitalPinToInterrupt(buttonPin), dist, FALLING);
}

void loop()
{
}

void dist(){
 // Clears the trigPin
 digitalWrite(trigPin, LOW);
 delayMicroseconds(2);
 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10);
 digitalWrite(trigPin, LOW);
 duration = pulseIn(echoPin, HIGH);
 distanceCm = duration * 0.034 / 2;
 delay(10);
 Serial.println(distanceCm);
    move_m();
}

void move_m()
{

  if(distanceCm < 100)
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
  if(distanceCm > 100)
  {
    servo_9.write(0);
  }
}