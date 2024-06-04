### SuperbØwl Build Guide

#### Components Required
- ESP8266 microcontroller
- IR333-A infrared LED
- Two 4.7Ω resistors (1W each) or one 2.2Ω resistor (2W)
- 330Ω resistor (1/4W)
- 2N2222A NPN transistor
- Breadboard and jumper wires

#### Circuit Diagram
*Diagram illustration coming soon*

#### Step-by-Step Instructions

1. **Resistor Configuration:**
   - Connect two 4.7Ω resistors in parallel (total ~2.35Ω) or use one 2.2Ω resistor.
   - The combined power rating of the two 4.7Ω resistors will be 2W, suitable for handling the current.

2. **Connect the IR LED:**
   - Anode to Vcc (3.3V) through the parallel resistors or single 2.2Ω resistor.
   - Cathode to the collector of the 2N2222A transistor.

3. **Transistor Base:**
   - Base of the 2N2222A to an ESP8266 GPIO pin through a 330Ω resistor.

4. **Transistor Emitter:**
   - Emitter to ground (GND).

5. **Powering the Circuit:**
   - Ensure the ESP8266 is powered correctly with a 3.3V supply.

#### Expected Currents
- **2.2Ω resistor**: Approximately 0.955A
- **2.35Ω resistor (two 4.7Ω in parallel)**: Approximately 0.894A
- **3.3Ω resistor**: Approximately 0.636A

### LED Power Handling
**Note:The IR333-A LED can handle up to 1A pulses for remote applications. Ensure pulses are short to prevent damage.**


### Notes and Common Questions

1. **Resistor Wattage:**
   - The 330Ω resistor for the transistor base does not need to be exactly 1/4W; higher wattage resistors (e.g., 1/2W) are also acceptable and will work without issue.

2. **Short Pulse Duration:**
   - A short pulse typically ranges from a few microseconds to a few milliseconds. Avoid continuous high-current pulses to prevent overheating and damage to the LED and transistor.

3. **Power Supply Considerations:**
   - The circuit is designed to run off a 3.3V supply from the ESP8266. Connecting to a 5V pin would require different resistor values to prevent overcurrent and potential damage to the components.

4. **Parallel Resistor Configuration:**
   - Using two 4.7Ω resistors in parallel provides a resistance of 2.35Ω and a combined power rating of 2W. This setup can safely handle the current required by the IR LED.

5. **Current Limiting:**
   - Ensure the current-limiting resistors are correctly valued and rated to handle the expected current without overheating.

6. **Identifying 2N2222A Transistor Legs:**
   - The 2N2222A transistor has three legs: Emitter, Base, and Collector. When the flat side of the transistor is facing you, the legs are (from left to right): Emitter, Base, Collector.

This guide provides the essential steps to build an IR remote using an ESP8266. For more detailed instructions, check the GitHub repository linked [here](#).