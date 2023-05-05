#include <Servo.h>

Servo myservo;

const int fan = 8;
const int photo1 = A0;
const int photo2 = A1;
const int photo3 = A2;
const int photo4 = A3;
int Button = 9;
int threshold = 900;
int flag = 0;

void setup() {
pinMode(fan,OUTPUT);

pinMode(photo1, INPUT);
pinMode(photo2, INPUT);
pinMode(photo3, INPUT);
pinMode(photo4, INPUT);

pinMode(Button, INPUT);

myservo.attach(3);

Serial.begin(9600);
}

void loop() {
myservo.write(146);

if (digitalRead(Button) == HIGH) {
  flag = 1;
  delay(200);
}
int count = 0;
if (flag == 1) {
    for (int i = 145; i > 40; i += -1) {
    myservo.write(i);
    delay(20);
  }
  delay(1000);
  int count = 0;
  Serial.print("1: ");
  Serial.println(analogRead(photo1));
  if (analogRead(photo1) > threshold) {
    count++;
    Serial.print("1: ");
    Serial.println(analogRead(photo1));

  }
  if (analogRead(photo2) > threshold) {
    count++;
    Serial.print("2: ");
    Serial.println(analogRead(photo2));
  }
  if (analogRead(photo3) > threshold) {
    count++;
    Serial.print("3: ");
    Serial.println(analogRead(photo3));
  }
  if (analogRead(photo4) > threshold) {
    count++;
    Serial.print("4: ");
    Serial.println(analogRead(photo4));
  }
  flag = 0;
  Serial.println(count);
  delay(100);
  digitalWrite(fan, HIGH);
  delay(1000);
  digitalWrite(fan, LOW);
  for (int i = 40; i < 146; i++) {
    myservo.write(i);
    delay(20);
  }
}
}
