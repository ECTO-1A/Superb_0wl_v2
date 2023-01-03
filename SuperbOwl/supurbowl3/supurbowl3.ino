#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <IRsend.h>
#include <Time.h>
#include <sys/time.h>

IRsend irsend(4);  // IR LED is connected to pin 4


const char* ssid = "SupurbOwl";
const char* password = "12345678";

ESP8266WebServer server(80);

String irCode;
int triggerCount = 1;
int triggerDelay = 0;
time_t triggerTime;  // define triggerTime as a global variable


void setTime(time_t time) {
  struct timeval tv;
  tv.tv_sec = time;
  tv.tv_usec = 0;
  settimeofday(&tv, nullptr);
}


void handleRoot() {
  String html = "";
  html += "<h1>SuperbOwl v1.0</h1>";
  html += "<p>Enter the hex value of the IR signal to emit:</p>";
  html += "<form method='post'>";
  html += "<input type='text' name='irCode' value='" + irCode + "'>";
  html += "<br><br>";
  html += "<p>Enter the number of times to trigger the IR signal:</p>";
  html += "<input type='number' name='triggerCount' value='" + String(triggerCount) + "'>";  html += "<br><br>";
  html += "<p>Enter the delay between triggers (in milliseconds):</p>";
  html += "<input type='number' name='triggerDelay' value='" + String(triggerDelay) + "'>";  html += "<br><br>";
  html += "<p>Enter the date and time to trigger the IR signal:</p>";
  html += "<input type='datetime-local' name='triggerTime'>";
  html += "<br><br>";
  html += "<input type='submit' value='Set'>";
  html += "</form>";
  html += "<br><br>";
  if (triggerTime > 0) {
    html += "Trigger is set!<br>";
    html += "IR Code: " + irCode + "<br>";
    html += "Trigger Count: " + String(triggerCount) + "<br>";
    html += "Trigger Delay: " + String(triggerDelay) + " milliseconds<br>";
    html += "Trigger Time: " + String(triggerTime);
  } else {
    html += "Trigger is not set.";
  }
  server.send(200, "text/html", html);
}

void handleSubmit() {
  irCode = server.arg("irCode");
  triggerCount = server.arg("triggerCount").toInt();
  triggerDelay = server.arg("triggerDelay").toInt();
  String triggerTimeStr = server.arg("triggerTime");
  int year = triggerTimeStr.substring(0, 4).toInt();
  int month = triggerTimeStr.substring(5, 7).toInt();
  int day = triggerTimeStr.substring(8, 10).toInt();
  int hour = triggerTimeStr.substring(11, 13).toInt();
  int minute = triggerTimeStr.substring(14, 16).toInt();
  int second = triggerTimeStr.substring(17, 19).toInt();
  struct tm timeStruct;
  timeStruct.tm_year = year - 1900;  // years since 1900
  timeStruct.tm_mon = month - 1;  // months since January (0-11)
  timeStruct.tm_mday = day;  // day of the month (1-31)
  timeStruct.tm_hour = hour;  // hours since midnight (0-23)
  timeStruct.tm_min = minute;  // minutes after the hour (0-59)
  timeStruct.tm_sec = second;  // seconds after the minute (0-61)
  timeStruct.tm_isdst = -1;  // daylight saving time is not known
  time_t triggerTime = mktime(&timeStruct);
  setTime(triggerTime);
  server.send(200, "text/plain", "IR Code: " + irCode + "\nTrigger Count: " + triggerCount + "\nTrigger Delay: " + triggerDelay + "\nTrigger Time: " + (String)triggerTime);
}

void setup() {
  Serial.begin(115200);
  IPAddress apIP(192, 168, 4, 1);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP(ssid, password);
  server.on("/", handleRoot);
  server.on("/submit", handleSubmit);
  server.begin();
  Serial.println("HTTP server started");
  Serial.println(WiFi.localIP());

}

void loop() {
  time_t currentTime = time(nullptr);
  server.handleClient();
  if (currentTime >= triggerTime) {
    for (int i = 0; i < triggerCount; i++) {
      irsend.sendNEC(irCode.toInt(), 32);
      delay(triggerDelay);
    }
    triggerTime = 0;  // reset trigger time
  }
}
