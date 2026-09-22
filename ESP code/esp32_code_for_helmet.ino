/*
  ================================================================
             SMART HELMET FOR COAL MINE WORKER SAFETY
  ================================================================

  Controller : ESP32

  Sensors:
    - DHT11       : Temperature & Humidity
    - MQ135       : Air Quality / Gas Level
    - LDR         : Light Intensity
    - MPU6050     : Motion / Fall Detection
    - NEO-6M GPS  : Worker Location

  Outputs:
    - LED / LED Strip
    - Buzzer
    - Emergency Alert
    - Web Dashboard

  Communication:
    - Wi-Fi
    - ESP32 Web Server

  ================================================================
*/

// ========================= LIBRARIES ============================

#include <WiFi.h>
#include <WebServer.h>
#include <Wire.h>
#include <DHT.h>
#include <TinyGPS++.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

// ========================= WIFI SETTINGS ========================

// Change these according to your Wi-Fi
const char* WIFI_SSID = "YOUR_WIFI_NAME";
const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";

// ========================= PIN DEFINITIONS ======================

// DHT11
#define DHT_PIN 25
#define DHT_TYPE DHT11

// MQ135
#define MQ135_PIN 34

// LDR
#define LDR_PIN 35

// LED / LED STRIP
#define LED_PIN 27

// Buzzer
#define BUZZER_PIN 26

// Emergency Button
#define EMERGENCY_BUTTON_PIN 14

// GPS
#define GPS_RX_PIN 16
#define GPS_TX_PIN 17

// MPU6050 uses I2C
#define MPU_SDA 21
#define MPU_SCL 22

// ========================= OBJECTS ==============================

DHT dht(DHT_PIN, DHT_TYPE);

TinyGPSPlus gps;

HardwareSerial GPS_Serial(1);

Adafruit_MPU6050 mpu;

WebServer server(80);

// ========================= SENSOR DATA ==========================

float temperature = 0.0;
float humidity = 0.0;

int gasLevel = 0;
int lightLevel = 0;

float accelX = 0.0;
float accelY = 0.0;
float accelZ = 0.0;

float totalAcceleration = 0.0;

double latitude = 0.0;
double longitude = 0.0;

int satellites = 0;

// ========================= STATUS VARIABLES =====================

bool fallDetected = false;
bool gasAlert = false;
bool temperatureAlert = false;
bool humidityAlert = false;
bool darkEnvironment = false;

bool emergencyAlert = false;

bool ledStripState = false;

// ========================= THRESHOLDS ===========================

// Gas threshold
const int GAS_THRESHOLD = 400;

// Temperature threshold
const float TEMPERATURE_THRESHOLD = 35.0;

// Humidity limits
const float HUMIDITY_MIN = 30.0;
const float HUMIDITY_MAX = 80.0;

// LDR threshold
const int DARK_THRESHOLD = 1000;

// Fall threshold in g
const float FALL_THRESHOLD = 2.5;

// ========================= TIMING ===============================

unsigned long lastSensorRead = 0;
unsigned long lastGPSRead = 0;

const unsigned long SENSOR_INTERVAL = 2000;
const unsigned long GPS_INTERVAL = 5000;

// ========================= FUNCTION DECLARATIONS ================

void readSensors();
void readGPS();
void checkSafetyConditions();
void controlSafetyOutputs();

void handleRoot();
void handleData();
void handleToggleLED();
void handleEmergency();

String getSafetyStatus();


// =================================================================
//                         SETUP
// =================================================================

