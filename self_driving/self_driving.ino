bool on = false;
int UStrigPin = 2;
int USechoPin = 3;

void setup() {
  // put your setup code here, to run once:
  pinMode(UStrigPin, OUTPUT);
  Serial.begin(9600);
}

/*
 * Helper methods
 */

float ultrasonic_reading() {
  // get reading from ultrasonic device
  digitalWrite(UStrigPin, LOW);
  delay(1);
  digitalWrite(UStrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(UStrigPin, LOW);
  // calculate approximate distance
  long duration = pulseIn(USechoPin, HIGH);
  // Serial.print("Duration: ");
  // Serial.print(duration);
  
  // returns distance in centimeters (ish)
  return (duration / 2) / 29.1;
}

void loop() {
  // get state of on/off button
  
  
  // if state is "on", begin navigation
  while (on) {
    
  }
  
}
