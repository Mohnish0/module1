#include <Servo.h>
int pos = 0;
const int trigPin1 = 11;
const int echoPin1 = 12;

const int trigPin2 = 10;
const int echoPin2 = 8;
Servo servo_9;

const int buttonPin1 = 2;

const int buttonPin2 = 3;

int distanceCm1, distanceInch1;
long duration1;
int distance1;

int distanceCm2, distanceInch2;
long duration2;
int distance2;

void setup()
{
  Serial.begin(9600);
    servo_9.attach(9, 0, 0);

  pinMode(trigPin1, OUTPUT); 
  pinMode(echoPin1, INPUT); 
  
  pinMode(trigPin2, OUTPUT); 
  pinMode(echoPin2, INPUT); 

  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);

  digitalWrite(trigPin1, LOW);
  digitalWrite(trigPin2, LOW);

  attachInterrupt(digitalPinToInterrupt(buttonPin1), dist1, FALLING);
  attachInterrupt(digitalPinToInterrupt(buttonPin2), dist2, FALLING);
}

void loop()
{
}

void dist1(){
 // Clears the trigPin
 digitalWrite(trigPin1, LOW);
 delayMicroseconds(2);
 digitalWrite(trigPin1, HIGH);
 delayMicroseconds(10);
 digitalWrite(trigPin1, LOW);
 duration1 = pulseIn(echoPin1, HIGH);
 distanceCm1 = duration1 * 0.034 / 2;
 delay(10);
 Serial.print("Diatance for sensor 1: ");
 Serial.println(distanceCm1);

}

void dist2(){
 // Clears the trigPin
 digitalWrite(trigPin2, LOW);
 delayMicroseconds(2);
 digitalWrite(trigPin2, HIGH);
 delayMicroseconds(10);
 digitalWrite(trigPin2, LOW);
 duration2 = pulseIn(echoPin2, HIGH);
 distanceCm2 = duration2 * 0.034 / 2;
 delay(10);
 Serial.print("Diatance for sensor 2: ");
 Serial.println(distanceCm2);

}
