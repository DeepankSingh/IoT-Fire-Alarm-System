# IoT Based Fire Alarm System

This project demonstrates an IoT-based fire alarm system using the ESP8266 module. It monitors temperature and gas levels and triggers an alarm when thresholds are exceeded.

## Components

- ESP8266 NodeMCU
- Temperature sensor
- Gas sensor
- Piezo buzzer
- LED

## Setup

1. Connect the sensors and actuators to the ESP8266 as described in the code comments.
2. Upload the code to the ESP8266 using the Arduino IDE.
3. Connect the ESP8266 to a WiFi network.

## Usage

The system will monitor the temperature and gas levels. If the temperature exceeds 80°C or gas levels exceed 200, the buzzer and LED will turn on.

![image](https://github.com/DeepankSingh/IoT-Fire-Alarm-System/assets/74452975/53d0b5bc-9948-46cc-8909-24c7236b4c56)

![image](https://github.com/DeepankSingh/IoT-Fire-Alarm-System/assets/74452975/2fc71f76-9b10-456f-94f5-acdfbd2819e2)

![image](https://github.com/DeepankSingh/IoT-Fire-Alarm-System/assets/74452975/21bf3d24-04e5-4879-b444-08b5b5e65ba3)


You can also manually control the buzzer through the web interface.

- To turn on the buzzer: `/piezo=ON`
- To turn off the buzzer: `/piezo=OFF`
