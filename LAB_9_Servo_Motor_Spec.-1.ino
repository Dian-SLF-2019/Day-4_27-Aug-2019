#include <Servo.h>
Servo myServo;
int angle = 0;

void setup() {
  Serial.begin(9600);
  myServo.attach(3);
}

void loop() {
  // move from 0 to 180 degrees
  static unsigned long tick = millis ();
  for(int i = 0; i < 10; i++)
  {
  for(angle = 0; angle < 180; angle++){
  {
    myServo.write(angle);
    delay(15);
 }
  
  //move in reverse direction, from 180 to 0 degrees
  for(angle = 180; angle > 0; angle--)
  {
    myServo.write(angle);
    delay(15);
  }
  }
  Serial.println(millis() - tick);
  }
}
