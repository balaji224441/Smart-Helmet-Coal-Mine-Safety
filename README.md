⛑️ Smart Helmet for Coal Mine Safety

IoT-Enabled Smart Helmet for Coal Mine Worker Safety Using ESP32

The Smart Helmet for Coal Mine Safety is an IoT-based wearable
safety system designed to improve the safety of workers operating in
coal mines and other hazardous industrial environments.

The system integrates environmental monitoring, fall detection, GPS
tracking, automatic lighting, emergency alerts, and real-time web
monitoring into a single wearable helmet platform.

The helmet continuously monitors temperature, humidity, air quality,
light intensity, and worker movement. When hazardous conditions or
abnormal events are detected, the system provides local alerts using a
buzzer and LED indicators while transmitting monitored information
to a web-based dashboard.

📌 Project Overview

Coal mine workers can be exposed to harmful gases, poor visibility,
abnormal temperature and humidity, accidental falls, and difficulties in
locating workers during emergencies.

This project combines multiple sensors with an ESP32 microcontroller
to create a portable safety-monitoring platform.

The system consists of:

ESP32 microcontroller

DHT11 temperature and humidity sensor

MQ135 air-quality/gas sensor

LDR light sensor

MPU6050 accelerometer/gyroscope

NEO-6M GPS module

LED strip for automatic illumination

Buzzer for local warning

Emergency push button

Status LED

Wi-Fi communication

Web monitoring dashboard

3.7 V, 1200 mAh Li-ion battery

The ESP32 acts as the central controller. It collects sensor readings,
checks configured safety thresholds, controls local alerts, processes
GPS information, and transmits information through Wi-Fi.

🎯 Objectives

The main objectives of the project are:

Design a smart helmet for coal mine worker safety.

Monitor temperature and humidity continuously.

Monitor air-quality/gas-level changes.

Detect low-light conditions.

Automatically illuminate the helmet in dark conditions.

Detect sudden motion and possible falls.

Track worker location using GPS.

Provide an emergency push-button mechanism.

Provide local warnings using a buzzer and LED.

Transmit sensor information wirelessly using ESP32 Wi-Fi.

Display sensor information on a web dashboard.

Develop a low-cost, portable and scalable safety prototype.

✨ Features

⛑️ Wearable coal-mine safety system

🌡️ Real-time temperature monitoring

💧 Real-time humidity monitoring

🧪 MQ135 air-quality/gas monitoring

💡 Automatic lighting using LDR

📐 MPU6050-based motion/fall detection

📍 GPS-based location tracking

🚨 Manual emergency button

🔊 Buzzer-based safety warning

💡 LED-based indication and illumination

📡 ESP32 Wi-Fi communication

🌐 Web-based monitoring dashboard

🔋 Portable battery-powered operation

⚡ Real-time sensor processing

🛡️ Multi-parameter safety monitoring

🏭 Project Motivation

Traditional safety helmets mainly provide physical protection and
illumination. They do not normally provide continuous information about
environmental hazards or worker status.

The proposed Smart Helmet adds electronic sensing and communication
capabilities to the helmet.

The intended monitoring concept is:

                  WORKER
                    │
                    ▼
              SMART HELMET
                    │
       ┌────────────┼────────────┐
       │            │            │
       ▼            ▼            ▼
 Environmental    Motion       Location
   Monitoring    Monitoring    Tracking
       │            │            │
       └────────────┼────────────┘
                    ▼
                  ESP32
                    │
             ┌──────┴──────┐
             ▼             ▼
       Local Alerts       Wi-Fi
             │             │
             ▼             ▼
        Worker Alert   Web Dashboard

📸 Project Environment

The project report includes an illustrative coal-mine environment
representing the intended application area.



🔧 Hardware Used

Component                 Quantity Purpose

ESP32                            1 Main controller and Wi-Fi communication
DHT11                            1 Temperature and humidity monitoring
MQ135                            1 Air-quality/gas monitoring
LDR                              1 Light-intensity detection
MPU6050                          1 Motion and fall detection
NEO-6M GPS                       1 Worker location tracking
LED Strip                        1 Automatic illumination
Buzzer                           1 Audible safety alert
Emergency Push Button            1 Manual emergency alert
Toggle Switches                  2 System control/mode selection
Status LED                       1 System status indication
Li-ion Battery                   1 Portable power supply
Safety Helmet                    1 Wearable platform
Connecting Wires                - Electrical connections

