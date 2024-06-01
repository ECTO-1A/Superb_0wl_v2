### Arduino IDE Setup for ESP8266

1. **Install Board Manager:**
   - Open Arduino IDE.
   - Go to `File` > `Preferences`.
   - In "Additional Boards Manager URLs," add: `http://arduino.esp8266.com/stable/package_esp8266com_index.json`.
   - Click "OK."

2. **Install ESP8266 Board:**
   - Go to `Tools` > `Board` > `Boards Manager`.
   - Search for "ESP8266" and click "Install."

3. **Select Board:**
   - Go to `Tools` > `Board` and select your specific ESP8266 model (e.g., "NodeMCU 1.0 (ESP-12E Module)").

4. **Configure Settings:**
   - `Tools` > `Port`: Select the appropriate COM port.
   - `Tools` > `Upload Speed`: Select `115200`.
   - `Tools` > `Flash Size`: Select appropriate size (e.g., "4M (3M SPIFFS)").

5. **Install Libraries:**
   - Go to `Sketch` > `Include Library` > `Manage Libraries`.
   - Search for and install `IRremoteESP8266`.

6. **Upload Code:**
   - Click the upload button to program your ESP8266.
