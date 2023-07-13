// I2C
#include <Wire.h>

// MPU6050
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

// MPU6050
Adafruit_MPU6050 mpu;
const int MPU_ADDR = 0x68; // I2C address of the MPU-6050
float AcX, AcY, AcZ, GyX, GyY, GyZ;

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
  i2cmpu.begin(i2c_sda, i2c_scl, 100000);
  sta = mpu.begin(MPU_ADDR, &i2cmpu);
  if(!sta) {
    Serial.println("Not found");
    while(1);
  }
  // mpu.begin();
  // if(!mpu.begin()) {
  //   Serial.println("MPU6050 Not found");
  //   while(!mpu.begin()) {
  //     mpu.begin();
  //   }
  // }

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
  delay(500);
}