🧠 System Architecture

The complete Smart Helmet system follows the architecture below:



                    SMART HELMET
                         │
                         ▼
                  ┌─────────────┐
                  │    ESP32    │
                  │ Controller  │
                  └──────┬──────┘
                         │
      ┌──────────────────┼──────────────────┐
      │                  │                  │
      ▼                  ▼                  ▼
 Environmental         Motion             GPS
    Sensors            Sensor           Module
      │                  │                  │
 ┌────┼────┐             │                  │
 ▼    ▼    ▼             ▼                  ▼
DHT11 MQ135 LDR        MPU6050            NEO-6M
 │     │    │             │                  │
 └─────┴────┴─────────────┴──────────────────┘
                         │
                         ▼
                  Sensor Processing
                         │
                         ▼
                  Safety Evaluation
                         │
             ┌───────────┼───────────┐
             ▼           ▼           ▼
          Buzzer        LED       Wi-Fi
             │           │           │
             └───────────┴───────────┘
                                     │
                                     ▼
                              Web Dashboard

🔌 Pin Configuration

Sensor Pins

Sensor / Device     ESP32 GPIO Function

MQ135                  GPIO 34 Analog gas input
DHT11                  GPIO 25 Temperature/humidity data
LDR                    GPIO 35 Analog light input
MPU6050 SDA            GPIO 21 I²C SDA
MPU6050 SCL            GPIO 22 I²C SCL

GPS

GPS Signal     ESP32 GPIO

GPS RX            GPIO 16
GPS TX            GPIO 17

Control Pins

Device               ESP32 GPIO

LED Strip               GPIO 27
Buzzer                  GPIO 26
Emergency Button        GPIO 14
Toggle Switch 1         GPIO 13
Toggle Switch 2         GPIO 12
Status LED               GPIO 2

🌡️ Temperature Monitoring

The DHT11 sensor measures the ambient temperature around the worker.

The ESP32 continuously reads the temperature and compares it with the
configured threshold.

The prototype uses:

Temperature Threshold = 35°C

Decision logic:

             DHT11
               │
               ▼
        Temperature Reading
               │
               ▼
          Temperature
             > 35°C ?
           /         \
         YES          NO
          │            │
          ▼            ▼
       ALERT         NORMAL
          │
          ▼
   Buzzer / LED / Dashboard

💧 Humidity Monitoring

The DHT11 also measures relative humidity.

The configured prototype limits are:

Low Humidity  < 30%
High Humidity > 80%

                  HUMIDITY
                     │
                     ▼
              Read DHT11 Value
                     │
                     ▼
             30% ≤ H ≤ 80% ?
                /        \
              YES         NO
               │           │
               ▼           ▼
            NORMAL        ALERT

🧪 MQ135 Air-Quality / Gas Monitoring

The MQ135 provides an analog signal that is read by the ESP32.

The prototype uses:

MQ135 Threshold = 400

The monitoring process is:

                  MQ135
                    │
                    ▼
             Analog Gas Value
                    │
                    ▼
                > 400 ?
               /      \
             YES       NO
              │         │
              ▼         ▼
           GAS ALERT   NORMAL
              │
        ┌─────┴─────┐
        ▼           ▼
      BUZZER       LED

The MQ135 is used as a prototype air-quality/gas indicator. Accurate gas
concentration measurement requires appropriate sensor calibration and
gas-specific sensing methods.

💡 LDR Light Detection

The LDR is used to determine the surrounding light condition.

The implemented dark-condition threshold is:

LDR Dark Threshold = 1000

For the implemented circuit:

LDR Value > 1000
       │
       ▼
Dark Condition
       │
       ▼
LED Strip ON

When the surrounding condition is sufficiently bright, the illumination
can remain OFF.

🔦 Automatic Helmet Illumination