void setup()
{
  Serial.begin(115200);

  delay(1000);

  Serial.println();
  Serial.println("========================================");
  Serial.println("       SMART HELMET SYSTEM");
  Serial.println("========================================");

  // ---------------- GPIO SETUP ----------------

  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(EMERGENCY_BUTTON_PIN, INPUT_PULLUP);

  digitalWrite(LED_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);

  // ---------------- DHT11 ----------------

  dht.begin();

  Serial.println("DHT11 initialized");

  // ---------------- MPU6050 ----------------

  Wire.begin(MPU_SDA, MPU_SCL);

  if (!mpu.begin())
  {
    Serial.println("ERROR: MPU6050 not detected!");
  }
  else
  {
    Serial.println("MPU6050 initialized");

    mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
    mpu.setGyroRange(MPU6050_RANGE_500_DEG);

    mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  }

  // ---------------- GPS ----------------

  GPS_Serial.begin(
    9600,
    SERIAL_8N1,
    GPS_RX_PIN,
    GPS_TX_PIN
  );

  Serial.println("GPS initialized");

  // ---------------- WIFI ----------------

  WiFi.mode(WIFI_STA);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.print("Connecting to Wi-Fi");

  unsigned long wifiStart = millis();

  while (WiFi.status() != WL_CONNECTED &&
         millis() - wifiStart < 20000)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println();

  if (WiFi.status() == WL_CONNECTED)
  {
    Serial.println("Wi-Fi connected!");

    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
  }
  else
  {
    Serial.println("Wi-Fi connection failed.");
    Serial.println("Starting Access Point mode...");

    WiFi.mode(WIFI_AP);

    WiFi.softAP(
      "SmartHelmet",
      "12345678"
    );

    Serial.print("AP IP Address: ");
    Serial.println(WiFi.softAPIP());
  }

  // ---------------- WEB SERVER ----------------

  server.on("/", HTTP_GET, handleRoot);

  server.on("/api/data", HTTP_GET, handleData);

  server.on("/toggleLED", HTTP_GET, handleToggleLED);

  server.on("/emergency", HTTP_GET, handleEmergency);

  server.begin();

  Serial.println("Web server started");

  Serial.println("----------------------------------------");
  Serial.println("SMART HELMET READY");
  Serial.println("----------------------------------------");
}


// =================================================================
//                         MAIN LOOP
// =================================================================

void loop()
{
  server.handleClient();

  // Read GPS continuously
  readGPS();

  // Read sensors periodically
  if (millis() - lastSensorRead >= SENSOR_INTERVAL)
  {
    lastSensorRead = millis();

    readSensors();

    checkSafetyConditions();

    controlSafetyOutputs();

    // Print data to Serial Monitor
    Serial.println();
    Serial.println("------------- SENSOR DATA -------------");

    Serial.print("Temperature : ");
    Serial.print(temperature);
    Serial.println(" °C");

    Serial.print("Humidity    : ");
    Serial.print(humidity);
    Serial.println(" %");

    Serial.print("Gas Level   : ");
    Serial.println(gasLevel);

    Serial.print("Light Level : ");
    Serial.println(lightLevel);

    Serial.print("Acceleration: ");
    Serial.print(totalAcceleration);
    Serial.println(" g");

    Serial.print("GPS Latitude: ");
    Serial.println(latitude, 6);

    Serial.print("GPS Longitude: ");
    Serial.println(longitude, 6);

    Serial.print("Satellites  : ");
    Serial.println(satellites);

    Serial.print("Safety      : ");
    Serial.println(getSafetyStatus());

    Serial.println("----------------------------------------");
  }

  // Emergency button
  if (digitalRead(EMERGENCY_BUTTON_PIN) == LOW)
  {
    emergencyAlert = true;

    digitalWrite(BUZZER_PIN, HIGH);

    Serial.println("!!! EMERGENCY BUTTON PRESSED !!!");

    delay(300);

    digitalWrite(BUZZER_PIN, LOW);
  }
}


// =================================================================
//                     READ ALL SENSORS
// =================================================================

void readSensors()
{
  // ==============================================================
  // DHT11
  // ==============================================================

  float newTemperature = dht.readTemperature();
  float newHumidity = dht.readHumidity();

  if (!isnan(newTemperature))
  {
    temperature = newTemperature;
  }

  if (!isnan(newHumidity))
  {
    humidity = newHumidity;
  }

  // ==============================================================
  // MQ135
  // ==============================================================

  gasLevel = analogRead(MQ135_PIN);

  // ==============================================================
  // LDR
  // ==============================================================

  lightLevel = analogRead(LDR_PIN);

  // ==============================================================
  // MPU6050
  // ==============================================================

  sensors_event_t acceleration;
  sensors_event_t gyro;
  sensors_event_t temperatureEvent;

  if (mpu.begin())
  {
    mpu.getEvent(
      &acceleration,
      &gyro,
      &temperatureEvent
    );

    accelX = acceleration.acceleration.x;
    accelY = acceleration.acceleration.y;
    accelZ = acceleration.acceleration.z;

    /*
      Convert m/s² to g.

      1 g ≈ 9.81 m/s²
    */

    float ax = accelX / 9.81;
    float ay = accelY / 9.81;
    float az = accelZ / 9.81;

    totalAcceleration =
      sqrt(
        ax * ax +
        ay * ay +
        az * az
      );
  }
}


// =================================================================
//                          GPS
// =================================================================

void readGPS()
{
  while (GPS_Serial.available())
  {
    char c = GPS_Serial.read();

    gps.encode(c);
  }

  if (millis() - lastGPSRead >= GPS_INTERVAL)
  {
    lastGPSRead = millis();

    if (gps.location.isValid())
    {
      latitude = gps.location.lat();
      longitude = gps.location.lng();
    }

    if (gps.satellites.isValid())
    {
      satellites = gps.satellites.value();
    }
  }
}


