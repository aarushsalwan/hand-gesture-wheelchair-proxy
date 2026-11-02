#include "esp_now.h"
#include "WiFi.h"

// Set Motor PINs
#define IN1 14
#define IN2 27
#define IN3 26
#define IN4 25
#define LED_PIN 2     // Define LED pin

// Global variables for movement
bool front = false;
bool back = false;
bool left = false;
bool right = false;
bool stopCar = false;

// Struct to receive data (same as on "hand" side)
typedef struct {
  bool f;
  bool b;
  bool l;
  bool r;
  bool stop;
} message;

message data;

// Correct callback function with proper signature
void OnDataRecv(const esp_now_recv_info* recv_info, const uint8_t* incomingData, int len) {
  memcpy(&data, incomingData, sizeof(data));  // Copy the received data into the 'data' struct

  // Update movement flags based on received data
  front = data.f;
  back = data.b;
  left = data.l;
  right = data.r;
  stopCar = data.stop;
}

void setup() {
  // Initialize motor control pins
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(LED_PIN, OUTPUT); // Configure LED pin
  digitalWrite(LED_PIN,HIGH);
  delay(1000);

  // Initialize Serial Monitor
  Serial.begin(115200);

  // Initialize Wi-Fi in STA mode
  WiFi.mode(WIFI_STA);

  // Initialize ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW Initialization Failed");
    return;
  }

  // Register callback function for receiving data
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
  // Print movement status (for debugging purposes)
  Serial.print("Front: ");
  Serial.print(front);
  Serial.print(" Back: ");
  Serial.print(back);
  Serial.print(" Left: ");
  Serial.print(left);
  Serial.print(" Right: ");
  Serial.print(right);
  Serial.print(" Stop: ");
  Serial.println(stopCar);

  // Control the car based on received gesture data
  if (stopCar) {
    carStop();
    digitalWrite(LED_PIN, HIGH); // Turn on LED
  } 
  else {
    digitalWrite(LED_PIN, LOW); // Turn off LED
    if (front) {
      carForward();
    } 
    else if (back) {
      carBackward();
    } 
    else if (left) {
      carTurnLeft();
    } 
    else if (right) {
      carTurnRight();
    } 
    else {
      carStop();
    }
  }
}

// Function to move the car forward
void carForward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH); 
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

// Function to move the car backward
void carBackward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

// Function to turn the car left
void carTurnLeft() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

// Function to turn the car right
void carTurnRight() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

// Function to stop the car
void carStop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}