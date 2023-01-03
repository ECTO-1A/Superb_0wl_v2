# SuperbOwl
Turns ESP8266 into a WIFI controlled IR device with an option to set future trigger times through the web interface.

<img width="575" alt="Screen Shot 2023-01-03 at 7 28 02 AM" src="https://user-images.githubusercontent.com/112792126/210357380-11ab9fbc-fc09-4adb-a395-e5b7203804ab.png">


KNOWN ISSUES:

- "Trigger is not set" message isnt updating (should show all info from set trigger)

FUTURE PLANS:

- Wifi trigger (activate IR signal when specific wifi network is seen)
- ability to trigger each other in a mini "botnet" where when connected to, it begins broadcasting the name of the "trigger" wifi network to others that then kick off the same process.
- Dropdowns for Makes and Models of IR devices
- better solution for handeling raw hex of IR signal
- ability to set multiple triggers for different devices
- option to select either trigger by DATE or WIFI
