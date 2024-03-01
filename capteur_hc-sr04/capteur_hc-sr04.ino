const int trig = 3;
const int echo = 4;
const int vibration_buzzer = 8;
long duration;
int distance;
bool isBuzzing = false;
unsigned long buzzStartTime = 0;

unsigned long previousTime = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(vibration_buzzer, OUTPUT);
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

  unsigned long currentTime = millis();
  unsigned long interval = 10*distance;

  if (distance < 200)
  {
    if (currentTime - previousTime >= interval)
    {
      if (!isBuzzing)
      {
        digitalWrite(vibration_buzzer, LOW);
        buzzStartTime = millis();
        isBuzzing = true;
      }
      else if (isBuzzing && millis() - buzzStartTime > 100)
      {
        digitalWrite(vibration_buzzer, HIGH);
        isBuzzing = false;
      }
      previousTime = currentTime;
    }
  }

  Serial.print(distance);
  Serial.print("cm\n");

  
}


