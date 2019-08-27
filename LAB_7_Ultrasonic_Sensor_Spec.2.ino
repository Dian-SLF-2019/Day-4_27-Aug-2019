#define trigPin 13
#define echoPin 12
//#define BUZZER 6
#define redPin 5
#define greenPin 9
#define bluePin 10

void setup() {
  Serial.begin (9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  long duration, distance;
//(1) : generate ultrasonic waveform
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 17 / 1000;

  set_color(distance, 255,255);
  Serial.println(distance);
  delay(1000);
}

void set_color(int red, int green, int blue)
{
  analogWrite(redPin, red*10);
  analogWrite(greenPin, 255);
  analogWrite(bluePin, 255);
}
