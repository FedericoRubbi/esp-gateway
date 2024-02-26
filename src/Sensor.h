#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>
#include <RestClient.h>

#define SENSOR_LIGHT_PIN A0
#define SENSOR_READ_INTERVAL 1000
#define SENSOR_SEND_INTERVAL 5000
#define SENSOR_CONTENT_TYPE "application/json"

class Sensor {
 private:
  RestClient* client;
  unsigned long lastSendTime;
  unsigned long lastReadTime;
  int brightness;
  float temperature;
  float humidity;
  int volume;

 public:
  Sensor(RestClient* client);
  void begin();
  int readBrightness();
  float readTemperature();
  float readHumidity();
  int readVolume();
  String formatData();
  void sendData();
  void loop();
};

#endif  // SENSOR_H