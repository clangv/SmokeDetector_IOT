# NodeMCU Smoke Detection & IoT Control

This project uses a NodeMCU ESP8266 to monitor smoke using an MQ2 sensor, control a light and fan, and trigger a buzzer alarm. All devices can be controlled via a simple HTTP interface.

## Features

- Smoke detection with MQ2 sensor
- Alarm with buzzer and status LED
- Remote control of light and fan via HTTP
- Alarm reset and sensor status query

## Hardware

| Component   | NodeMCU Pin |
|------------|-------------|
| Light      | D5          |
| Fan        | D6          |
| Buzzer     | D7          |
| Status LED | D2          |
| MQ2 Sensor | A0          |

## Software

- Arduino IDE
- ESP8266 board support: `https://arduino.esp8266.com/stable/package_esp8266com_index.json`
- Library: `ESP8266WiFi`

## Setup

1. Add the ESP8266 URL in **File → Preferences → Additional Boards Manager URLs**
2. Install ESP8266 board via **Tools → Board → Boards Manager**
3. Select **NodeMCU 1.0 (ESP-12E Module)**
4. Update Wi-Fi credentials in the code
5. Upload code
6. Open Serial Monitor at 9200 baud to see the NodeMCU IP

## HTTP Commands

| Endpoint        | Action                     |
|----------------|----------------------------|
| `/light/on`     | Turn light ON             |
| `/light/off`    | Turn light OFF            |
| `/fan/on`       | Turn fan ON               |
| `/fan/off`      | Turn fan OFF              |
| `/alarm/off`    | Reset buzzer and LED       |
| `/status`       | Get smoke status (SMOKE/NORMAL) |

## Notes

- Adjust `smokeThreshold` for your environment
- Alarm triggers once until reset
- Secure HTTP endpoints for real deployment
