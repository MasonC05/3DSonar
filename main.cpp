#include <Arduino.h>
#include <Servo.h>
// put function declarations here:
// int myFunction(int, int);
Servo Servo1;
Servo Servo2;

long duration;
int distance;

const int trigPin = A4;
const int echoPin = A5;

void calculateDistance(){
  distance = 0;
  int validSamples = 0;
  for (int i = 0; i < 3; i++){
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH, 30000);
    
    if (duration > 0) {
      distance += duration * .034 / 2;
      validSamples++;
    }

    delay(5);
  }
  distance = (validSamples > 0) ? distance / validSamples : -1;
}

// void calculateDistance(){
//   digitalWrite(trigPin, LOW);
//   delayMicroseconds(2);

//   digitalWrite(trigPin, HIGH);
//   delayMicroseconds(5);
//   digitalWrite(trigPin, LOW);

//   duration = pulseIn(echoPin, HIGH, 30000);
  
//   distance += duration * .034 / 2;
// }

void setup() {
  // put your setup code here, to run once:
  Servo1.attach(9);
  Servo2.attach(8);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(115200);
}

void loop() {
  for (int i = 15; i <= 165; i+= 10){
    Servo2.write(i);
    for (int j = 15; j <= 165; j += 10){
      Servo1.write(j);
      delay(100);
      calculateDistance();
      Serial.print(i);
      Serial.print(",");
      Serial.print(j);
      Serial.print(",");
      Serial.println(distance);
    }
    i += 10;
    Servo2.write(i);
    delay(10);

    for (int j = 165; j > 15; j -= 10){
      Servo1.write(j);
      delay(100);
      calculateDistance();

      Serial.print(i);
      Serial.print(",");
      Serial.print(j);
      Serial.print(",");
      Serial.println(distance);
    }

  }
}

