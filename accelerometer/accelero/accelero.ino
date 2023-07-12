// I2C
#include <Wire.h>

// MPU6050
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

// MAX30100
#include "MAX30100_PulseOximeter.h"

#include <WiFi.h>

// MPU6050
Adafruit_MPU6050 mpu;
const int MPU_ADDR = 0x68; // I2C address of the MPU-6050
float AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;

// MAX30100
#define REPORTING_PERIOD_MS 1000
PulseOximeter pox;
float BPM, SpO2;
uint32_t tsLastReport = 0;


void setup() {
  Serial.begin(115200);
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  // Starting the MPU6050
  Serial.println("Initializing MPU6050 sensor");
  mpu.begin();
  // if(!mpu.begin()) {
  //   Serial.println("MPU6050 Not found");
  //   while(1) {
  //     delay(10);
  //   }
  // }

  /*// Starting the MAX30100
  Serial.print("Initializing Pulse Oximeter sensor");
  if (!pox.begin()) {
    Serial.println("FAILED");
    while(1) {
      delay(10);
    }
  }
  Serial.println("SUCCESS");*/
  delay(100);
}

void loop() {
  /*// MAX30100
  pox.update();
  BPM = pox.getHeartRate();
  SpO2 = pox.getSpO2();
  if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
    Serial.print("Heart rate:");
    Serial.print(BPM);
    Serial.print(" bpm / SpO2:");
    Serial.print(SpO2);
    Serial.println(" %");
    tsLastReport = millis();
  }*/

  // MPU6050
  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  AcX = a.acceleration.x;
  AcY = a.acceleration.y;
  AcZ = a.acceleration.z;
  GyX = g.gyro.x;
  GyY = g.gyro.y;
  GyZ = g.gyro.z;
  // Tmp = temp.temperature;

  /* Print out the values */
  Serial.print("Acceleration X: "); Serial.print(AcX); Serial.print(", Y: "); Serial.print(AcY); Serial.print(", Z: "); Serial.print(AcZ); Serial.println(" m/s^2");

  Serial.print("Rotation X: "); Serial.print(GyX); Serial.print(", Y: "); Serial.print(GyY); Serial.print(", Z: "); Serial.print(GyZ); Serial.println(" rad/s");

  // Serial.print("Temperature: "); Serial.print(temp.temperature); Serial.println(" degC");
  Serial.println("");
  delay(1000);
}
