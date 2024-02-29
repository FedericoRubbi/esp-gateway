#include "Sensor.h"
#include "Adafruit_AHTX0.h"
#include <PrettyDebug.h>

Sensor::Sensor(RestClient* client) : client(client) {
}

void Sensor::begin() {
  if (!aht.begin()) {
    DEBUG_ERROR("Could not find a valid AHT sensor, check wiring!");
    while (1)
      ;
  }
  DEBUG_OK("AHT sensor found!");
  aht_temp = aht.getTemperatureSensor();
  aht_temp->printSensorDetails();
  aht_humidity = aht.getHumiditySensor();
  aht_humidity->printSensorDetails();
  pinMode(SENSOR_LIGHT_PIN, INPUT);
  lastSendTime = millis();
  lastReadTime = millis();
}

int Sensor::readBrightness() {
  brightness = analogRead(SENSOR_LIGHT_PIN);
  return brightness;
}

float Sensor::readTemperature() {
  sensors_event_t event;
  aht_temp->getEvent(&event);
  temperature = event.temperature;
  return temperature;
}

float Sensor::readHumidity() {
  sensors_event_t event;
  aht_humidity->getEvent(&event);
  humidity = event.relative_humidity;
  return humidity;
}

int Sensor::readVolume() {
  // TODO: update volume
  return volume;
}

String Sensor::formatData() {
  return "{\"temperature\": " + String(temperature) + ", \"humidity\": " + String(humidity) +
         ", \"audio\": " + String(volume) + ", \"light\": " + String(brightness) + "}";
}

void Sensor::sendData() {
  DEBUG_OK("Sending sensor data...");
  String response;
  client->setContentType(SENSOR_CONTENT_TYPE);
  int s = client->post("", formatData(), &response);
  if (s >= 200 && s < 300) {
    DEBUG_ERROR("Error sending data to server: %d", s);
    DEBUG_ERROR("Response: %s", response);
  }
  else {
    DEBUG_OK("Response status code: %d", s);
    DEBUG_OK("Response: %s", response);
    DEBUG_OK("Data sent successfully!");
  }
}

void Sensor::loop() {
  // Read sensor every SENSOR_READ_INTERVAL milliseconds.
  if (millis() - lastReadTime > SENSOR_READ_INTERVAL) {
    DEBUG_OK("Reading sensor data...");
    readBrightness();
    DEBUG_VARIABLE(brightness, "%d");
    readTemperature();
    DEBUG_VARIABLE(temperature, "%f");
    readHumidity();
    DEBUG_VARIABLE(humidity, "%f");
    readVolume();
    DEBUG_VARIABLE(volume, "%d");
    lastReadTime = millis();
  }
  // Send data every SENSOR_SEND_INTERVAL milliseconds.
  if (millis() - lastSendTime > SENSOR_SEND_INTERVAL) {
    DEBUG_OK("Sending sensor data...");
    sendData();
    lastSendTime = millis();
  }
}