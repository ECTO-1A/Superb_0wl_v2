# SuperbOwl
Turns ESP8266 into a WIFI controlled IR physical botnet. It can be used to turn on/off devices that are controlled by IR signals and triggered by the presence of a specific WIFI network. They will then change their own SSID to the name of the trigger network and begin broadcasting it to others in the area to trigger them as well.

<img width="575" alt="Screen Shot 2023-01-03 at 7 28 02 AM" src="https://user-images.githubusercontent.com/112792126/210357380-11ab9fbc-fc09-4adb-a395-e5b7203804ab.png">

CURRENTLY WORKING:
- Web interface to set IR signal
-  Wifi trigger (activate IR signal when specific wifi network is seen)
- Ability to trigger each other in a mini "botnet" where when connected to, it begins broadcasting the name of the "trigger" wifi network to others that then kick off the same process.

KNOWN ISSUES:


FUTURE PLANS:

- Option to set future trigger times through the web interface
- Dropdowns for Makes and Models of IR devices
- better solution for handeling raw hex of IR signal
- ability to set multiple triggers for different devices
- option to select either trigger by DATE or WIFI
