#include <Servo.h> 
// Declare the Servo pin 
int servoPin = 13; 
// Create a servo object
const int speakerPin = 9; // Chân kết nối của loa
#define PIN_RELAY_1  1 // the Arduino pin, which connects to the IN1 pin of relay module
#define PIN_RELAY_2  2 // the Arduino pin, which connects to the IN2 pin of relay module
#define PIN_RELAY_3  3 // the Arduino pin, which connects to the IN3 pin of relay module
#define PIN_RELAY_4  4 // the Arduino pin, which connects to the IN4 pin of relay module

Servo Servo1; 

void setup()
{
  pinMode(0, INPUT); //initialize Flame sensor output pin connected pin as input.
  pinMode(LED_BUILTIN, OUTPUT);// initialize digital pin LED_BUILTIN as an output.
  Serial.begin(9600);// initialize serial communication @ 9600 baud:
  Servo1.attach(servoPin); 
  pinMode(speakerPin, OUTPUT);
  pinMode(PIN_RELAY_1, OUTPUT);
  pinMode(PIN_RELAY_2, OUTPUT);
  pinMode(PIN_RELAY_3, OUTPUT);
  pinMode(PIN_RELAY_4, OUTPUT);
}
void loop()
{
  if (digitalRead(0) == 0 )
  {
    digitalWrite(LED_BUILTIN, HIGH); // Led off
    Serial.println("** Warning!!!!   Fire detected!!! **");
    digitalWrite(speakerPin, HIGH);
    delay(100);
    Servo1.write(180); 
    delay(100);
    digitalWrite(PIN_RELAY_1, LOW);
    digitalWrite(PIN_RELAY_2, LOW); 
    digitalWrite(PIN_RELAY_3, LOW);
    digitalWrite(PIN_RELAY_4, LOW);   
    }
  else
  {
    digitalWrite(LED_BUILTIN, LOW); // Led on
    Serial.println("No Fire detected"); 
    digitalWrite(speakerPin, LOW);
    Servo1.write(0);
    delay(100);
    digitalWrite(PIN_RELAY_1, HIGH);
    digitalWrite(PIN_RELAY_2, HIGH);
    digitalWrite(PIN_RELAY_3, HIGH);
    digitalWrite(PIN_RELAY_4, HIGH);
    delay(1000); 
  }
  delay(1000);
}
