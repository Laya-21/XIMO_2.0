#include <WiFi.h>
#include <WebServer.h>
#include <ESP32Servo.h>

// WiFi credentials
const char* ssid = "NAO";
const char* password = "laya1234";

// Create server
WebServer server(80);

// Servo pins
const int servoPins[4] = {14, 27, 26, 25};
Servo servos[4];

// HTML Web Page
String htmlPage() {
  String page = "<!DOCTYPE html><html><head><meta name='viewport' content='width=device-width, initial-scale=1.0'>";
  page += "<title>ESP32 Servo Control</title></head><body><h2>Servo Controller</h2>";
  for (int i = 0; i < 4; i++) {
    page += "Servo " + String(i+1) + ": <input type='range' min='0' max='180' value='90' id='servo" + String(i) + "' onchange='updateServo(" + String(i) + ")'><br><br>";
  }
  page += "<script>function updateServo(n){var val=document.getElementById('servo'+n).value;fetch('/servo?n='+n+'&v='+val);}</script>";
  page += "</body></html>";
  return page;
}

// Handle root
void handleRoot() {
  server.send(200, "text/html", htmlPage());
}

// Handle slider data
void handleServo() {
  if (server.hasArg("n") && server.hasArg("v")) {
    int index = server.arg("n").toInt();
    int val = server.arg("v").toInt();
    if (index >= 0 && index < 4) {
      servos[index].write(val);
      Serial.printf("Servo %d set to %d degrees\n", index, val);
    }
  }
  server.send(200, "text/plain", "OK");
}

void setup() {
  Serial.begin(115200);

  // Attach servos
  for (int i = 0; i < 4; i++) {
    servos[i].attach(servoPins[i]);
    servos[i].write(90);  // Default to middle
  }

  // Start WiFi in AP mode
  WiFi.softAP(ssid, password);
  Serial.println("Access Point Started");
  Serial.println(WiFi.softAPIP());

  // Set up routes
  server.on("/", handleRoot);
  server.on("/servo", handleServo);
  server.begin();
  Serial.println("Web server started");
}

void loop() {
  server.handleClient();
}
