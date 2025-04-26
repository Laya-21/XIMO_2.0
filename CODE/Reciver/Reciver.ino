#include <ESP32Servo.h>

Servo myServo;

int angles[] = {0, 45, 90, 135, 180};  // Angles to sweep
int numAngles = sizeof(angles) / sizeof(angles[0]);

void setup() {
  Serial.begin(115200);
  myServo.setPeriodHertz(50);           // Standard 50Hz servo PWM
  myServo.attach(13, 500, 2400);        // GPIO13, min and max pulse width

  Serial.println("Servo Sweep Starting...");
}

void loop() {
  for (int i = 0; i < numAngles; i++) {
    myServo.write(angles[i]);           // Move servo
    Serial.print("Moving to angle: ");
    Serial.println(angles[i]);
    delay(1000);                        // Wait 1 second
  }
}
