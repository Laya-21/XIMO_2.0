#include <esp_now.h>
#include <WiFi.h>

// === Joystick 1 (ADC1) ===
#define JOY1_X_PIN 34
#define JOY1_Y_PIN 35
#define JOY1_SW_PIN 32

// === Joystick 2 (ADC2) ===
#define JOY2_X_PIN 25
#define JOY2_Y_PIN 26
#define JOY2_SW_PIN 27

// === Pushbuttons ===
#define BUTTON1_PIN 2
#define BUTTON2_PIN 15

// Structure to send
typedef struct struct_message {
  int joy1_x;
  int joy1_y;
  bool joy1_sw;
  int joy2_x;
  int joy2_y;
  bool joy2_sw;
  bool button1;
  bool button2;
} struct_message;

struct_message outgoingData;

// Receiver MAC Address
uint8_t receiverAddress[] = {0x5C, 0x01, 0x3B, 0x72, 0x8E, 0x30};

void setup() {
  Serial.begin(115200);

  // Setup pin modes
  pinMode(JOY1_SW_PIN, INPUT_PULLUP);
  pinMode(JOY2_SW_PIN, INPUT_PULLUP);
  pinMode(BUTTON1_PIN, INPUT_PULLUP);
  pinMode(BUTTON2_PIN, INPUT_PULLUP);

  // Init WiFi in STA mode
  WiFi.mode(WIFI_STA);
  Serial.println("ESP-NOW Transmitter");

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("❌ Error initializing ESP-NOW");
    return;
  }

  // Register peer
  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, receiverAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("❌ Failed to add peer");
    return;
  }

  Serial.println("✅ ESP-NOW Initialized.");
}

void loop() {
  // Read joystick 1
  outgoingData.joy1_x = analogRead(JOY1_X_PIN);
  outgoingData.joy1_y = analogRead(JOY1_Y_PIN);
  outgoingData.joy1_sw = digitalRead(JOY1_SW_PIN) == LOW;

  // Read joystick 2
  outgoingData.joy2_x = analogRead(JOY2_X_PIN);
  outgoingData.joy2_y = analogRead(JOY2_Y_PIN);
  outgoingData.joy2_sw = digitalRead(JOY2_SW_PIN) == LOW;

  // Read push buttons
  outgoingData.button1 = digitalRead(BUTTON1_PIN) == LOW;
  outgoingData.button2 = digitalRead(BUTTON2_PIN) == LOW;

  // Print the outgoing data
  Serial.println("📤 Sending Data:");
  Serial.printf("Joy1 - X: %d | Y: %d | SW: %s\n", outgoingData.joy1_x, outgoingData.joy1_y, outgoingData.joy1_sw ? "Pressed" : "Released");
  Serial.printf("Joy2 - X: %d | Y: %d | SW: %s\n", outgoingData.joy2_x, outgoingData.joy2_y, outgoingData.joy2_sw ? "Pressed" : "Released");
  Serial.printf("Button 1: %s | Button 2: %s\n", outgoingData.button1 ? "Pressed" : "Released", outgoingData.button2 ? "Pressed" : "Released");

  // Send data
  esp_err_t result = esp_now_send(receiverAddress, (uint8_t *)&outgoingData, sizeof(outgoingData));

  if (result == ESP_OK) {
    Serial.println("✅ Data sent successfully!\n");
  } else {
    Serial.println("❌ Error sending the data\n");
  }

  delay(300);
}