Automatic illumination is one of the important features of the Smart
Helmet.

                    LDR
                     │
                     ▼
              Light Detection
                     │
                     ▼
              Dark Condition?
                /          \
              YES           NO
               │             │
               ▼             ▼
            LED ON          LED OFF

This feature is useful in low-light environments and underground working
areas.

📐 MPU6050 Motion Monitoring

The MPU6050 provides accelerometer and gyroscope measurements.

The accelerometer measures:

X-axis acceleration

Y-axis acceleration

Z-axis acceleration

The overall acceleration magnitude is calculated using:

A = √(Ax² + Ay² + Az²)

The prototype uses a fall threshold of approximately:

2.5 g

🧍 Fall Detection

The fall-detection sequence is:

                 MPU6050
                    │
                    ▼
             Acceleration Data
                    │
                    ▼
        Calculate Acceleration Magnitude
                    │
                    ▼
                 > 2.5 g ?
                 /       \
               YES        NO
                │          │
                ▼          ▼
           FALL ALERT    NORMAL
                │
          ┌─────┴─────┐
          ▼           ▼
        BUZZER       LED

The current implementation is a threshold-based prototype method.
Further validation and signal-processing/ML techniques can be
investigated for robust fall classification.

📍 GPS Location Tracking

A NEO-6M GPS module is used to track the worker's location.

The GPS communicates with the ESP32 through UART.

              NEO-6M GPS
                  │
          ┌───────┴───────┐
          │               │
          TX              RX
          │               │
          ▼               ▼
     ESP32 GPIO16    ESP32 GPIO17

The GPS can provide:

Latitude

Longitude

Date

Time

Satellite information

GPS validity

GPS availability can be limited in underground environments.

🚨 Emergency Button

The emergency push button provides a manual method for generating an
emergency condition.

             EMERGENCY BUTTON
                    │
                    ▼
                  ESP32
                    │
                    ▼
             Emergency Status
                    │
          ┌─────────┼─────────┐
          ▼         ▼         ▼
        Buzzer      LED       GPS
          │         │         │
          └─────────┴─────────┘
                    │
                    ▼
              Emergency Alert

The GPS information can be used when a valid location fix is available.

🔊 Buzzer Alert System

The buzzer provides immediate local audible warnings.

The alert system can be activated by conditions such as:

High gas-level reading

High temperature

Abnormal humidity

Fall detection

Emergency button activation

Unsafe Condition
       │
       ▼
   ESP32 Alert
       │
       ▼
     BUZZER
       │
       ▼
 Local Audible Warning

💡 LED Alert System

LEDs are used for:

Status indication

Safety warning

Automatic illumination

The LED strip is also controlled using the LDR-based lighting logic.

📡 ESP32 Wi-Fi Communication

The ESP32 provides built-in Wi-Fi communication.

The communication path is:

Sensors
   │
   ▼
ESP32
   │
   ▼
Data Processing
   │
   ▼
Wi-Fi
   │
   ▼
Web Server / Dashboard
   │
   ▼
Remote Monitoring

The ESP32 collects sensor values, processes them, and transmits the
information to the monitoring interface.

🌐 Web Dashboard

The Smart Helmet uses a web-based dashboard for remote monitoring.

The dashboard is designed to display information such as:

Temperature

Humidity

Gas level

Light condition

Motion/fall status

GPS information

Emergency status

Helmet/LED status



🖥️ Dashboard Monitoring Concept

                  SMART HELMET
                       │
                       ▼
                     ESP32
                       │
                       ▼
                    Wi-Fi
                       │
                       ▼
                Web Dashboard
                       │
       ┌───────────────┼───────────────┐
       │               │               │
       ▼               ▼               ▼
 Environment         Safety          Location
 Monitoring         Monitoring       Monitoring
       │               │               │
       ▼               ▼               ▼
 Temp/Humidity    Fall/Emergency       GPS
 Gas/Light

🔄 Complete Working Principle

The Smart Helmet operates in three major stages:

Stage 1 --- Data Collection

Sensors collect:

Temperature
Humidity
Air Quality
Light
Acceleration
GPS

Stage 2 --- Processing

The ESP32:

Reads Sensor Values
       ↓
Processes Data
       ↓
