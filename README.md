# Automatic Irrigation System

## Introduction:
This project is an automated plant watering system using an Arduino. It monitors the soil moisture level every hour and waters the plant if the soil is too dry. The system uses an RTC module to schedule watering at a specific time daily. The pump stops automatically when the soil moisture reaches an optimal level or after a set maximum duration.

## Hardware List:
1. Arduino board (e.g., Arduino Nano)
2. Soil moisture sensor
3. Relay module
4. Water pump
5. RTC module (e.g., DS3231)
6. Jumper wires
7. Power supply for the pump

## How It Works:
1. The system reads the soil moisture level using a sensor.
2. At the scheduled time (e.g., 6:00 AM), it checks if the soil is dry.
3. If the moisture level is below the threshold, the water pump is activated.
4. Additionally, it will check the soil moisture level every hour.
5. If the moisture level drops below the threshold during these hourly checks, the pump will water the plant.
6. The pump continues until the moisture level is sufficient or the maximum watering duration (2 minutes) is reached.
7. The RTC ensures accurate timing for the daily checks and watering schedule.

## Future Development:
1. Add a water level sensor to monitor the reservoir and provide low-water alerts.
2. Integrate Wi-Fi or Bluetooth for remote monitoring and control.
3. Use solar power for energy efficiency.
4. Extend the system to handle multiple plants/zones.


## Disclaimer:
This code has been tested only on my specific hardware setup (Arduino Nano, DS3231 RTC, relay module, and soil moisture sensor). It may not work as intended on other Arduino boards or with different hardware configurations. Please test and adjust the code according to your hardware setup before deployment.

--- 

Feel free to use or modify this project.