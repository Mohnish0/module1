
int pos = 0;
const int trigPin1 = 11;
const int echoPin1 = 12;

const int trigPin2 = 10;
const int echoPin2 = 8;

const int buttonPin1 = 2;

const int buttonPin2 = 3;

int distanceCm1, distanceInch1;
long duration1;
int distance1;

int distanceCm2, distanceInch2;
long duration2;
int distance2;


volatile bool curr_State = false;
volatile bool D7_state = LOW;

const int led_pin = PB5;

const uint16_t t1_load = 0;
const uint16_t t1_comp = 31250;

const byte motionSens2 = 7;

void setup()
{
  Serial.begin(9600);

  pinMode(trigPin1, OUTPUT); 
  pinMode(echoPin1, INPUT); 
  
  pinMode(trigPin2, OUTPUT); 
  pinMode(echoPin2, INPUT); 

  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);

  digitalWrite(trigPin1, LOW);
  digitalWrite(trigPin2, LOW);

    PCICR |= B00000100;
    // Enable PCINT18  & PCINT23 (Pins D2 & D7)
    PCMSK2 |= B10000000;

    // pinMode(LED_BUILTIN, OUTPUT);
    DDRB |= (1 << led_pin);

  attachInterrupt(digitalPinToInterrupt(buttonPin1), dist1, FALLING);
  attachInterrupt(digitalPinToInterrupt(buttonPin2), dist2, FALLING);

  
    TCCR1A = 0;

    // Clear on compare
    TCCR1B &= ~(1 << WGM13);
    TCCR1B |= (1 << WGM12);

    // set prescaler 1024
    TCCR1B |= (1 << CS12);
    TCCR1B &= ~(1 << CS11);
    TCCR1B |= (1 << CS10);

    // reset timer1 set and compare values
    TCNT1 = t1_load;
    OCR1A = t1_comp;

    // enable timer1 compare interrupt
    TIMSK1 = (1 << OCIE1A);

    // enabling global interrupts
    sei();

}

ISR(TIMER1_COMPA_vect)
{
    PORTB ^= (1 << led_pin);
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

ISR(PCINT2_vect)
{
    if (digitalRead(motionSens2) == LOW)
    {
        D7_state = !D7_state;
        digitalWrite(LED_BUILTIN, D7_state);
        Serial.println("Motion Interrupt 2");
    }
}