Checks Thresholds
       ↓
Detects Safety Events

Stage 3 --- Transmission and Alert

Unsafe Condition
       │
       ├────────► Buzzer
       │
       ├────────► LED
       │
       └────────► Web Dashboard

🧠 Safety Decision Algorithm

                       START
                         │
                         ▼
                  Initialize ESP32
                         │
                         ▼
                  Initialize Sensors
                         │
                         ▼
                  Connect to Wi-Fi
                         │
                         ▼
                  Read Sensor Data
                         │
        ┌────────────────┼────────────────┐
        │                │                │
        ▼                ▼                ▼
       DHT11            MQ135            LDR
        │                │                │
        └────────────────┼────────────────┘
                         │
                         ▼
                      MPU6050
                         │
                         ▼
                        GPS
                         │
                         ▼
                  Check Thresholds
                         │
        ┌────────────────┼────────────────┐
        │                │                │
        ▼                ▼                ▼
      Gas?             Temp?            Humidity?
        │                │                │
        └────────────────┼────────────────┘
                         │
                         ▼
                   Check Fall
                         │
                         ▼
                  Check Emergency
                         │
                         ▼
                  Safety Decision
                         │
               ┌─────────┴─────────┐
               ▼                   ▼
            NORMAL               ALERT
                                   │
                         ┌─────────┴─────────┐
                         ▼                   ▼
                       BUZZER               LED
                         │
                         ▼
                   Transmit Data
                         │
                         ▼
                  Web Dashboard
                         │
                         ▼
                       LOOP

📋 Safety Thresholds

Parameter              Threshold

MQ135 Gas Level           > 400
Temperature              > 35°C
Humidity Low              < 30%
Humidity High             > 80%
LDR Dark Detection       > 1000
Fall Detection          > 2.5 g

These values represent the thresholds used in the prototype
implementation.

⏱️ System Timing

Operation                       Interval

Sensor Reading                 2 seconds
GPS Reading                    5 seconds
Dashboard / Display Update     3 seconds

The report also describes transmitting data to the server periodically
and displaying readings on the web dashboard.

🖥️ Software Used

ESP32 Firmware

The ESP32 firmware uses:

Arduino IDE

ESP32 Arduino Core

C/C++

Wire

TinyGPS++

HardwareSerial

Adafruit MPU6050

Adafruit Unified Sensor

DHT

Wi-Fi

Web Dashboard

The web interface uses:

HTML

CSS

JavaScript

The report also identifies HTTP/MQTT-style server communication as part
of the implementation concept and notes that ThingSpeak/Firebase can be
integrated for storage.

📚 Main Libraries

Wire
TinyGPS++
HardwareSerial
Adafruit MPU6050
Adafruit Unified Sensor
DHT
WiFi

🔋 Power Supply

The documented prototype uses:

Battery Type : Li-ion
Voltage      : 3.7 V
Capacity     : 1200 mAh

The battery provides portable power for the ESP32, sensors, GPS and
alert circuitry.

🧪 Testing Methodology

The prototype was tested under simulated mining conditions.

The testing focused on:

Varying light intensity

Varying gas concentration

Temperature monitoring

Humidity monitoring

Fall/motion events

GPS operation

Local alerts

Dashboard updates

📸 Physical Prototype

The completed prototype integrates the electronics onto a safety helmet.



The assembled prototype contains the ESP32, sensors, wiring,
illumination system and supporting electronic components.

💡 Smart Helmet --- Light and Dark Testing

The prototype was tested under both illuminated and dark conditions.



The test demonstrates the automatic lighting concept using the LDR
sensor.

Bright Condition
      ↓
    LDR
      ↓
LED OFF

Dark Condition
      ↓
    LDR
      ↓
LED ON

📊 Results

The developed Smart Helmet prototype demonstrates the integration of
environmental monitoring, motion/fall detection, GPS tracking, automatic
illumination, local alert generation and IoT-based monitoring.

The prototype was tested under simulated mining conditions with varying
light intensity and gas concentration.

🌡️ Temperature Monitoring Result

The DHT11 successfully provides temperature readings to the ESP32.

The system compares the reading with the configured threshold:

