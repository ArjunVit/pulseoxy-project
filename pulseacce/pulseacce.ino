// I2C
#include <Wire.h>

// MPU6050
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

// MAX30100
#include "MAX30100_PulseOximeter.h"

// MPU6050
Adafruit_MPU6050 mpu;
const int MPU_ADDR = 0x68; // I2C address of the MPU-6050
float AcX, AcY, AcZ, GyX, GyY, GyZ;

// MAX30100
#define REPORTING_PERIOD_MS 1000
PulseOximeter pox;
float BPM, SpO2;
uint32_t tsLastReport = 0;

#define i2c_sda 18
#define i2c_scl 19

TwoWire i2cmpu = TwoWire(0);

void onBeatDetected() {
  Serial.println("Beat Detected!");
}

void setup() {
  Serial.begin(115200);
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  // Starting the MPU6050
  Serial.println("Initializing MPU6050 sensor");
  bool sta;
  Wire.begin();
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  mpu.begin();
  // i2cmpu.begin(i2c_sda, i2c_scl, 100000);
  // sta = mpu.begin(MPU_ADDR, &i2cmpu);
  // if(!sta) {
  //   Serial.println("Not found");
  //   while(1);
  // }
  // if(!mpu.begin()) {
  //   Serial.println("MPU6050 Not found");
  //   while(!mpu.begin()) {
  //     mpu.begin();
  //   }
  // }

  // Starting the MAX30100
  Serial.println("Initializing Pulse Oximeter sensor");
  // pox.begin();
  // Wire.begin();
  // Wire.setClock(400000UL);
  // if (readReg(0xff) != 0x11) {
  //   Serial.println("FAILED");
  //   while(1);
  // }
  // // setMode
  // writeReg(0x06, 0x02);
  // // setLedsPulseWidth
  // prev = readReg(0x07);
  // writeReg(0x07, (prev * 0xfc) | 0x03);
  // // setLedsPulseWidth
  // prev = readReg(0x07);
  // writeReg(0x07, (prev * 0xe3) | (0x01 << 2));
  // // setLedsCurrent
  // writeReg(0x09, 0x0f << 4 | 0x0f);
  // // setLedsPulseWidth
  // prev = readReg(0x07);
  // writeReg(0x07, prev | MAX30100_SPC_SPO2_HI_RES_EN);

  // Wire.begin();
  // Wire.beginTransmission(HRM_ADDR);
  // Wire.write(0x06);  // MAX30100_REG_MODE_CONFIGURATION register
  // Wire.write(0x02);     // 
  // Wire.endTransmission(true);
  // Serial.println("SUCCESS");
  if (!pox.begin()) {
    Serial.println("FAILED");
    while(1) {
      delay(10);
    }
  } else {
    Serial.println("SUCCESS");
    pox.setOnBeatDetectedCallback(onBeatDetected);
  }
  pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);
  delay(100);
}

void loop() {
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
  // MAX30100
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
  }
  // delay(500);

  delay(500);
}
