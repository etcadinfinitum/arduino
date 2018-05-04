int trigPin = 2;
int echoPin = 3;
int red = 8;
int yellow = 9;
int green = 10;
int blue = 11;


void setup() {
  // put your setup code here, to run once:
  pinMode(trigPin, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  Serial.begin(9600);
}

void loop() {
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
  Serial.print("Distance: ");
  Serial.println(distance);
  
  delay(500);
}