// =================================================================
//                  SAFETY CONDITION CHECKING
// =================================================================

void checkSafetyConditions()
{
  // --------------------------------------------------------------
  // GAS
  // --------------------------------------------------------------

  gasAlert = false;

  if (gasLevel > GAS_THRESHOLD)
  {
    gasAlert = true;
  }

  // --------------------------------------------------------------
  // TEMPERATURE
  // --------------------------------------------------------------

  temperatureAlert = false;

  if (temperature > TEMPERATURE_THRESHOLD)
  {
    temperatureAlert = true;
  }

  // --------------------------------------------------------------
  // HUMIDITY
  // --------------------------------------------------------------

  humidityAlert = false;

  if (
    humidity < HUMIDITY_MIN ||
    humidity > HUMIDITY_MAX
  )
  {
    humidityAlert = true;
  }

  // --------------------------------------------------------------
  // LIGHT
  // --------------------------------------------------------------

  darkEnvironment = false;

  if (lightLevel < DARK_THRESHOLD)
  {
    darkEnvironment = true;
  }

  // --------------------------------------------------------------
  // FALL
  // --------------------------------------------------------------

  fallDetected = false;

  if (totalAcceleration > FALL_THRESHOLD)
  {
    fallDetected = true;
  }
}


// =================================================================
//                    SAFETY OUTPUT CONTROL
// =================================================================

void controlSafetyOutputs()
{
  bool dangerDetected =
    gasAlert ||
    temperatureAlert ||
    humidityAlert ||
    fallDetected ||
    emergencyAlert;

  // --------------------------------------------------------------
  // AUTOMATIC LIGHT CONTROL
  // --------------------------------------------------------------

  if (darkEnvironment)
  {
    digitalWrite(LED_PIN, HIGH);

    ledStripState = true;
  }
  else if (!ledStripState)
  {
    digitalWrite(LED_PIN, LOW);
  }

  // --------------------------------------------------------------
  // SAFETY ALERT
  // --------------------------------------------------------------

  if (dangerDetected)
  {
    digitalWrite(BUZZER_PIN, HIGH);
  }
  else
  {
    digitalWrite(BUZZER_PIN, LOW);
  }
}


// =================================================================
//                     SAFETY STATUS
// =================================================================

String getSafetyStatus()
{
  if (emergencyAlert)
  {
    return "EMERGENCY";
  }

  if (fallDetected)
  {
    return "FALL DETECTED";
  }

  if (gasAlert)
  {
    return "HIGH GAS";
  }

  if (temperatureAlert)
  {
    return "HIGH TEMPERATURE";
  }

  if (humidityAlert)
  {
    return "ABNORMAL HUMIDITY";
  }

  if (darkEnvironment)
  {
    return "DARK ENVIRONMENT";
  }

  return "NORMAL";
}


// =================================================================
//                       WEB DASHBOARD
// =================================================================

