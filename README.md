
# CONTROL RELAY USING ESP01 (ESP8266)

The ES01, Based on the ESP8266 chip designed by Espressif, its focus on low power consumption and compact size makes it easy to develop for small-scale projects. Despite its small size, this microcontroller allows us to create systems with Wi-Fi or internet features. Its specifications are as follows: 1MB Flash, 80kB RAM, 802.11 b/g/n 2.4GHz. However, this chip has a more limited pinout.


## Cool Features

- 2 Relays
- Control by using WIFI
- Without complex configuration and program
- Low Cost Project
- Very Easy to make



## Installation

Install by download or clone this repository 

```bash
  git clone https://github.com/Nizar005/ESP-01_Remote_Controlled_Relay.git
  cd ESP-01_Remote_Controlled_Relay
```


## How to Flash

Use USB to TTL module, like CH340 or FTDI

1. Wiring the ESP01 to USB to TTL module with this schematic

| ESP01  | USB to TTL module |
| ------------- | ------------- |
| VCC  | 3V3  |
| CH_PD/CH_EN  | 3V3  |
| RX | TX |
|TX | RX |
| GND | GND|
|GPIO0 (Flash) |GND |
2. Open your IDE, use Arduino IDE or PlatformIO; both are easy to use
3. In Arduino IDE, click ```File > Preferences```
4. Paste this link ```https://arduino.esp8266.com/stable/package_esp8266com_index.json``` into ```Additional boards managers URLs``` section 

### Wiring Example

![Wiring ESP01 to TTL](https://github.com/user-attachments/assets/05f1389d-55ba-4433-bb1b-b973f1ae405e)


## Running Program

To run program, follow these instructions
1. Power up the ESP01 
2. Connect to WIFI with SSID ```ESP-Control``` with password ```12345678```
3. Open the Captive-Portal or AP ```192.168.4.1```
4. Try to control the relay
## Schematic

![Schematic](https://i.pinimg.com/originals/02/dc/2f/02dc2ff30a91cfba8379da958848db64.gif)

## Documentation

![demo](https://i.pinimg.com/originals/02/dc/2f/02dc2ff30a91cfba8379da958848db64.gif)


## Authors

- [@nizmi005](https://www.instagram.com/nizmi005/)


