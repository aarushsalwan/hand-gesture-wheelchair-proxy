//Set Motor PINs
// Motor A
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

//Initialize global variables
bool front = 0;
bool back = 0;
bool left = 0;
bool right = 0;

//Struct to recieve data (same as on transmitter side)
typedef struct{
  bool f;
  bool b;
  bool l;
  bool r;
} message;
message data;

//Function to be called on callback
void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len){
  memcpy(&data, incomingData, sizeof(data));
  front = data.f;
  back = data.b;
  left = data.l;
  right = data.r;
}

void setup() {
  //Initialize pins
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);

  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);

  pinMode(motor3Pin1, OUTPUT);
  pinMode(motor3Pin2, OUTPUT);

  pinMode(motor4Pin1, OUTPUT);
  pinMode(motor4Pin2, OUTPUT);

  Serial.begin(115200);
  Serial.println("Car Initializing...");

  WiFi.mode(WIFI_STA);

  //Initialize esp-now
  if (esp_now_init() != ESP_OK){
    return;
  }

  //Register callback function
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
  if (front == 1) {
    carforward();
  } 
  else if (back == 1) {
    carbackward();
  } 
  else if (left == 1) {
    carturnleft();
  } 
  else if (right == 1) {
    carturnright();
  } 
  else if (front == 0 && back == 0 && left == 0 && right == 0) {
    carStop();
  }
}

//Functions for specific movements
void carforward() {
  Serial.println("Moving Forward");
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH); 
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW); 
  digitalWrite(motor3Pin1, LOW);
  digitalWrite(motor3Pin2, HIGH); 
  digitalWrite(motor4Pin1, HIGH);
  digitalWrite(motor4Pin2, LOW);
}
void carbackward() {
  Serial.println("Moving Backwards");
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH); 
  digitalWrite(motor3Pin1, HIGH);
  digitalWrite(motor3Pin2, LOW);
  digitalWrite(motor4Pin1, LOW);
  digitalWrite(motor4Pin2, HIGH);
}
void carturnleft() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
void carturnright() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
void carStop() {
  Serial.println("Motor stopped");
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
  digitalWrite(motor3Pin1, LOW);
  digitalWrite(motor3Pin2, LOW);
  digitalWrite(motor4Pin1, LOW);
  digitalWrite(motor4Pin2, LOW);
}