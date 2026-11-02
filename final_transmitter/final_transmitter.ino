#include "esp_now.h"
#include "WiFi.h"
#include "Wire.h"
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

// Receiver MAC Address
uint8_t broadcastAddress[] = {0x2C, 0xBC, 0xBB, 0x4C, 0x64, 0xB8};

// Struct to send data
typedef struct {
  bool f;
  bool b;
  bool l;
  bool r;
  bool stop;
} message; 
message data;

// Create an object of the Adafruit_MPU6050 class
Adafruit_MPU6050 mpu;

// Initialize global variables
unsigned long timer = 0;
float x, y;
bool front = false, back = false, left = false, right = false;
const int BUTTON_PIN = 4; // Define button pin
bool stopCar = false;
bool lastButtonState = HIGH;

// Initialize a peer
esp_now_peer_info_t peerInfo;

// Function to be called upon callback
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void setup() {
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Configure the button pin`
  
  WiFi.mode(WIFI_STA);

  // Initialize esp-now
  if (esp_now_init() != 0) {
    Serial.println("Error Initializing ESP NOW");
    return;
  }

  // Register callback function
  esp_now_register_send_cb(OnDataSent);

  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  // Add peer
  if (esp_now_add_peer(&peerInfo) != 0) {
    Serial.println("Failed to add peer");
    return;
  }

  // Code for MPU6050 setup using Adafruit library (accelerometer only)
  Wire.setPins(21, 22); // If using custom I2C pins, otherwise can omit
  Wire.begin();

  if (!mpu.begin()) {
    Serial.println("Failed to initialize MPU6050!");
    while (1);
  }
  Serial.println("MPU6050 Initialized!");

  mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  delay(1000);
}

void loop() {
  // Check if the button is pressed and toggle stopCar state
  bool buttonState = digitalRead(BUTTON_PIN) == LOW; // Active LOW button
  if (buttonState && lastButtonState == HIGH) {
    stopCar = !stopCar;
  }
  lastButtonState = buttonState;

  data.stop = stopCar; // Set stop flag

  // Get accelerometer and gyroscope data from MPU6050
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  x = a.acceleration.x;
  y = a.acceleration.y;

  Serial.print("Accelerometer X: ");
  Serial.print(x);
  Serial.print("\tY: ");
  Serial.println(y);

  if ((millis() - timer) > 100) {
    if (!stopCar) {
      front = (x <= -5);
      back = (x >= 5);
      right = (y >= 5);
      left = (y <= -5);
    } else {
      front = back = left = right = false; // Stop movement
    }

    timer = millis();

    // Prepare the message to send
    data.f = front;
    data.b = back;
    data.l = left;
    data.r = right;

    // Send the message over ESP-NOW protocol
    esp_now_send(broadcastAddress, (uint8_t *)&data, sizeof(data));
  }
}