Temperature > 35°C
        ↓
Temperature Alert

The information can also be presented through the monitoring dashboard.

💧 Humidity Monitoring Result

The DHT11 provides humidity readings.

The system identifies abnormal humidity when:

Humidity < 30%
       OR
Humidity > 80%

The corresponding condition can be represented as an alert in the
monitoring system.

🧪 Gas Monitoring Result

The MQ135 responds to changes in the surrounding air-quality/gas
condition.

The prototype checks:

MQ135 > 400

When the configured threshold is crossed, the system generates a gas
alert and activates the local warning mechanism.

💡 Automatic Lighting Result

The LDR-based lighting system responds to changes in light intensity.

Light Condition
      │
 ┌────┴─────┐
 ▼          ▼
Bright      Dark
 │           │
 ▼           ▼
LED OFF     LED ON

The report's prototype testing includes photographs of the helmet under
light and dark conditions.

📐 Fall Detection Result

The MPU6050 was integrated for motion and fall monitoring.

The system calculates acceleration magnitude:

A = √(Ax² + Ay² + Az²)

and compares it with the configured threshold:

2.5 g

The report states that the prototype responded to fall conditions during
testing.

📍 GPS Result

The GPS module was integrated to provide worker-location information.

The system can obtain:

Latitude
Longitude
GPS Status
Satellite Information
Date
Time

GPS operation is dependent on availability of a valid GPS signal.

🚨 Emergency Alert Result

The emergency button provides a manual mechanism for triggering an
emergency condition.

Button Pressed
      ↓
ESP32
      ↓
Emergency Status
      ↓
Buzzer + LED
      ↓
GPS Information

🌐 Web Dashboard Result

The dashboard provides remote visibility of the sensor information.

The report states that:

The dashboard displayed updates within approximately 2--3 seconds of
data transmission.

The dashboard provides a centralized interface for monitoring the Smart
Helmet.



📊 Overall Results Table

Feature                       Result

ESP32 Controller              ✅ Implemented
Temperature Monitoring        ✅ Implemented
Humidity Monitoring           ✅ Implemented
MQ135 Gas Monitoring          ✅ Implemented
LDR Light Detection           ✅ Implemented
Automatic Lighting            ✅ Demonstrated
MPU6050 Motion Monitoring     ✅ Implemented
Fall Detection                ✅ Implemented
GPS Tracking                  ✅ Implemented
Emergency Button              ✅ Implemented
Buzzer Alert                  ✅ Implemented
LED Alert                     ✅ Implemented
Wi-Fi Communication           ✅ Implemented
Web Dashboard                 ✅ Demonstrated
Physical Helmet Prototype     ✅ Completed
Simulated Condition Testing   ✅ Completed

📈 Results and Discussion

The Smart Helmet demonstrates how multiple sensing and communication
functions can be integrated into a wearable industrial safety system.

Environmental Monitoring

The DHT11, MQ135 and LDR provide information about temperature,
humidity, air-quality/gas level and surrounding light.

Automatic Illumination

The LDR allows the system to activate the LED illumination under dark
conditions.

Motion and Fall Monitoring

The MPU6050 provides acceleration data that is used by the prototype
fall-detection algorithm.

Location Tracking

The NEO-6M GPS provides location information when a valid GPS signal is
available.

Local Alerts

The buzzer and LED provide immediate local warnings when unsafe
conditions are detected.

Remote Monitoring

The ESP32 Wi-Fi capability allows monitored information to be
transmitted to a web dashboard.

The project report states that the prototype responded to variations in
gas concentration, light and falls and that dashboard updates were
displayed within approximately 2--3 seconds of data transmission.

🧪 Testing Summary

Test                    Expected Behavior       Prototype Observation

Temperature             Detect high temperature Alert logic implemented

Humidity                Detect abnormal         Alert logic implemented
humidity

Gas                     Detect threshold        Gas response observed
crossing

Light                   Detect dark condition   Automatic lighting
demonstrated

Fall                    Detect significant      Fall response
acceleration            implemented

GPS                     Obtain location         GPS integrated

Emergency Button        Trigger emergency state Emergency logic
implemented

Dashboard               Display sensor data     Updates demonstrated

