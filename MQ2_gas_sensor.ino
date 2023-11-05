// Khai báo chân kết nối của cảm biến và đèn LED
#include <Servo.h> 
const int gasSensor = A0;
int servoPin = 12; // Create a servo object
Servo Servo1;
// Khởi tạo biến
int gasValue;

void setup() {
  
  // Bắt đầu Serial Monitor
  Serial.begin(9600);
}

void loop() {
  // Đọc giá trị từ cảm biến
  gasValue = analogRead(gasSensor);

  // In giá trị đọc được lên Serial Monitor
  Serial.print("Gas value: ");
  Serial.println(gasValue);

  // Nếu giá trị vượt ngưỡng quy định, bật đèn LED
  if (gasValue > 300) {
    Servo1.write(180); 
    delay(100);
  } else {
    Servo1.write(0); 
    delay(100);
  }

  // Chờ 1 giây trước khi lặp lại
  delay(1000);
}
