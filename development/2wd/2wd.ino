// Motor C
int motor3Pin1 = 14; 
int motor3Pin2 = 27; 

// Motor D
int motor4Pin1 = 26; 
int motor4Pin2 = 25; 

void setup() {
  // put your setup code here, to run once:
  pinMode(motor3Pin1, OUTPUT);
  pinMode(motor3Pin2, OUTPUT);
  pinMode(motor4Pin1, OUTPUT);
  pinMode(motor4Pin2, OUTPUT);

  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Forward");
  digitalWrite(motor3Pin1, LOW);
  digitalWrite(motor3Pin2, HIGH); 
  digitalWrite(motor4Pin1, LOW);
  digitalWrite(motor4Pin2, HIGH);
  delay(2000);

  Serial.println("Backward");
  digitalWrite(motor3Pin1, HIGH);
  digitalWrite(motor3Pin2, LOW); 
  digitalWrite(motor4Pin1, HIGH);
  digitalWrite(motor4Pin2, LOW);
  delay(2000);

  Serial.println("Stop");
  digitalWrite(motor3Pin1, LOW);
  digitalWrite(motor3Pin2, LOW); 
  digitalWrite(motor4Pin1, LOW);
  digitalWrite(motor4Pin2, LOW);
  delay(2000);

  Serial.println("Left");
  digitalWrite(motor3Pin1, HIGH);
  digitalWrite(motor3Pin2, LOW); 
  digitalWrite(motor4Pin1, LOW);
  digitalWrite(motor4Pin2, HIGH);
  delay(2000);

  Serial.println("Right");
  digitalWrite(motor3Pin1, LOW);
  digitalWrite(motor3Pin2, HIGH); 
  digitalWrite(motor4Pin1, HIGH);
  digitalWrite(motor4Pin2, LOW);
  delay(2000);

  Serial.println("Stop");
  digitalWrite(motor3Pin1, LOW);
  digitalWrite(motor3Pin2, LOW); 
  digitalWrite(motor4Pin1, LOW);
  digitalWrite(motor4Pin2, LOW);
  delay(2000);
}
