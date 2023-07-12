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
  ArduinoCloud.setThingId("");
  ArduinoCloud.addProperty(accx, READ, ON_CHANGE);
  ArduinoCloud.addProperty(accy, READ, ON_CHANGE);
  ArduinoCloud.addProperty(accz, READ, ON_CHANGE);
  ArduinoCloud.addProperty(gyrx, READ, ON_CHANGE);
  ArduinoCloud.addProperty(gyry, READ, ON_CHANGE);
  ArduinoCloud.addProperty(gyrz, READ, ON_CHANGE);
  ArduinoCloud.addProperty(heartRate, READ, ON_CHANGE);
  ArduinoCloud.addProperty(oxyPer, READ, ON_CHANGE);
  ArduinoCloud.addProperty(tem, READ, ON_CHANGE);
}

WiFiConnectionHandler ArduinoIoTPreferredConnection("","");
