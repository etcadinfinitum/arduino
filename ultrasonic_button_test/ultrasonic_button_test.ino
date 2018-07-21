int trigPin = 2;
int echoPin = 3;
int red = 8;
int yellow = 9;
int green = 10;
int blue = 11;
int btn = 12;
bool on = false;
int val = 0;

void setup() {
  // initialize pin modes and begin I/O
  pinMode(trigPin, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(btn, INPUT);
  Serial.begin(9600);
}

void loop() {
  val = digitalRead(btn);
  if (val == HIGH) {
    if (on == true) {
      // reset lights
      digitalWrite(red, LOW);
      digitalWrite(yellow, LOW);
      digitalWrite(green, LOW);
      digitalWrite(blue, LOW);
      on = false;
    } else {
      on = true;
    }
  }

  // this will only run if display is set to "on"
  if (on) {
    // get reading from ultrasonic device
    digitalWrite(trigPin, LOW);
    delay(1);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    // calculate approximate distance
    long duration = pulseIn(echoPin, HIGH);
    Serial.print("Duration: ");
    Serial.print(duration);
    long distance = (duration / 2) / 29.1;
  
    // reset lights
    digitalWrite(red, LOW);
    digitalWrite(yellow, LOW);
    digitalWrite(green, LOW);
    digitalWrite(blue, LOW);
  
    // trigger lights 
    if (distance < 10) {
      digitalWrite(red, HIGH);
    } else if (distance < 20) {
      digitalWrite(yellow, HIGH);
    } else if (distance < 40) {
      digitalWrite(green, HIGH);
    } else {
      digitalWrite(blue, HIGH);
    }
  }
  
  delay(500);
}
