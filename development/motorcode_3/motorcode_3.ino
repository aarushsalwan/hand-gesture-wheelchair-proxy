// Motor A
int motor3Pin1 = 27; 
int motor3Pin2 = 26; 
int enable1Pin = 14; 

// Motor B
int motor4Pin1 = 33; 
int motor4Pin2 = 32; 
int enable2Pin = 35; 

// Setting PWM properties
const int freq = 30000;
const int pwmChannel = 0;
const int resolution = 8;
int dutyCycle = 200;

void setup() {
  // sets the pins as outputs:
  pinMode(motor3Pin1, OUTPUT);
  pinMode(motor3Pin2, OUTPUT);
  pinMode(enable1Pin, OUTPUT);

  pinMode(motor4Pin1, OUTPUT);
  pinMode(motor4Pin2, OUTPUT);
  pinMode(enable2Pin, OUTPUT);
  
  // configure LED PWM functionalitites
  //ledcSetup(pwmChannel, freq, resolution);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachChannel(enable1Pin, freq, resolution, pwmChannel);
  ledcAttachChannel(enable2Pin, freq, resolution, pwmChannel);
  Serial.begin(115200);
  // testing
  Serial.print("Testing DC Motor...");
}

void loop() {
  // Move the DC motor forward at maximum speed
  Serial.println("Moving Forward");
  digitalWrite(motor3Pin1, LOW);
  digitalWrite(motor3Pin2, HIGH); 
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
  
  // Move DC motor backwards at maximum speed
  Serial.println("Moving Backwards");
  digitalWrite(motor3Pin1, HIGH);
  digitalWrite(motor3Pin2, LOW);
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
  
  // Move DC motor forward with increasing speed
  digitalWrite(motor3Pin1, HIGH);
  digitalWrite(motor3Pin2, HIGH);
  digitalWrite(motor4Pin1, HIGH);
  digitalWrite(motor4Pin2, HIGH);
  
  while (dutyCycle <= 255){
    ledcWrite(pwmChannel, dutyCycle);   
    Serial.print("Forward with duty cycle: ");
    Serial.println(dutyCycle);
    dutyCycle = dutyCycle + 5;
    delay(500);
  }
  dutyCycle = 200;
}