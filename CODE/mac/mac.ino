#include <WiFi.h>

void setup() {
  Serial.begin(115200);
  WiFi.begin();                  // Add this line!
  delay(100);                    // Small wait just in case
  WiFi.mode(WIFI_STA);
  Serial.print("Receiver MAC Address: ");
  Serial.println(WiFi.macAddress());
}

void loop() {}
