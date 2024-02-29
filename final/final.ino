#define MAX_RANG (520)        // the max measurement vaule of the module is 520cm(a little bit longer than  effective max range)
#define ADC_SOLUTION (1023.0) // ADC accuracy of Arduino UNO is 10bit

const int trigRight = 1;
const int echoRight = 2;
const int trigLeft = 3;
const int echoLeft = 4;
const int sensorFrontTop = A0;
const int sensorFrontBottom = A1;
const int sensorBackTop = A2;
const int sensorBackBottom = A3;

const int vibrationFront = 6;
const int vibrationRight = 7;
const int vibrationLeft = 8;
const int vibrationBack = 9;

long durationRight;
long durationLeft;
float sensityFrontTop;
float sensityFrontBottom;
float sensityBackTop;
float sensityBackBottom;

int distanceRight;
int distanceLeft;
float distanceFrontTop;
float distanceFrontBottom;
float distanceBackTop;
float distanceBackBottom;

unsigned long previousTimeFront = 0;
unsigned long previousTimeRight = 0;
unsigned long previousTimeLeft = 0;
unsigned long previousTimeBack = 0;

void setup()
{
    // Set the modes of the pins connected to HC-SR04 sensors
    pinMode(trigRight, OUTPUT);
    pinMode(echoRight, INPUT);
    pinMode(trigLeft, OUTPUT);
    pinMode(echoLeft, INPUT);
    // Set the modes of the pins connected to vibration motors
    pinMode(vibrationFront, OUTPUT);
    pinMode(vibrationRight, OUTPUT);
    pinMode(vibrationLeft, OUTPUT);
    pinMode(vibrationBack, OUTPUT);

    Serial.begin(9600);
}

void loop()
{
    // put your main code here, to run repeatedly:
    unsigned long currentTime = millis();
    unsigned long interval;

    // Distance on the right
    digitalWrite(trigRight, LOW);
    delayMicroseconds(5);
    digitalWrite(trigRight, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigRight, LOW);
    durationRight = pulseIn(echoRight, HIGH);
    distanceRight = (durationRight / 2) * 0.0343;

    // Distance on the left
    digitalWrite(trigLeft, LOW);
    delayMicroseconds(5);
    digitalWrite(trigLeft, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigLeft, LOW);
    durationLeft = pulseIn(echoLeft, HIGH);
    distanceLeft = (durationLeft / 2) * 0.0343;

    // Distance on the front & back
    sensityFrontTop = analogRead(sensorFrontTop);
    distanceFrontTop = sensityFrontTop * MAX_RANG / ADC_SOLUTION;

    sensityFrontBottom = analogRead(sensorFrontBottom);
    distanceFrontBottom = sensityFrontBottom * MAX_RANG / ADC_SOLUTION;

    sensityBackTop = analogRead(sensorBackTop);
    distanceFrontTop = sensityBackTop * MAX_RANG / ADC_SOLUTION;

    sensityBackBottom = analogRead(sensorBackBottom);
    distanceFrontBottom = sensityBackBottom * MAX_RANG / ADC_SOLUTION;

    // Vibration motors
    // Front
    if (distanceFrontTop < 200 || distanceFrontBottom < 200)
    {
        interval = distanceFrontTop < 200 ? distanceFrontTop * 10 : distanceFrontBottom * 10;
        if (currentTime - previousTimeFront >= interval)
        {
            digitalWrite(vibrationFront, LOW);
            delay(100);
            digitalWrite(vibrationFront, HIGH);
            previousTimeFront = currentTime;
        }
    }

    if (distanceRight < 200)
    {
        interval = distanceRight * 10;
        if (currentTime - previousTimeRight >= interval)
        {
            digitalWrite(vibrationRight, LOW);
            delay(100);
            digitalWrite(vibrationRight, HIGH);
            previousTimeRight = currentTime;
        }
    }

    if (distanceLeft < 200)
    {
        interval = distanceRight * 10;
        if (currentTime - previousTimeLeft >= interval)
        {
            digitalWrite(vibrationRight, LOW);
            delay(100);
            digitalWrite(vibrationRight, HIGH);
            previousTimeBack = currentTime;
        }
    }

    if (distanceBackTop < 200 || distanceBackBottom < 200)
    {
        interval = distanceBackTop < 200 ? distanceBackTop * 10 : distanceBackBottom * 10;
        if (currentTime - previousTimeBack >= interval)
        {
            digitalWrite(vibrationBack, LOW);
            delay(100);
            digitalWrite(vibrationBack, HIGH);
            previousTimeBack = currentTime;
        }
    }
}