🏗️ Prototype Implementation

The complete prototype combines:

                  SMART HELMET
                       │
       ┌───────────────┼────────────────┐
       │               │                │
       ▼               ▼                ▼
 Environmental       Safety           Location
   Monitoring        Monitoring       Tracking
       │               │                │
       ▼               ▼                ▼
 DHT11/MQ135/LDR     MPU6050           GPS
       │               │                │
       └───────────────┼────────────────┘
                       ▼
                     ESP32
                       │
             ┌─────────┴─────────┐
             ▼                   ▼
        Local Alerts          Wi-Fi
             │                   │
       ┌─────┴─────┐             ▼
       ▼           ▼        Web Dashboard
     Buzzer        LED

📸 Complete Prototype Gallery

Assembled Helmet



Light and Dark Demonstration



Web Dashboard



System Block Diagram



System Flowchart



🏭 Applications

The Smart Helmet concept can be applied to:

Coal mine worker safety

Underground tunnel worker safety

Oil refineries

Chemical industries

Construction sites

High-risk industrial zones

Firefighter safety

Disaster management

Hazardous-environment monitoring

The project report specifically identifies coal mines/tunnels, oil
refineries and chemical industries, construction/high-risk zones, and
firefighter/rescue operations as application areas.

⚠️ Limitations

1. Wi-Fi Connectivity

Wi-Fi signals may become unreliable in deep underground mining
environments.

2. GPS Availability

GPS operation can be difficult underground because satellite signals may
not be available.

3. Limited Battery Backup

The current battery capacity limits long-duration operation.

4. Gas Sensor Calibration

The MQ135 requires proper calibration for accurate gas detection.

5. No GSM in Current Version

The current prototype does not include GSM communication.

6. Prototype-Level Fall Detection

The current fall-detection approach is threshold-based and would require
further validation for reliable real-world deployment.

🚀 Future Scope

The project can be extended in several directions.

1. GSM Communication

GSM can be integrated for communication where Wi-Fi is unavailable.

Smart Helmet
     │
     ▼
   ESP32
     │
     ▼
    GSM
     │
     ▼
Mobile Network
     │
     ▼
Supervisor

2. LoRa Communication

LoRa can be investigated for long-range communication in underground
environments.

Helmet 1 ──┐
Helmet 2 ──┤
Helmet 3 ──┼──► LoRa Gateway
Helmet 4 ──┤
Helmet N ──┘
                  │
                  ▼
             Monitoring
                System

3. Solar Charging

A solar charging system can be added to extend battery operating time.

4. AI-Based Predictive Hazard Analysis

Machine learning can be used to analyze sensor trends and predict
potentially hazardous conditions.

Possible inputs:

Temperature
Humidity
Gas Level
Acceleration
Light
Historical Sensor Data

Possible outputs:

SAFE
WARNING
DANGER
EMERGENCY

5. Mobile Application

A mobile application can provide:

Real-time sensor monitoring

Emergency notifications

GPS information

Worker status

Historical sensor data

Multiple-worker monitoring

6. Cloud Monitoring

The system can be extended to store sensor data in a cloud platform.

Smart Helmet
      │
      ▼
    ESP32
      │
      ▼
    Wi-Fi
      │
      ▼
 Cloud Platform
      │
      ├────► Web Dashboard
      │
      └────► Mobile Application

7. Improved Fall Detection

Future versions can combine:

Accelerometer

Gyroscope

Signal processing

Feature extraction

Machine learning

to improve fall-event classification.

8. Advanced Gas Detection

Future versions can use dedicated gas sensors for specific mining
hazards such as:

Methane

Carbon monoxide

Hydrogen sulfide

Other hazardous gases

This can provide more meaningful gas-specific measurements.

🛠️ Development Workflow

Problem Identification
        │
        ▼
Coal Mine Safety Analysis
        │
        ▼
System Architecture
        │
        ▼
Component Selection
        │
        ▼
ESP32 Development
        │
        ▼
Sensor Integration
        │
        ▼
Safety Algorithm
        │
        ▼
Alert System
        │
        ▼
Wi-Fi Communication
        │
        ▼
