// # Editor     : roker
// # Date       : 18.02.2019

// # Product name: URM09 Ultrasonic Sensor(Gravity Analog)(V1.0)
// # Product SKU : SEN0307
// # Version     : 1.0


#define  MAX_RANG      (520)//the max measurement vaule of the module is 520cm(a little bit longer than  effective max range)
#define  ADC_SOLUTION      (1023.0)//ADC accuracy of Arduino UNO is 10bit

int sensityPin = A4;    // select the input pin 
int vibration = 9;
void setup() {
  // Serial init
  Serial.begin(9600);
  pinMode(vibration, OUTPUT);
}
float distance, sensity_t;
void loop() {
  // read the value from the sensor:
  sensity_t = analogRead(sensityPin);
  // turn the ledPin on
  distance = sensity_t * MAX_RANG  / ADC_SOLUTION;//

  if (distance < 200)
  {
    digitalWrite(vibration, LOW);
    delay(100);
    digitalWrite(vibration, HIGH);
    delay(distance * 10);
  }

  Serial.print(distance,0);
  Serial.println("cm");
}