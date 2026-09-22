# ⛑️ Smart Helmet for Coal Mine Worker Safety

## IoT-Enabled Smart Helmet for Real-Time Industrial Safety Monitoring

An IoT-enabled wearable safety system designed for **coal mine workers** using an ESP32, environmental sensors, motion sensing, GPS tracking, automatic illumination, emergency alerts, and a real-time web dashboard.

The system continuously monitors important environmental and physical parameters such as:

- Temperature
- Humidity
- Air quality / gas level
- Light intensity
- Worker motion and fall conditions
- GPS location

The collected sensor data is processed by an **ESP32 microcontroller** and transmitted wirelessly for real-time monitoring through a web-based dashboard.

When potentially unsafe conditions are detected, the system can generate local alerts using a **buzzer and LED indicators**, while the dashboard provides remote visibility of the worker's condition.

---

# 📌 Project Overview

Coal mining environments can expose workers to several hazards, including poor lighting, abnormal temperature and humidity, harmful gas concentrations, falls, and difficulty locating workers during emergency situations.

Conventional safety helmets mainly provide physical protection but do not continuously monitor environmental or worker conditions.

This project combines a safety helmet with embedded sensing and IoT technologies to create a wearable monitoring platform.

The system integrates:

- ESP32 microcontroller
- DHT11 temperature and humidity sensor
- MQ135 air-quality/gas sensor
- LDR light sensor
- MPU6050 accelerometer and gyroscope
- NEO-6M GPS module
- LED / LED strip
- Buzzer
- Emergency push button
- Wi-Fi connectivity
- Web-based monitoring dashboard

The prototype demonstrates how multiple sensors can be combined into a single wearable safety system.

---

# 🎯 Objectives

The main objectives of the project are:

1. Design a smart helmet capable of monitoring temperature and humidity.
2. Monitor air quality using the MQ135 sensor.
3. Detect changes in lighting conditions using an LDR.
4. Automatically control an illumination LED/LED strip in dark conditions.
5. Detect sudden acceleration events that may indicate a fall.
6. Track the worker's location using GPS.
7. Provide local alerts using a buzzer and LED indicators.
8. Provide an emergency alert mechanism.
9. Transmit sensor information wirelessly using ESP32 Wi-Fi.
10. Display sensor information on a real-time web dashboard.
11. Develop a compact and portable prototype for industrial safety monitoring.

---

# ⭐ Key Features

- ⛑️ Wearable smart helmet prototype
- 📡 ESP32-based IoT system
- 🌡️ Real-time temperature monitoring
- 💧 Humidity monitoring
- ⚠️ MQ135-based gas/air-quality monitoring
- 💡 Automatic lighting based on ambient light
- 📐 MPU6050-based motion and fall detection
- 📍 GPS-based worker location tracking
- 🚨 Emergency push-button alert
- 🔊 Buzzer-based local warning
- 💡 LED-based visual warning
- 🌐 Real-time web dashboard
- 📊 Live sensor data visualization
- 🔋 Portable battery-powered prototype
- 🧩 Modular sensor architecture
- 🏭 Potential applications in hazardous industrial environments

---

# 🧠 System Concept

The overall system can be represented as:

```text
                  SMART HELMET SYSTEM
                         │
                         ▼
                  ┌─────────────┐
                  │    ESP32    │
                  │ Controller  │
                  └──────┬──────┘
                         │
       ┌─────────────────┼──────────────────┐
       │                 │                  │
       ▼                 ▼                  ▼
   ENVIRONMENT        MOTION             LOCATION
     SENSORS          SENSOR               GPS
       │                 │                  │
       ▼                 ▼                  ▼
    DHT11            MPU6050             NEO-6M
    MQ135
     LDR
       │                 │                  │
       └─────────────────┼──────────────────┘
                         │
                         ▼
                  DATA PROCESSING
                         │
              ┌──────────┴──────────┐
              │                     │
              ▼                     ▼
       LOCAL SAFETY ALERT       Wi-Fi DATA
              │                     │
       ┌──────┴──────┐              ▼
       │             │        WEB DASHBOARD
       ▼             ▼
     BUZZER        LED
