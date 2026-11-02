// Motor A
int motor3Pin1 = 14; 
int motor3Pin2 = 27; 

// Motor B
int motor4Pin1 = 26; 
int motor4Pin2 = 25; 

void setup() {
  // sets the pins as outputs:
  pinMode(motor3Pin1, OUTPUT);
  pinMode(motor3Pin2, OUTPUT);

  pinMode(motor4Pin1, OUTPUT);
  pinMode(motor4Pin2, OUTPUT);

  Serial.begin(115200);
  // testing
  Serial.print("Testing DC Motor...");
}

void loop() {
  // Move the DC motor forward at maximum speed
  Serial.println("Moving Forward");
  digitalWrite(motor3Pin1, LOW);
  digitalWrite(motor3Pin2, HIGH); 
  digitalWrite(motor4Pin1, HIGH);
  digitalWrite(motor4Pin2, LOW); 
  delay(2000);
  
  // Stop the DC motor
  Serial.println("Motor stopped");
  digitalWrite(motor3Pin1, LOW);
  digitalWrite(motor3Pin2, LOW);
  digitalWrite(motor4Pin1, LOW);
  digitalWrite(motor4Pin2, LOW);
  delay(1000);
  
  // Move DC motor backwards at maximum speed
  Serial.println("Moving Backwards");
  digitalWrite(motor3Pin1, HIGH);
  digitalWrite(motor3Pin2, LOW);
  digitalWrite(motor4Pin1, LOW);
  digitalWrite(motor4Pin2, HIGH); 
  delay(2000);
  
  // Stop the DC motor
  Serial.println("Motor stopped");
  digitalWrite(motor3Pin1, LOW);
  digitalWrite(motor3Pin2, LOW);
  digitalWrite(motor4Pin1, LOW);
  digitalWrite(motor4Pin2, LOW);
  delay(1000);
  
}