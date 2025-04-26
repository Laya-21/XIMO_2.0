// === Joystick 1 (ADC1) ===
#define JOY1_X_PIN 34
#define JOY1_Y_PIN 35
#define JOY1_SW_PIN 32

// === Joystick 2 (ADC2 — no WiFi) ===
#define JOY2_X_PIN 25
#define JOY2_Y_PIN 26
#define JOY2_SW_PIN 27

// === Pushbuttons ===
#define BUTTON1_PIN 2
#define BUTTON2_PIN 15

void setup() {
  Serial.begin(115200);

  // Joystick switches
  pinMode(JOY1_SW_PIN, INPUT_PULLUP);
  pinMode(JOY2_SW_PIN, INPUT_PULLUP);

  // Push buttons
  pinMode(BUTTON1_PIN, INPUT_PULLUP);
  pinMode(BUTTON2_PIN, INPUT_PULLUP);
}

void loop() {
  // === Joystick 1 ===
  int joy1_x = analogRead(JOY1_X_PIN);
  int joy1_y = analogRead(JOY1_Y_PIN);
  bool joy1_sw = digitalRead(JOY1_SW_PIN) == LOW;

  // === Joystick 2 ===
  int joy2_x = analogRead(JOY2_X_PIN);
  int joy2_y = analogRead(JOY2_Y_PIN);
  bool joy2_sw = digitalRead(JOY2_SW_PIN) == LOW;

  // === Pushbuttons ===
  bool button1 = digitalRead(BUTTON1_PIN) == LOW;
  bool button2 = digitalRead(BUTTON2_PIN) == LOW;

  // === Serial Output ===
  Serial.println("=== Joystick 1 ===");
  Serial.printf("X: %d | Y: %d | Switch: %s\n", joy1_x, joy1_y, joy1_sw ? "Pressed" : "Released");

  Serial.println("=== Joystick 2 ===");
  Serial.printf("X: %d | Y: %d | Switch: %s\n", joy2_x, joy2_y, joy2_sw ? "Pressed" : "Released");

  Serial.println("=== Push Buttons ===");
  Serial.printf("Button 1 (GPIO 2): %s\n", button1 ? "Pressed" : "Released");
  Serial.printf("Button 2 (GPIO 15): %s\n", button2 ? "Pressed" : "Released");

  Serial.println("----------------------------\n");
  delay(300);
}
