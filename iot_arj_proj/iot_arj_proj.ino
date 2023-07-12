#include <WiFi.h>
#include "time.h"

// I2C
#include <Wire.h>

// MAX30100
#include "MAX30100_PulseOximeter.h"

// MPU6050
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

// Arduino Cloud
//#include "thingProperties.h"
#include <ArduinoIoTCloud.h>
// MAX30100
#define REPORTING_PERIOD_MS 100
PulseOximeter pox;
uint32_t tsLastReport = 0;
void onBeatDetected() {
  Serial.println("Beat!");
}

// MPU6050
Adafruit_MPU6050 mpu;

// Variables to be created in arduino cloud
float heartRate;
int oxyPer;
float accx;
float accy;
float accz;
float gyrx;
float gyry;
float gyrz;
float tem;
void initProperties() {
  //ArduinoCloud.setThingId("");
  //ArduinoCloud.addProperty(accx, READ, ON_CHANGE);
  //ArduinoCloud.addProperty(accy, READ, ON_CHANGE);
  //ArduinoCloud.addProperty(accz, READ, ON_CHANGE);
  //ArduinoCloud.addProperty(gyrx, READ, ON_CHANGE);
  // ArduinoCloud.addProperty(gyry, READ, ON_CHANGE);
  // ArduinoCloud.addProperty(gyrz, READ, ON_CHANGE);
  ArduinoCloud.addProperty(heartRate, READ, ON_CHANGE);
  ArduinoCloud.addProperty(oxyPer, READ, ON_CHANGE);
  // ArduinoCloud.addProperty(tem, READ, ON_CHANGE);
}

// WiFiConnectionHandler ArduinoIoTPreferredConnection("c7dcabd1-2183-40ea-be4d-cf6a69dd66f6", "SRRVYOAQULUCERVRBMR1");
void setup() {
  Serial.begin(9600);
  Wire.begin();

  /*// Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();*/

  // MPU6050
  while (!Serial)
    delay(10);  // will pause Zero, Leonardo, etc until serial console opens

  /*Serial.println("Adafruit MPU6050 test!");
  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
      if(mpu.begin()) {
        break;
      }
    }
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  Serial.print("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange()) {
    case MPU6050_RANGE_2_G:
      Serial.println("+-2G");
      break;
    case MPU6050_RANGE_4_G:
      Serial.println("+-4G");
      break;
    case MPU6050_RANGE_8_G:
      Serial.println("+-8G");
      break;
    case MPU6050_RANGE_16_G:
      Serial.println("+-16G");
      break;
  }
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  Serial.print("Gyro range set to: ");
  switch (mpu.getGyroRange()) {
    case MPU6050_RANGE_250_DEG:
      Serial.println("+- 250 deg/s");
      break;
    case MPU6050_RANGE_500_DEG:
      Serial.println("+- 500 deg/s");
      break;
    case MPU6050_RANGE_1000_DEG:
      Serial.println("+- 1000 deg/s");
      break;
    case MPU6050_RANGE_2000_DEG:
      Serial.println("+- 2000 deg/s");
      break;
  }

  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);
  Serial.print("Filter bandwidth set to: ");
  switch (mpu.getFilterBandwidth()) {
    case MPU6050_BAND_260_HZ:
      Serial.println("260 Hz");
      break;
    case MPU6050_BAND_184_HZ:
      Serial.println("184 Hz");
      break;
    case MPU6050_BAND_94_HZ:
      Serial.println("94 Hz");
      break;
    case MPU6050_BAND_44_HZ:
      Serial.println("44 Hz");
      break;
    case MPU6050_BAND_21_HZ:
      Serial.println("21 Hz");
      break;
    case MPU6050_BAND_10_HZ:
      Serial.println("10 Hz");
      break;
    case MPU6050_BAND_5_HZ:
      Serial.println("5 Hz");
      break;
  }

  Serial.println("");
  delay(100);*/

  // MAX30100
  if (!pox.begin()) {
    Serial.println("FAILED");
    while(1) {
      delay(10);
      if(pox.begin()) {
        break;
      }
    }
  }
  Serial.println("SUCCESS POX");
  pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);
  pox.setOnBeatDetectedCallback(onBeatDetected);
}

void loop() {
  // ArduinoCloud.update();
  // Time
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    // return;
  } else {
    char timeWeekDay[100];
    strftime(timeWeekDay, 100, "%d %B %Y, %H:%M:%S", &timeinfo);
  }

  // MAX30100
  if (pox.begin()) {
    pox.update();
    if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
      heartRate = pox.getHeartRate();
      oxyPer = pox.getSpO2();
      Serial.print("Heart rate:");
      Serial.print(heartRate);
      Serial.print("bpm / SpO2:");
      Serial.print(oxyPer);
      Serial.println("%");
      tsLastReport = millis();
    }
  }

  /*// MPU6050
  if (mpu.begin(0x68)) {
    sensors_event_t a, g, temp;
    accx = a.acceleration.x;
    accy = a.acceleration.y;
    accz = a.acceleration.z;
    gyrx = g.gyro.x;
    gyry = g.gyro.y;
    gyrz = g.gyro.z;
    tem = temp.temperature;
    mpu.getEvent(&a, &g, &temp);

    Serial.print("Acceleration X: ");
    Serial.print(accx);
    Serial.print(", Y: ");
    Serial.print(accy);
    Serial.print(", Z: ");
    Serial.print(accz);
    Serial.println(" m/s^2");

    Serial.print("Rotation X: ");
    Serial.print(gyrx);
    Serial.print(", Y: ");
    Serial.print(gyry);
    Serial.print(", Z: ");
    Serial.print(gyrz);
    Serial.println(" rad/s");

    Serial.print("Temperature: ");
    Serial.print(tem);
    Serial.println(" degC");
    Serial.println("");
  }*/
  delay(500);
}

/*
  Since HeartRate is READ_WRITE variable, onHeartRateChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onHeartRateChange() {
  // Add your code here to act upon HeartRate change
}

/*
  Since OxyPer is READ_WRITE variable, onOxyPerChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onOxyPerChange() {
  // Add your code here to act upon OxyPer change
}
