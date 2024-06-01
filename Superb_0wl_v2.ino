#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <Ticker.h>

// Define GPIO pin for IR LED
const uint16_t kIrLed = D2;  // GPIO4

// Create IRsend object
IRsend irsend(kIrLed);

// WiFi settings
const char* ssid = "Superb0wl_v2";
const char* password = "12345678";

// Create WebServer object on port 80
ESP8266WebServer server(80);

String hexValue = "20DF10EF"; // Default test value
uint32_t frequency = 38000;  // Default frequency for NEC protocol
uint8_t repeatCount = 3;     // Default number of times to repeat the signal
unsigned long interval = 1000; // Default interval in milliseconds
bool sendingIndefinitely = false;

Ticker irTicker;
unsigned long lastScanTime = 0;
const unsigned long scanInterval = 10000; // Scan every 10 seconds

void sendIRSignal() {
  unsigned long irCode = strtoul(hexValue.c_str(), NULL, 16);

  // Send IR signal
  for (uint8_t i = 0; i < repeatCount; i++) {
    irsend.sendNEC(irCode, 32);
    delay(40);  // Delay between repeats
  }
}

void handleRoot() {
  server.send(200, "text/html", R"rawliteral(
    <!DOCTYPE HTML>
    <html>
    <head>
      <title>Superb0wl_v2</title>
      <meta name="viewport" content="width=device-width, initial-scale=1">
      <style>
        body {
          font-family: Arial, sans-serif;
          background-color: #f4f4f4;
          color: #333;
          text-align: center;
          padding: 20px;
        }
        h1 {
          color: #4CAF50;
        }
        form {
          background: #fff;
          padding: 20px;
          margin: 20px auto;
          border-radius: 8px;
          box-shadow: 0 0 10px rgba(0, 0, 0, 0.1);
          max-width: 400px;
        }
        input[type="text"], input[type="submit"] {
          width: 100%;
          padding: 10px;
          margin: 10px 0;
          border: 1px solid #ccc;
          border-radius: 4px;
        }
        input[type="submit"] {
          background-color: #4CAF50;
          color: white;
          border: none;
          cursor: pointer;
        }
        input[type="submit"]:hover {
          background-color: #45a049;
        }
        .form-group {
          margin-bottom: 15px;
          text-align: left;
        }
        label {
          margin-bottom: 5px;
          display: block;
        }
      </style>
    </head>
    <body>
      <h1>Superb0wl_v2</h1>
      <form action="/get" method="GET">
        <div class="form-group">
          <label for="hex">Hex Value:</label>
          <input type="text" id="hex" name="hex" value="20DF10EF">
        </div>
        <div class="form-group">
          <label for="freq">Frequency (Hz):</label>
          <input type="text" id="freq" name="freq" value="38000">
        </div>
        <div class="form-group">
          <label for="repeat">Repeat Count:</label>
          <input type="text" id="repeat" name="repeat" value="3">
        </div>
        <div class="form-group">
          <label for="interval">Interval (ms):</label>
          <input type="text" id="interval" name="interval" value="1000">
        </div>
        <input type="submit" value="Submit">
      </form>
      <form action="/start" method="GET">
        <input type="submit" value="Start Indefinite Sending">
      </form>
      <form action="/stop" method="GET">
        <input type="submit" value="Stop Indefinite Sending">
      </form>
    </body>
    </html>
  )rawliteral");
}

void handleGet() {
  if (server.hasArg("hex")) {
    hexValue = server.arg("hex");
  }
  if (server.hasArg("freq")) {
    frequency = server.arg("freq").toInt();
  }
  if (server.hasArg("repeat")) {
    repeatCount = server.arg("repeat").toInt();
  }
  if (server.hasArg("interval")) {
    interval = server.arg("interval").toInt();
  }

  sendIRSignal();
  server.send(200, "text/html", "IR Signal Sent! <a href=\"/\">Go Back</a>");
}

void handleStart() {
  if (!sendingIndefinitely) {
    sendingIndefinitely = true;
    irTicker.attach_ms(interval, sendIRSignal);
    server.send(200, "text/html", "Started Indefinite Sending! <a href=\"/\">Go Back</a>");
  } else {
    server.send(200, "text/html", "Already Sending Indefinitely! <a href=\"/\">Go Back</a>");
  }
}

void handleStop() {
  if (sendingIndefinitely) {
    sendingIndefinitely = false;
    irTicker.detach();
    server.send(200, "text/html", "Stopped Indefinite Sending! <a href=\"/\">Go Back</a>");
  } else {
    server.send(200, "text/html", "Not Currently Sending Indefinitely! <a href=\"/\">Go Back</a>");
  }
}

void changeAPNameAndStart() {
  int n = WiFi.scanNetworks();
  for (int i = 0; i < n; ++i) {
    String detectedSSID = WiFi.SSID(i);
    if (detectedSSID == "SUPERB_0WL") {
      WiFi.softAP("SUPERB_0WL", password);
      Serial.println("Changed AP name to SUPERB_0WL and started sending IR signals.");
      sendingIndefinitely = true;
      irTicker.attach_ms(interval, sendIRSignal);
      break;
    }
  }
}

void setup() {
  Serial.begin(115200);

  // Set IR LED pin to output and ensure it's low to avoid interference during boot
  pinMode(kIrLed, OUTPUT);
  digitalWrite(kIrLed, LOW);

  // Set up access point
  WiFi.softAP(ssid, password);
  delay(100);

  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());

  // Add a delay before initializing IRsend to ensure proper boot
  delay(5000);  // Wait for 5 seconds

  // Initialize IRsend after network is set up
  irsend.begin();

  // Define the routes
  server.on("/", handleRoot);
  server.on("/get", handleGet);
  server.on("/start", handleStart);
  server.on("/stop", handleStop);

  // Start server
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  // Handle client requests
  server.handleClient();

  // Scan for networks at intervals
  if (millis() - lastScanTime > scanInterval) {
    lastScanTime = millis();
    if (!sendingIndefinitely) {
      changeAPNameAndStart();
    }
  }
}
