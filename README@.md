# SuperbOwl

SuperbOwl is an ESP8266-based project that turns the ESP8266 into a WiFi-controlled IR physical botnet. It can be used to turn on/off devices that are controlled by IR signals and triggered by the presence of a specific WiFi network. The devices will change their own SSID to the name of the trigger network and begin broadcasting it to others in the area to trigger them as well.

<img width="575" alt="Superb0wl v2" src="https://github.com/ECTO-1A/SuperbOwl/assets/112792126/cce06009-27d2-444e-85f1-74ca5c52370e">

## Features
- **Web Interface**: Configure and control the IR signal sending through a web interface.
- **WiFi Trigger**: Activate IR signals when a specific WiFi network is detected.
- **Botnet Capability**: Devices trigger each other in a mini "botnet", broadcasting the trigger WiFi network to initiate the same process on other devices.

## Hardware Requirements
- ESP8266 NodeMCU / D1 Mini
- IR LED
- 2N2222A NPN Transistor
- Resistors: 1kΩ
- Connecting wires
- Breadboard (optional)

## Schematic
**COMING SOON*

## Wiring
- **IR LED:**
  - Anode (long leg) to 5V.
  - Cathode (short leg) to the collector of the 2N2222A transistor.
- **2N2222A Transistor:**
  - Base to GPIO pin D2 of the ESP8266 through a 1kΩ resistor.
  - Collector to the cathode of the IR LED.
  - Emitter to GND.


## Software Setup
1. **Install the Required Libraries**:
   - `ESP8266WiFi`
   - `ESP8266WebServer`
   - `IRremoteESP8266`
   - `Ticker`

2. **Upload the Code**:
   - Use the Arduino IDE to upload the code to the ESP8266.

3. **Connect to the Device**:
   - After powering on the ESP8266, it will create a WiFi network with the SSID "Superb0wl_v2".
   - Connect to this network using the password "12345678".

4. **Access the Web Interface**:
   - Open a web browser and navigate to the IP address provided by the ESP8266 (usually `192.168.4.1`).
   - Use the web interface to configure the IR signal parameters and control the sending process.

## Current Features
- **Web Interface to Set IR Signal**: Allows users to input hex values, frequency, repeat count, and interval for the IR signal.
- **WiFi Trigger**: Automatically starts sending the IR signal when a specific WiFi network ("SUPERB_0WL") is detected.
- **Botnet Functionality**: Devices change their SSID to the trigger network's name and begin broadcasting it, triggering nearby devices to do the same.

## Known Issues
- No known issues at this time.

## Future Plans
- **Set Future Trigger Times**: Add an option to set future trigger times through the web interface.
- **Dropdowns for IR Device Makes and Models**: Simplify the process of selecting IR signals for common devices.
- **Improve Handling of Raw Hex IR Signal**: Provide better input validation and feedback for raw hex IR signals.
- **Multiple Triggers for Different Devices**: Allow setting multiple triggers for different devices.
- **Trigger by Date or WiFi**: Option to select whether to trigger by a specific date/time or WiFi network detection.

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments
- Concepts and initial work by [ECTO-1A](https://github.com/ECTO-1A)

---
Feel free to contribute, open issues, or submit pull requests!
```
