// Include Libraries
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
} message;
message data;

// Create an object of the Adafruit_MPU6050 class
Adafruit_MPU6050 mpu;

// Initialize global variables
unsigned long timer = 0;
float x, y;
bool front = false, back = false, left = false, right = false;

// Initialize a peer
esp_now_peer_info_t peerInfo;

// Function to be called upon callback
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void setup() {
  Serial.begin(9600);

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
    while (1);  // Halt if initialization fails
  }
  Serial.println("MPU6050 Initialized!");

  // Configure accelerometer (no need for gyroscope configuration)
  mpu.setAccelerometerRange(MPU6050_RANGE_2_G);  // Set accelerometer range (2g)
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);    // Optional: set low-pass filter bandwidth

  delay(1000); // Allow time for sensor setup
}

void loop() {
  // Get accelerometer and gyroscope data from MPU6050
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);  // Only using accelerometer (gyroscope data is ignored)

  // Read accelerometer data (X and Y axis)
  x = a.acceleration.x;
  y = a.acceleration.y;

  // Print accelerometer values to Serial Monitor
  Serial.print("Accelerometer X: ");
  Serial.print(x);
  Serial.print("\tY: ");
  Serial.println(y);

  // Process accelerometer data to determine movement
  if ((millis() - timer) > 100) { // Get data every 100ms (instead of 10ms)

    // Movement detection based on accelerometer values (with reduced threshold)
    if (x >= 5)
      back = true;
    else
      back = false;

    if (x <= -5)
      front = true;
    else
      front = false;

    if (y >= 5)
      right = true;
    else
      right = false;

    if (y <= -5)
      left = true;
    else
      left = false;

    timer = millis();  // Update timer

    // Prepare the message to send
    data.f = front;
    data.b = back;
    data.l = left;
    data.r = right;

    // Send the message over ESP-NOW
    esp_now_send(broadcastAddress, (uint8_t *)&data, sizeof(data));
  }
}