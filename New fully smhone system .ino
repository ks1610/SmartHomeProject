//    servo cửa 
#include <Servo.h> // Declare the Servo pin
Servo Servo1;
int servoPin1 = 13; //  servo phòng ngủ
Servo Servo2;
int servoPin2 = 10; //  servo phòng bếp
Servo Servo3;
int servoPin3 = 7;  //  servo cửa chính
Servo Servo4;
int servoPin4 = 22;  //  servo cổng vào


//    cảm biến độ ẩm & thời tiết DHT-11
#include <dht.h> 
dht DHT;       
#define outPin 8 // cảm biến độ ẩm trong phòng
int humidi = 0;
#define outPin1 5  // cảm biến thời tiết ngoài trời 
int temper = 0;                     

//    loa
const int speakerPin = 9; // Chân kết nối của loa

//  công tắc điều khiền quạt 
#define PIN_RELAY_2  2 // quạt bếp
#define PIN_RELAY_3  3 // quạt phòng khách
#define PIN_RELAY_4  4 // quạt phòng ngủ

//  công tắc điều khiển máy bơm
#define PIN_RELAY_13  11 // máy bơm vườn 
#define PIN_RELAY_14  12 // máy bơm nhà

//  cảm biến khí gas
#include<MQ2.h>
#define MQ2pin 0 // Define the "smoke detected" value.
#define smoke 400
float sensorValue; 

//  cảm biến chống lụt
int Moisture_signal = A1; //Define the Analog pin# on the Arduino for the soil moisture sensor signal
int water = 0;

void setup()
{
  
  // khai báo cảm biến lửa
  pinMode(0, INPUT); //initialize Flame sensor output pin connected pin as input.
  pinMode(LED_BUILTIN, OUTPUT);// initialize digital pin LED_BUILTIN as an output.
  
  Serial.begin(9600);// initialize serial communication @ 9600 baud:

  // khai báo servo
  Servo1.attach(servoPin1); 
  Servo2.attach(servoPin2);
  Servo3.attach(servoPin3);
  Servo3.attach(servoPin4);
  
  // khai báo loa
  pinMode(speakerPin, OUTPUT);

  // khai báo công tắc quạt
  pinMode(PIN_RELAY_2, OUTPUT);
  pinMode(PIN_RELAY_3, OUTPUT);
  pinMode(PIN_RELAY_4, OUTPUT);

  // khai báo công tắc máy bơm
  pinMode(PIN_RELAY_13, OUTPUT);
  pinMode(PIN_RELAY_14, OUTPUT);
}
void chonglut()
{
  int Moisture = analogRead(Moisture_signal);
  Serial.print("Soil Moisture Level: ");
  Serial.println(Moisture);
  delay(200);
  // condition for controlling water machine
  if(Moisture < 750)
  {
    water = 1;
  }
  else 
  {
    water = 0;
  }
}
void dhtnha()
{
 int readData = DHT.read11(outPin);
  float h = DHT.humidity;           // độ ẩm
  Serial.print("Humidity = ");
  Serial.print(h);
  Serial.println("% ");
  Serial.println("");
  // condition for controlling 3 Fans 
  if(h > 80)
  {
    humidi = 1;
  }
  else
  {
    humidi = 0;
  }
  delay(2000); 
}
void dhtvuon()
{
  int readData = DHT.read11(outPin1);

  float t = DHT.temperature;        // nhiệt độ
  //float h = DHT.humidity;           // độ ẩm

  Serial.print("Temperature = ");
  Serial.print(t);
  Serial.print("°C | ");
  Serial.println("");
  delay(2000);
  // condition for controlling water machine
  if(t > 40)
  {
    temper = 1;    
  }
  else
  {
    temper = 0;
  }
}
void phongkhach()
{
  if (digitalRead(0) == 0 ) // phát hiện lửa
  {
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("** Warning!!!!   Fire detected!!! **");
    digitalWrite(speakerPin, HIGH);
    delay(200);
    Servo1.write(180); // cửa sổ phòng ngủ mở
    Servo2.write(180); // cửa sổ phòng khách mở
    Servo3.write(90); // cửa chính mở
    Servo4.write(90); // cổng mở
    digitalWrite(PIN_RELAY_13, LOW); // máy bơm xả nước
    digitalWrite(PIN_RELAY_14, LOW);   
    }
  else // không phát hiện lửa, nhà an toàn
  {
    digitalWrite(LED_BUILTIN, LOW); 
    Serial.println("No Fire detected"); 
    digitalWrite(speakerPin, LOW);
    Servo1.write(0);
    Servo2.write(0);
    Servo3.write(0);
    Servo4.write(0);
    digitalWrite(PIN_RELAY_13, HIGH);
    digitalWrite(PIN_RELAY_14, HIGH);
    delay(1000); 
  }
  delay(1000);
}

void phongbep()
{
  float sensorValue = analogRead(MQ2pin); // Define & read analog values 
  Serial.println("Sensor Value: ");// Display the sensor values
  Serial.print(sensorValue);
  if(sensorValue > smoke) // phát hiện có khí gas
  {
    Serial.print(" | Smoke");
    delay(200);
    digitalWrite(speakerPin, HIGH);
    delay(500);
    Servo1.write(180); // cửa sổ phòng ngủ mở
    Servo2.write(180); // cửa sổ phòng bếp mở
    Servo3.write(90);  // cửa chính mở
    Servo4.write(90);  // cổng mở
    delay(200);
    digitalWrite(PIN_RELAY_2, LOW); // quạt phòng bếp mở 
    digitalWrite(PIN_RELAY_3, LOW); // quạt phòng khách mở
    digitalWrite(PIN_RELAY_4, LOW); // quạt phòng ngủ mở
    delay(200);
  } 
  else // không phát hiện nhà có khí gas, nhà an toàn 
  {
    digitalWrite(speakerPin, LOW);
    delay(500);
    Servo1.write(0);
    Servo2.write(0);
    Servo3.write(0);
    Servo4.write(0);
    delay(500);
    digitalWrite(PIN_RELAY_2, HIGH); 
    digitalWrite(PIN_RELAY_3, HIGH);
    digitalWrite(PIN_RELAY_4, HIGH);
    delay(500);
  }
  Serial.println("");
  delay(2000); 
}
void loop()
{
  dhtvuon();
  if(temper)
  {
    digitalWrite(PIN_RELAY_13, LOW); // máy bơm vườn mở
    delay(1000);
  }
  chonglut();
  if(water)
  {
    digitalWrite(PIN_RELAY_14, LOW); // máy bơm xả nước ra ngoài trong nhà mở
    digitalWrite(PIN_RELAY_13, LOW); // máy bơm xả nước ra ngoài ở vườn mở
    delay(2000);
  }
  dhtnha();
  if(humidi)
  {
    digitalWrite(PIN_RELAY_2, LOW); // bật quạt phòng ngủ
    digitalWrite(PIN_RELAY_3, LOW); // bật quạt phòng khách
    digitalWrite(PIN_RELAY_4, LOW); // bật quạt phòng bếp
    delay(2000);
  }
  phongkhach();
  phongbep();
}