void handleRoot()
{
  String html = R"rawliteral(

<!DOCTYPE html>

<html>

<head>

<meta name="viewport"
      content="width=device-width, initial-scale=1">

<title>Smart Helmet Dashboard</title>

<style>

body
{
  font-family: Arial, sans-serif;
  background: #111827;
  color: white;
  margin: 0;
  padding: 15px;
}

.container
{
  max-width: 600px;
  margin: auto;
}

h1
{
  text-align: center;
  color: #ffffff;
}

.subtitle
{
  text-align: center;
  color: #9ca3af;
  margin-bottom: 20px;
}

.card
{
  background: #1f2937;
  border-radius: 12px;
  padding: 18px;
  margin-bottom: 12px;
  box-shadow: 0 3px 10px rgba(0,0,0,0.3);
}

.title
{
  font-size: 16px;
  color: #9ca3af;
}

.value
{
  font-size: 28px;
  font-weight: bold;
  margin-top: 5px;
}

.status
{
  display: inline-block;
  padding: 5px 10px;
  border-radius: 15px;
  margin-top: 8px;
  font-size: 13px;
}

.normal
{
  background: #166534;
}

.warning
{
  background: #92400e;
}

.danger
{
  background: #991b1b;
}

button
{
  width: 100%;
  padding: 15px;
  margin-top: 10px;
  border: none;
  border-radius: 8px;
  color: white;
  font-size: 16px;
  cursor: pointer;
}

.emergency
{
  background: #dc2626;
}

.led
{
  background: #0891b2;
}

.gps
{
  background: #374151;
  min-height: 100px;
  border-radius: 8px;
  padding: 10px;
}

.small
{
  color: #9ca3af;
  font-size: 13px;
}

</style>

</head>


<body>

<div class="container">

<h1>⛑️ Smart Helmet Dashboard</h1>

<div class="subtitle">
Real-Time Coal Mine Safety Monitoring System
</div>


<!-- TEMPERATURE -->

<div class="card">

<div class="title">
🌡️ Temperature
</div>

<div class="value">
<span id="temperature">--</span> °C
</div>

<div id="temperatureStatus"
     class="status normal">
Normal
</div>

</div>


<!-- HUMIDITY -->

<div class="card">

<div class="title">
💧 Humidity
</div>

<div class="value">
<span id="humidity">--</span> %
</div>

<div id="humidityStatus"
     class="status normal">
Normal
</div>

</div>


<!-- GAS -->

<div class="card">

<div class="title">
⚠️ Gas Level
</div>

<div class="value">
<span id="gas">--</span> ppm
</div>

<div id="gasStatus"
     class="status normal">
Normal
</div>

</div>


<!-- LIGHT -->

<div class="card">

<div class="title">
💡 Light Level
</div>

<div class="value">
<span id="light">--</span>
</div>

<div id="lightStatus"
     class="status normal">
Normal
</div>

</div>


<!-- MOTION -->

<div class="card">

<div class="title">
📐 Motion Sensor
</div>

<div class="value">
<span id="acceleration">--</span> g
</div>

<div id="motionStatus"
     class="status normal">
Normal
</div>

<p class="small">
X: <span id="ax">--</span> m/s²
<br>
Y: <span id="ay">--</span> m/s²
<br>
Z: <span id="az">--</span> m/s²
</p>

</div>


<!-- GPS -->

<div class="card">

<div class="title">
📍 GPS Location
</div>

<p>
Latitude:
<span id="latitude">--</span>
</p>

<p>
Longitude:
<span id="longitude">--</span>
</p>

<p>
Satellites:
<span id="satellites">--</span>
</p>

<div class="gps">
GPS Map View
</div>

</div>


<!-- SYSTEM STATUS -->

<div class="card">

<div class="title">
🛡️ System Safety Status
</div>

<div class="value">
<span id="systemStatus">
NORMAL
</span>
</div>

</div>


<!-- EMERGENCY -->

<button
class="emergency"
onclick="sendEmergency()">

🚨 EMERGENCY ALERT

</button>


<!-- LED -->

<button
class="led"
onclick="toggleLED()">

💡 TOGGLE LED STRIP

</button>


<p
class="small"
style="text-align:center">

Last updated:
<span id="updated">
--

</span>

</p>

</div>


<script>

function updateDashboard()
{

fetch('/api/data')

.then(response => response.json())

.then(data =>
{

document.getElementById(
"temperature"
).innerHTML =
data.temperature.toFixed(1);


document.getElementById(
"humidity"
).innerHTML =
data.humidity.toFixed(1);


document.getElementById(
"gas"
).innerHTML =
data.gas;


document.getElementById(
"light"
).innerHTML =
data.light;


document.getElementById(
"acceleration"
).innerHTML =
data.acceleration.toFixed(2);


document.getElementById(
"ax"
).innerHTML =
data.ax.toFixed(2);


document.getElementById(
"ay"
).innerHTML =
data.ay.toFixed(2);


document.getElementById(
"az"
).innerHTML =
data.az.toFixed(2);


document.getElementById(
"latitude"
).innerHTML =
data.latitude.toFixed(6);


document.getElementById(
"longitude"
).innerHTML =
data.longitude.toFixed(6);


document.getElementById(
"satellites"
).innerHTML =
data.satellites;


document.getElementById(
"systemStatus"
).innerHTML =
data.status;


// Temperature status

let tempStatus =
document.getElementById(
"temperatureStatus"
);

if(data.temperatureAlert)
{
  tempStatus.innerHTML =
  "HIGH TEMPERATURE";

  tempStatus.className =
  "status danger";
}
else
{
  tempStatus.innerHTML =
  "Normal";

  tempStatus.className =
  "status normal";
}


// Humidity status

let humStatus =
document.getElementById(
"humidityStatus"
);

if(data.humidityAlert)
{
  humStatus.innerHTML =
  "ABNORMAL HUMIDITY";

  humStatus.className =
  "status warning";
}
else
{
  humStatus.innerHTML =
  "Normal";

  humStatus.className =
  "status normal";
}


// Gas status

let gasStatus =
document.getElementById(
"gasStatus"
);

if(data.gasAlert)
{
  gasStatus.innerHTML =
  "HIGH GAS LEVEL";

  gasStatus.className =
  "status danger";
}
else
{
  gasStatus.innerHTML =
  "Normal";

  gasStatus.className =
  "status normal";
}


// Light status

let lightStatus =
document.getElementById(
"lightStatus"
);

if(data.dark)
{
  lightStatus.innerHTML =
  "Dark Environment - LED ON";

  lightStatus.className =
  "status warning";
}
else
{
  lightStatus.innerHTML =
  "Normal";

  lightStatus.className =
  "status normal";
}


// Motion status

let motionStatus =
document.getElementById(
"motionStatus"
);

if(data.fall)
{
  motionStatus.innerHTML =
  "FALL DETECTED";

  motionStatus.className =
  "status danger";
}
else
{
  motionStatus.innerHTML =
  "Normal";

  motionStatus.className =
  "status normal";
}


// Emergency status

if(data.emergency)
{
  document.getElementById(
  "systemStatus"
  ).style.color = "#ef4444";
}
else
{
  document.getElementById(
  "systemStatus"
  ).style.color = "white";
}


document.getElementById(
"updated"
).innerHTML =
new Date().toLocaleTimeString();

})

.catch(error =>
{
  console.log(error);
});

}


// ================================================================
// EMERGENCY BUTTON
// ================================================================

function sendEmergency()
{

fetch('/emergency')

.then(response =>
response.text())

.then(data =>
{
  alert(data);
});

}


// ================================================================
// LED BUTTON
// ================================================================

function toggleLED()
{

fetch('/toggleLED')

.then(response =>
response.text())

.then(data =>
{
  alert(data);
});

}


// Update every 2 seconds

setInterval(
updateDashboard,
2000
);

updateDashboard();

</script>

</body>

</html>

)rawliteral";


  server.send(
    200,
    "text/html",
    html
  );
}


