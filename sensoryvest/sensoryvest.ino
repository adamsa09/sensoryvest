#define MAX_RANG (520)
#define ADC_SOLUTION (1023.0)

// Define the pins for the sensors. SEN0307 are analog pins
int frontTop = A0;
int frontBottom = A1;
int trigRight = 1;
int echoRight = 2;
int trigLeft = 3;
int echoLeft = 4;
int backTop = A2;
int backBottom = A3;

// Define the pins, the timers and the states for the vibrators
int vibrationFront = 6;
bool vibrationFrontOn = false;
unsigned long buzzStartTimeFront = 0;

int vibrationRight = 7;
bool vibrationRightOn = false;
unsigned long buzzStartTimeRight = 0;

int vibrationLeft = 8;
bool vibrationLeftOn = false;
unsigned long buzzStartTimeLeft = 0;

int vibrationBack = 9;
bool vibrationBackOn = false;
unsigned long buzzStartTimeBack = 0;

// Define the previous time that a vibration was made
unsigned long previousTimeFront = 0;
unsigned long previousTimeRight = 0;
unsigned long previousTimeLeft = 0;
unsigned long previousTimeBack = 0;

void setup()
{
  Serial.begin(9600); // Start serial serial com. on 9600
  // Define the modes for the pins defined above
  pinMode(vibrationFront, OUTPUT);
  pinMode(vibrationRight, OUTPUT);
  pinMode(vibrationLeft, OUTPUT);
  pinMode(vibrationBack, OUTPUT);

  pinMode(trigRight, OUTPUT);
  pinMode(echoRight, INPUT);

  pinMode(trigLeft, OUTPUT);
  pinMode(echoLeft, INPUT);
}

// Define the variables for the data received from the sensors and for the calculations of distance
float sensityFrontTop_t, sensityFrontBottom_t, sensityBackTop_t, sensityBackBottom_t;
long sensityRight, sensityLeft;
float distanceFrontTop, distanceFrontBottom, distanceRight, distanceLeft, distanceBackTop, distanceBackBottom;

void loop()
{
  // For hc-sr04, emit ultrasonic waves
  digitalWrite(trigRight, LOW);
  delayMicroseconds(5);
  digitalWrite(trigRight, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigRight, LOW);

  digitalWrite(trigLeft, LOW);
  delayMicroseconds(5);
  digitalWrite(trigLeft, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigLeft, LOW);

  // Read the values from each sensor
  sensityFrontTop_t = analogRead(frontTop);
  sensityFrontBottom_t = analogRead(frontBottom);
  sensityRight = pulseIn(echoRight, HIGH);
  sensityLeft = pulseIn(echoLeft, HIGH);
  sensityBackTop_t = analogRead(backTop);
  sensityBackBottom_t = analogRead(backBottom);

  // Calculate the distances based on the values from each sensor
  distanceFrontTop = sensityFrontTop_t * MAX_RANG / ADC_SOLUTION;
  distanceFrontBottom = sensityFrontBottom_t * MAX_RANG / ADC_SOLUTION;
  distanceRight = (sensityRight / 2) * 0.0343;
  distanceLeft = (sensityLeft / 2) * 0.0343;
  distanceBackTop = sensityBackTop_t * MAX_RANG / ADC_SOLUTION;
  distanceBackBottom = sensityBackBottom_t * MAX_RANG / ADC_SOLUTION;

  // Define the current time and create the variable for the later-defined interval between buzzes.
  unsigned long currentTime = millis();
  unsigned long intervalFront;
  unsigned long intervalRight;
  unsigned long intervalLeft;
  unsigned long intervalBack;

  if (distanceFrontTop < 200 || distanceFrontBottom < 200)
  {
    // Turnary operation to set intervalFront to the distance that is below 200. If they are both below 200, choose the lower value
    intervalFront = distanceFrontTop < distanceFrontBottom && distanceFrontTop < 200 ? 10 * distanceFrontTop : 10 * distanceFrontBottom;
    // If the interval time is up, vibrate again
    if (currentTime - previousTimeFront >= intervalFront)
    {
      // If the vibrator is not on, turn it on and set the start time of the vibration
      if (!vibrationFrontOn)
      {
        digitalWrite(vibrationFront, LOW);
        buzzStartTimeFront = millis();
        vibrationFrontOn = true;
      }
      // If the vibrator is on, make sure the 100ms is elapsed and turn it off.
      else if (vibrationFrontOn && millis() - buzzStartTimeFront >= 100)
      {
        digitalWrite(vibrationFront, HIGH);
        vibrationFrontOn = false;
      }
      // Set the previous time to the current time
      // That is such a bad comment oh my
      previousTimeFront = currentTime;
    }
  }

  if (distanceRight < 200)
  {
    intervalLeft = 10 * distanceRight;
    if (currentTime - previousTimeRight >= intervalRight)
    {
      if (!vibrationRightOn)
      {
        digitalWrite(vibrationRight, LOW);
        buzzStartTimeRight = millis();
        vibrationRightOn = true;
      }
      else if (vibrationRightOn && millis() - buzzStartTimeRight >= 100)
      {
        digitalWrite(vibrationRight, HIGH);
        vibrationRightOn = false;
      }
      previousTimeRight = currentTime;
    }
  }

  if (distanceLeft < 200)
  {
    intervalLeft = 10 * distanceLeft;
    if (currentTime - previousTimeLeft >= intervalLeft)
    {
      if (!vibrationLeftOn)
      {
        digitalWrite(vibrationLeft, LOW);
        buzzStartTimeLeft = millis();
        vibrationLeftOn = true;
      }
      else if (vibrationLeftOn && millis() - buzzStartTimeLeft >= 100)
      {
        digitalWrite(vibrationLeft, HIGH);
        vibrationLeftOn = false;
      }
      previousTimeLeft = currentTime;
    }
  }

  // Same as above, but for the back sensors
  if (distanceBackTop < 200 || distanceBackBottom < 200)
  {
    intervalBack = distanceBackTop < distanceBackBottom && distanceBackTop < 200 ? 10 * distanceBackTop : 10 * distanceBackBottom;
    if (currentTime - previousTimeBack >= intervalBack)
    {
      if (!vibrationBackOn)
      {
        digitalWrite(vibrationBack, LOW);
        buzzStartTimeBack = millis();
        vibrationBackOn = true;
      }
      else if (vibrationBackOn && millis() - buzzStartTimeBack > 100)
      {
        digitalWrite(vibrationBack, HIGH);
        vibrationBackOn = false;
      }
      previousTimeBack = currentTime;
    }
  }
}