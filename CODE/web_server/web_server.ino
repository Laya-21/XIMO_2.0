#include <WiFi.h>
#include <WebServer.h>
#include <ESP32Servo.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

const char* ssid = "NAO";
const char* password = "laya1234";

Servo servo1, servo2, servo3, servo4;
WebServer server(80);

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

bool isRecording = false;
struct Pose {
  int s1, s2, s3, s4;
};
std::vector<Pose> recordedMovements;

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <title>XIMO 2.0</title>
  <style>
    body {
      background-color: black;
      color: white;
      font-family: Arial, sans-serif;
      text-align: center;
      margin: 0;
      padding: 0;
    }
    h1 {
      color: #00ffcc;
      font-size: 36px;
      margin: 20px 0;
    }
    .slider-container {
      display: flex;
      justify-content: center;
      flex-direction: column;
      align-items: center;
      gap: 20px;
      margin-bottom: 40px;
    }
    input[type=range] {
      width: 300px;
    }
    button {
      background-color: #00ffcc;
      color: black;
      border: none;
      padding: 10px 20px;
      margin: 10px;
      font-size: 16px;
      cursor: pointer;
      border-radius: 5px;
    }
  </style>
</head>
<body>
  <h1>XIMO 2.0</h1>
  <div class="slider-container">
    <div>
      <label>Servo 1</label><br>
      <input type="range" min="0" max="180" value="90" onchange="sendSlider(1, this.value)">
    </div>
    <div>
      <label>Servo 2</label><br>
      <input type="range" min="0" max="180" value="90" onchange="sendSlider(2, this.value)">
    </div>
    <div>
      <label>Servo 3</label><br>
      <input type="range" min="0" max="180" value="90" onchange="sendSlider(3, this.value)">
    </div>
    <div>
      <label>Servo 4</label><br>
      <input type="range" min="0" max="180" value="90" onchange="sendSlider(4, this.value)">
    </div>
  </div>
  <div>
    <button onclick="startRecording()">Start Recording</button>
    <button onclick="stopRecording()">Stop Recording</button>
    <button onclick="playSequence()">Play Sequence</button>
  </div>
  <script>
    function sendSlider(servo, value) {
      fetch(`/slider?servo=${servo}&value=${value}`);
    }
    function startRecording() {
      fetch('/startRecording');
    }
    function stopRecording() {
      fetch('/stopRecording');
    }
    function playSequence() {
      fetch('/playSequence');
    }
  </script>
</body>
</html>
)rawliteral";

void updateOLED() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("IP: ");
  display.println(WiFi.localIP());
  display.setCursor(0, 16);
  display.printf("S1: %3d  S2: %3d\n", servo1.read(), servo2.read());
  display.printf("S3: %3d  S4: %3d\n", servo3.read(), servo4.read());
  display.display();
}

void handleRoot() {
  server.send(200, "text/html", index_html);
}

void recordPose() {
  Pose p = {
    servo1.read(),
    servo2.read(),
    servo3.read(),
    servo4.read()
  };
  recordedMovements.push_back(p);
}

void handleSlider() {
  int servoNum = server.arg("servo").toInt();
  int value = server.arg("value").toInt();
  Serial.printf("Slider: Servo %d -> %d degrees\n", servoNum, value);
  switch (servoNum) {
    case 1: servo1.write(value); break;
    case 2: servo2.write(value); break;
    case 3: servo3.write(value); break;
    case 4: servo4.write(value); break;
  }
  if (isRecording) {
    recordPose();
  }
  updateOLED();
  server.send(200, "text/plain", "OK");
}

void handleStartRecording() {
  recordedMovements.clear();
  isRecording = true;
  Serial.println("Recording started");
  server.send(200, "text/plain", "Recording started");
}

void handleStopRecording() {
  isRecording = false;
  Serial.println("Recording stopped");
  server.send(200, "text/plain", "Recording stopped");
}

void handlePlaySequence() {
  Serial.println("Playing recorded sequence");
  for (auto& pose : recordedMovements) {
    servo1.write(pose.s1);
    servo2.write(pose.s2);
    servo3.write(pose.s3);
    servo4.write(pose.s4);
    updateOLED();
    delay(500);
  }
  server.send(200, "text/plain", "Playback done");
}

void displayStartupMessage() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  
  // Display "I was created to create"
  display.setCursor(0, 0);
  display.println("I was created");
  display.setCursor(0, 10);
  display.println("to create");

  // Display "XIMO 2.0"
  display.setCursor(0, 30);
  display.setTextSize(2);  // Increase text size for title
  display.println("XIMO 2.0");

  display.display();
  delay(2000);  // Show this message for 2 seconds before moving on
}

void setup() {
  Serial.begin(115200);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true);
  }

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected to WiFi!");
  Serial.print("ESP32 IP Address: ");
  Serial.println(WiFi.localIP());

    displayStartupMessage();
  
  // Clear display before starting the normal info display
  display.clearDisplay();

  // Start with the normal servo control display
  updateOLED();


  servo1.setPeriodHertz(50); servo1.attach(5);
  servo2.setPeriodHertz(50); servo2.attach(27);
  servo3.setPeriodHertz(50); servo3.attach(26);
  servo4.setPeriodHertz(50); servo4.attach(25);

  server.on("/", handleRoot);
  server.on("/slider", handleSlider);
  server.on("/startRecording", handleStartRecording);
  server.on("/stopRecording", handleStopRecording);
  server.on("/playSequence", handlePlaySequence);
  server.begin();
  Serial.println("Web server started!");
}

void loop() {
  server.handleClient();
}