// =================================================================
//                       API DATA
// =================================================================

void handleData()
{
  String json = "{";

  json += "\"temperature\":";
  json += String(temperature, 2);

  json += ",";

  json += "\"humidity\":";
  json += String(humidity, 2);

  json += ",";

  json += "\"gas\":";
  json += String(gasLevel);

  json += ",";

  json += "\"light\":";
  json += String(lightLevel);

  json += ",";

  json += "\"ax\":";
  json += String(accelX, 2);

  json += ",";

  json += "\"ay\":";
  json += String(accelY, 2);

  json += ",";

  json += "\"az\":";
  json += String(accelZ, 2);

  json += ",";

  json += "\"acceleration\":";
  json += String(totalAcceleration, 2);

  json += ",";

  json += "\"latitude\":";
  json += String(latitude, 6);

  json += ",";

  json += "\"longitude\":";
  json += String(longitude, 6);

  json += ",";

  json += "\"satellites\":";
  json += String(satellites);

  json += ",";

  json += "\"gasAlert\":";
  json += gasAlert ? "true" : "false";

  json += ",";

  json += "\"temperatureAlert\":";
  json += temperatureAlert ? "true" : "false";

  json += ",";

  json += "\"humidityAlert\":";
  json += humidityAlert ? "true" : "false";

  json += ",";

  json += "\"dark\":";
  json += darkEnvironment ? "true" : "false";

  json += ",";

  json += "\"fall\":";
  json += fallDetected ? "true" : "false";

  json += ",";

  json += "\"emergency\":";
  json += emergencyAlert ? "true" : "false";

  json += ",";

  json += "\"led\":";
  json += ledStripState ? "true" : "false";

  json += ",";

  json += "\"status\":\"";
  json += getSafetyStatus();
  json += "\"";

  json += "}";

  server.send(
    200,
    "application/json",
    json
  );
}


// =================================================================
//                     TOGGLE LED
// =================================================================

void handleToggleLED()
{
  ledStripState = !ledStripState;

  digitalWrite(
    LED_PIN,
    ledStripState ? HIGH : LOW
  );

  String message;

  if (ledStripState)
  {
    message = "LED strip turned ON";
  }
  else
  {
    message = "LED strip turned OFF";
  }

  server.send(
    200,
    "text/plain",
    message
  );
}


// =================================================================
//                     EMERGENCY BUTTON
// =================================================================

void handleEmergency()
{
  emergencyAlert = true;

  digitalWrite(
    BUZZER_PIN,
    HIGH
  );

  delay(1000);

  digitalWrite(
    BUZZER_PIN,
    LOW
  );

  server.send(
    200,
    "text/plain",
    "EMERGENCY ALERT ACTIVATED"
  );
}
