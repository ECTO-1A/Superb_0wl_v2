// Use this to test out basic functionality if the main .ino isn't working

#include <IRremoteESP8266.h>
#include <IRsend.h>

const uint16_t kIrLedPin = D2; // GPIO pin

IRsend irsend(kIrLedPin);

void setup() {
  irsend.begin();
}

void loop() {
  irsend.sendNEC(0x20DF10EF, 32); // Example IR code
  delay(5000); // Delay between transmissions
}