const int trig = 7;
const int echo = 8;
const int vibration_buzzer = 9;
long duration;
int distance;

void setup() {
  // put your setup code here, to run once:
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(trig, LOW);
  delayMicroseconds(5);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  duration = pulseIn(echo, HIGH);

  distance = (duration / 2) * 0.0343;

  digitalWrite(vibration_buzzer, LOW);
  delayMicroseconds(10);
  digitalWrite(vibration_buzzer, HIGH);
  delay(distance/5*distance);

  Serial.print(distance);
  Serial.print("cm\n");
}