Web Dashboard
        │
        ▼
Helmet Assembly
        │
        ▼
Prototype Testing
        │
        ▼
Results Analysis
        │
        ▼
Future Enhancement

💻 Software Architecture

                  ESP32 FIRMWARE
                       │
                       ▼
                  INITIALIZATION
                       │
                       ▼
                  SENSOR READING
                       │
       ┌───────────────┼───────────────┐
       │               │               │
       ▼               ▼               ▼
     DHT11            MQ135            LDR
       │               │               │
       └───────────────┼───────────────┘
                       │
                       ▼
                    MPU6050
                       │
                       ▼
                      GPS
                       │
                       ▼
                 DATA PROCESSING
                       │
                       ▼
                 SAFETY DECISION
                       │
             ┌─────────┴─────────┐
             ▼                   ▼
          NORMAL                ALERT
                                 │
                           ┌─────┴─────┐
                           ▼           ▼
                         BUZZER       LED
                           │
                           ▼
                       Wi-Fi Data
                           │
                           ▼
                    Web Dashboard

📊 System Parameters

Parameter                                Value

ESP32 Serial Baud Rate                  115200
GPS Baud Rate                             9600
MQ135 Threshold                            400
Temperature Threshold                     35°C
Humidity Low Threshold                     30%
Humidity High Threshold                    80%
LDR Dark Threshold                        1000
Fall Threshold                           2.5 g
Sensor Reading Interval              2 seconds
GPS Reading Interval                 5 seconds
Dashboard Update Interval            3 seconds
Battery                       3.7 V / 1200 mAh

📁 Project Structure

Smart-Helmet-Coal-Mine-Safety/
│
├── ESP code/
│   └── Smart_Helmet.ino
│
├── Images/
│   ├── 01_coal_mine_environment.jpg
│   ├── 02_system_block_diagram.jpg
│   ├── 03_system_flowchart.jpg
│   ├── 04_assembled_smart_helmet.png
│   ├── 05_helmet_light_and_dark.png
│   └── 06_web_dashboard.jpg
│
├── README.md
│
└── project_report.pdf

⚙️ Setup

1. Install Arduino IDE

Install the Arduino IDE on your computer.

2. Install ESP32 Board Support

Install the ESP32 board package through the Arduino IDE Board Manager.

3. Install Required Libraries

Install:

DHT sensor library
Adafruit Unified Sensor
Adafruit MPU6050
TinyGPSPlus

4. Connect Hardware

Connect the sensors according to the pin configuration provided in this
README.

5. Configure Wi-Fi

Enter your own Wi-Fi credentials in the firmware.

const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

Do not upload real passwords or API keys to a public repository.

6. Select ESP32 Board

In Arduino IDE:

Tools → Board → ESP32

Select the appropriate ESP32 board.

7. Select COM Port

Connect the ESP32 and select its COM port.

8. Upload Firmware

Upload the Smart Helmet firmware.

9. Open Serial Monitor

Use:

115200 baud

to observe initialization and sensor information.

📜 Firmware Logic

The firmware performs:

Initialize
   ↓
DHT11
MQ135
LDR
MPU6050
GPS
   ↓
Read Sensors
   ↓
Process Data
   ↓
Check Thresholds
   ↓
Generate Alerts
   ↓
Control LED/Buzzer
   ↓
Transmit Data
   ↓
Update Dashboard
   ↓
Repeat

📚 Documentation

The complete technical documentation is available in:

project_report.pdf

The report contains:

Abstract

Introduction

Problem statement

Objectives

Scope

Literature review

Comparative analysis

Research gap

System design

Block diagram

Working principle

Circuit information

Flowchart

Hardware description

Software description

Algorithm

Testing environment

Results and discussion

Applications

Limitations

Conclusion

Future scope

References

ESP32 code appendix

📑 Report Results

According to the project report, the prototype was tested under
simulated mining conditions with varying light intensity and gas
concentration.

The report states that:

The system responded to variations in gas concentration.

The system responded to changes in light conditions.

The system responded to fall events.

The dashboard displayed updates within approximately 2--3 seconds of
data transmission.

The buzzer and LED provided local warnings.

