
// I2C
#include <Wire.h>

#include "MAX30100_PulseOximeter.h"
#define REPORTING_PERIOD_MS 1000

PulseOximeter pox;

float BPM, SpO2;
uint32_t tsLastReport = 0;

void onBeatDetected() {
  Serial.println("Beat Detected!");
}

void setup() {
  Serial.begin(115200);
  // Serial.print("Initializing Pulse Oximeter..");
  if (!pox.begin()) {
    // Serial.println("FAILED");
    for (;;)
      ;
  // } else {
    // Serial.println("SUCCESS");
    // pox.setOnBeatDetectedCallback(onBeatDetected);
  }
  pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);
}

void loop() {
  pox.update();
  BPM = pox.getHeartRate();
  SpO2 = pox.getSpO2();
  if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
    // Serial.print("Heart rate:");
    Serial.print(BPM);
    // Serial.print(" bpm / SpO2:");
    Serial.print(" ");
    Serial.println(SpO2);
    // Serial.println(" %");
    tsLastReport = millis();
  }
}