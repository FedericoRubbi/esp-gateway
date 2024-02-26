#include "Sensor.h"

Sensor::Sensor(RestClient* client) : client(client) {
}

void Sensor::begin() {
  pinMode(SENSOR_LIGHT_PIN, INPUT);
  lastSendTime = millis();
  lastReadTime = millis();
}

int Sensor::readBrightness() {
  brightness = analogRead(SENSOR_LIGHT_PIN);
  return brightness;
}

float Sensor::readTemperature() {
  // TODO: update temperature
  return temperature;
}

float Sensor::readHumidity() {
  // TODO: update humidity
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
  Serial.println("Sending sensor data...");
  String response;
  client->setContentType(SENSOR_CONTENT_TYPE);
  int s = client->post("", formatData(), &response);
  Serial.print("Response: ");
  Serial.println(response);
}

void Sensor::loop() {
  // Read sensor every SENSOR_READ_INTERVAL milliseconds.
  if (millis() - lastReadTime > SENSOR_READ_INTERVAL)
    readBrightness();
    readTemperature();
    readHumidity();
    readVolume();
    lastReadTime = millis();
  // Send data every SENSOR_SEND_INTERVAL milliseconds.
  if (millis() - lastSendTime > SENSOR_SEND_INTERVAL)
    sendData();
    lastSendTime = millis();
}