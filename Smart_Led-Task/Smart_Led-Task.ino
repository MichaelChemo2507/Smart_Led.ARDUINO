#define trigPin 11
#define echoPin 12
#define LED 4
#define LED_ON 20
#define LED_OFF 21

unsigned long lastTimePass , lastTimeOn;

long duration;
int distance, currVal;
void setup() {
  pinMode(LED, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  lastTimePass = millis();
  currVal = LED_OFF;
  Serial.begin(9600);
}

float lenMicroSec = (2000 * 2) / 0.034;
void loop() {
  
  send_trig();
  duration = pulseIn(echoPin, HIGH, lenMicroSec);
  distance = (duration * 0.034) / 2;

  
  if ((distance <= 50 && distance >= 20) && (millis() - lastTimePass) >= 500) {
  Serial.println(distance);
    lastTimePass = millis();
    switch (currVal) {
      case LED_OFF:
        digitalWrite(LED, HIGH);
        currVal = LED_ON;
        break;
      case LED_ON:
      lastTimeOn = millis();
        currVal = LED_OFF;
        break;
    }
  }
  if (currVal == LED_OFF && (millis() - lastTimeOn) >= 2000) {
          digitalWrite(LED, LOW);
  }
}
  void send_trig() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
  }