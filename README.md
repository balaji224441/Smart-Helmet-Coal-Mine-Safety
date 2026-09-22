# ⛑️ Smart Helmet for Coal Mine Worker Safety

## IoT-Enabled Smart Helmet for Real-Time Coal Mine Safety Monitoring

Smart Helmet for Coal Mine Worker Safety is an IoT-enabled wearable safety system designed to monitor environmental conditions, detect hazardous situations, track worker location, provide automatic lighting, and generate real-time safety alerts.

The system uses an **ESP32 microcontroller** as the central processing unit and integrates multiple sensors including **DHT11, MQ135, LDR, MPU6050, and NEO-6M GPS**.

The collected sensor data is processed by the ESP32 and transmitted wirelessly through Wi-Fi to a web-based monitoring dashboard.

The system also provides local alerts through a **buzzer, status LED, LED illumination system, and emergency push button**.

---

## 📌 Project Overview

Coal mining is one of the most hazardous industrial occupations. Workers may be exposed to harmful gases, abnormal temperature and humidity, poor lighting, falls, and emergency situations.

Traditional safety helmets mainly provide physical protection but do not continuously monitor the worker's environmental conditions or provide real-time information to supervisors.

This project proposes a **Smart Helmet for Coal Mine Workers** that combines wearable electronics, embedded systems, sensors, IoT communication, and real-time monitoring.

The helmet continuously monitors:

- Temperature
- Humidity
- Air-quality/gas level
- Light intensity
- Motion
- Fall conditions
- GPS location
- Emergency status

The system can automatically generate alerts when predefined safety conditions are detected.

---

## 🎯 Objectives

The main objectives of the project are:

1. To design a smart helmet for coal mine workers.
2. To monitor temperature in real time.
3. To monitor humidity conditions.
4. To detect abnormal air-quality/gas levels.
5. To detect surrounding light conditions.
6. To automatically activate illumination in dark environments.
7. To detect sudden motion and possible falls.
8. To track the worker's location using GPS.
9. To provide local alerts using a buzzer and LED.
10. To provide an emergency push-button mechanism.
11. To transmit sensor information using ESP32 Wi-Fi.
12. To display real-time sensor information on a web dashboard.
13. To develop a portable and low-cost industrial safety prototype.
14. To provide a foundation for future AI, GSM, LoRa, and cloud-based safety systems.

---

# ✨ Features

- ⛑️ Wearable smart helmet platform
- 🌡️ Real-time temperature monitoring
- 💧 Real-time humidity monitoring
- ⚠️ MQ135-based gas/air-quality monitoring
- 💡 Automatic lighting using LDR
- 📐 MPU6050-based motion and fall detection
- 📍 GPS-based worker location tracking
- 🚨 Emergency push-button
- 🔊 Buzzer-based warning system
- 💡 LED-based warning and illumination
- 📡 ESP32 Wi-Fi communication
- 🌐 Web-based real-time monitoring dashboard
- 🔋 Portable battery-powered operation
- 📊 Threshold-based safety decision system

---

# 🧩 System Components

The Smart Helmet consists of three major layers:

```text
                 SMART HELMET SYSTEM
                        │
        ┌───────────────┼───────────────┐
        │               │               │
        ▼               ▼               ▼
   ENVIRONMENT       SAFETY/MOTION     LOCATION
     SENSORS            SENSORS          SYSTEM
        │               │               │
        ▼               ▼               ▼
   DHT11 / MQ135      MPU6050          NEO-6M
        LDR
        │               │               │
        └───────────────┼───────────────┘
                        │
                        ▼
                     ESP32
                        │
              ┌─────────┴─────────┐
              │                   │
              ▼                   ▼
        LOCAL ALERTS            Wi-Fi
              │                   │
        ┌─────┴─────┐             ▼
        ▼           ▼        WEB DASHBOARD
      BUZZER        LED
