int LEDpin = 13;
int obstaclePin = 10;
int hasObstacle = LOW;  // LOW MEANS NO OBSTACLE

void setup() {
  pinMode(LEDpin, OUTPUT);
  pinMode(obstaclePin, INPUT); 
  pinMode(5,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  hasObstacle = digitalRead(obstaclePin);

  if (hasObstacle == LOW) {
    Serial.println("Stop something is ahead!!");
    digitalWrite(LEDpin, LOW);
  }
  else {
    Serial.println("Path is clear");
    digitalWrite(LEDpin, HIGH);
  }
  delay(200);{
  if (hasObstacle==LOW)
  digitalWrite(5,HIGH);
  else {
     
  digitalWrite(5,LOW);
  }
  }
}
