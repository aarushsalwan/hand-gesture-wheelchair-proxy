int motor1Pin1 = 33; 
int motor1Pin2 = 32; 

// Motor B
int motor2Pin1 = 18; 
int motor2Pin2 = 19; 

// Motor C
int motor3Pin1 = 14; 
int motor3Pin2 = 27; 

// Motor D
int motor4Pin1 = 26; 
int motor4Pin2 = 25; 

void setup() {
  // put your setup code here, to run once:
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);

  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);

  pinMode(motor3Pin1, OUTPUT);
  pinMode(motor3Pin2, OUTPUT);

  pinMode(motor4Pin1, OUTPUT);
  pinMode(motor4Pin2, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
  digitalWrite(motor3Pin1, HIGH);
  digitalWrite(motor3Pin2, LOW);
  digitalWrite(motor4Pin1, HIGH);
  digitalWrite(motor4Pin2, LOW);
}