🏆 Project Outcome

The project demonstrates a complete IoT-based wearable safety-monitoring
prototype.

The final system integrates:

Environmental Monitoring
        +
Motion / Fall Detection
        +
GPS Tracking
        +
Automatic Lighting
        +
Emergency Alert
        +
Wi-Fi Communication
        +
Web Monitoring

The project demonstrates the feasibility of combining multiple sensors
with an ESP32 to create a portable industrial safety system.

📌 Project Highlights

An IoT-enabled Smart Helmet that combines DHT11, MQ135, LDR, MPU6050
and NEO-6M GPS with ESP32 processing, automatic illumination, local
safety alerts and web-based real-time monitoring for coal mine worker
safety.

🛡️ Safety Disclaimer

This project is an academic and research prototype.

It should not be considered a certified replacement for industrial
mining safety equipment, certified gas-detection systems, mine
communication systems, or regulated emergency-response equipment.

Real-world deployment would require extensive calibration, environmental
testing, reliability testing, communication validation, battery and
enclosure qualification, and appropriate industrial certification.

🧑‍💻 Technologies Used

ESP32

Arduino IDE

C/C++

DHT11

MQ135

LDR

MPU6050

NEO-6M GPS

Wi-Fi

HTML

CSS

JavaScript

IoT

Embedded Systems

Wearable Electronics

Environmental Monitoring

Fall Detection

GPS Tracking

🔑 Keywords

Smart Helmet
Coal Mine Safety
IoT
ESP32
DHT11
MQ135
LDR
MPU6050
GPS
NEO-6M
Fall Detection
Environmental Monitoring
Worker Safety
Industrial IoT
Wearable Electronics
Wi-Fi Monitoring
Web Dashboard
Emergency Alert
Automatic Lighting

📚 References

R. S. Shinde, M. B. Patil, and A. P. Rane, "IoT Based Smart Helmet
for Coal Mine Safety," IEEE International Conference on Intelligent
Computing and Control Systems (ICICCS), Madurai, India,
pp. 987--992, Jun. 2021.

P. K. Sahu and S. K. Singh, "Real-Time Environmental Monitoring for
Underground Mines Using IoT," IEEE Access, vol. 9,
pp. 113245--113255, 2021.

A. Kumar, R. Gupta, and S. Verma, "Design and Implementation of an
IoT-Enabled Safety Helmet for Industrial Workers," IEEE Sensors
Journal, vol. 22, no. 14, pp. 14376--14384, Jul. 2022.

📄 Project Information

Project: Smart Helmet for Coal Mine Worker Safety

Controller: ESP32

Domain: IoT / Embedded Systems / Industrial Safety / Wearable
Electronics

Primary Application: Coal Mine Worker Safety

Communication: Wi-Fi

Monitoring: Web Dashboard

Power: 3.7 V, 1200 mAh Li-ion Battery

⭐ Final Summary

The Smart Helmet for Coal Mine Safety demonstrates an IoT-enabled
wearable approach to industrial worker protection.

The system combines environmental sensing, motion monitoring, GPS
tracking, automatic illumination, emergency input, local alerts and
wireless monitoring into a single ESP32-based platform.

The prototype successfully demonstrates:

✔ Temperature Monitoring
✔ Humidity Monitoring
✔ Gas/Air-Quality Monitoring
✔ Light Detection
✔ Automatic Illumination
✔ Fall Detection
✔ GPS Tracking
✔ Emergency Button
✔ Buzzer Alerts
✔ LED Alerts
✔ ESP32 Wi-Fi Communication
✔ Web Dashboard
✔ Physical Smart Helmet Prototype
✔ Simulated Safety Testing

The project provides a foundation for future improvements such as
GSM/LoRa communication, solar charging, AI-based predictive hazard
analysis, cloud monitoring, mobile applications, advanced gas sensing
and improved fall-detection algorithms.

⛑️ Smart Helmet for Safer Mining

       SENSE
         ↓
       PROCESS
         ↓
       DETECT
         ↓
       ALERT
         ↓
       TRANSMIT
         ↓
       MONITOR

IoT + Embedded Systems + Wearable Electronics + Industrial Safety
