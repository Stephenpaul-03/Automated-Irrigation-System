#include <Wire.h>
#include <RTClib.h> // Library for RTC module

const int moistureSensorPin = A0; // Soil moisture sensor pin
const int relayPin = 7;           // Relay control pin

const int dryThreshold = 400;     // Moisture level considered dry
const int wetThreshold = 700;     // Moisture level considered wet

RTC_DS3231 rtc;                   // RTC object
const int wateringHour = 6;       // Scheduled watering time: 6:00 AM
const unsigned long wateringDuration = 120000; // Max watering time: 2 minutes
const unsigned long hourlyCheckInterval = 3600000; // Check every hour (1 hour in milliseconds)

bool isWatering = false;
unsigned long wateringStartTime = 0;
unsigned long lastCheckTime = 0;

void setup() {
  pinMode(moistureSensorPin, INPUT);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);

  Serial.begin(9600);
  if (!rtc.begin() || rtc.lostPower()) {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // Set RTC to compile time
  }

  lastCheckTime = millis(); // Initialize the last check time
}

void loop() {
  DateTime now = rtc.now(); // Get current time

  // Scheduled watering at 6:00 AM
  if (now.hour() == wateringHour && now.minute() == 0 && !isWatering) {
    startWatering();
  }

  // Hourly moisture check
  if (millis() - lastCheckTime >= hourlyCheckInterval) {
    lastCheckTime = millis();
    checkMoisture();
  }

  if (isWatering) {
    continueWatering();
  }

  delay(1000);
}

void checkMoisture() {
  int moistureLevel = analogRead(moistureSensorPin);
  Serial.print("Hourly Check - Moisture Level: ");
  Serial.println(moistureLevel);

  if (moistureLevel < dryThreshold) {
    Serial.println("Soil is dry. Starting watering...");
    startWatering();
  } else {
    Serial.println("Soil moisture is sufficient.");
  }
}

void startWatering() {
  digitalWrite(relayPin, HIGH); // Turn on pump
  isWatering = true;
  wateringStartTime = millis();
}

void continueWatering() {
  int moistureLevel = analogRead(moistureSensorPin);
  if (moistureLevel >= wetThreshold || millis() - wateringStartTime >= wateringDuration) {
    stopWatering();
  }
}

void stopWatering() {
  digitalWrite(relayPin, LOW); // Turn off pump
  isWatering = false;
  Serial.println("Watering completed.");
}
