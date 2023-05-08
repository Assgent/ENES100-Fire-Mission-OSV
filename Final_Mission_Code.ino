#include <Servo.h>

Servo myservo;

const int photo1 = A0;
const int photo2 = A1;
const int photo3 = A2;
const int photo4 = A3;
int threshold = 900;

void setup() {
pinMode(photo1, INPUT);
pinMode(photo2, INPUT);
pinMode(photo3, INPUT);
pinMode(photo4, INPUT);

myservo.attach(A5);
Serial.begin(9600);
}

void loop() {
myservo.write(146);
int count = 0;
    for (int i = 145; i > 40; i += -1) {
    myservo.write(i);
    delay(20);
  }
  if (analogRead(photo1) > threshold) {
    count++;
  }
  if (analogRead(photo2) > threshold) {
    count++;
  }
  if (analogRead(photo3) > threshold) {
    count++;
  }
  if (analogRead(photo4) > threshold) {
    count++;
  }
  Serial.println(count);
  delay(10000);
  for (int i = 40; i < 146; i++) {
    myservo.write(i);
    delay(20);
  }
}
