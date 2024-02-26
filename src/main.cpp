#include <ESP8266React.h>
#include <RestClient.h>
#include <Sensor.h>

#define SERIAL_BAUD_RATE 115200
#define SERVER_PORT 80
#define HOST_ADDRESS "nodemcu.cliquesrl.it"
#define HOST_PORT 5000
#define HOST_PROTOCOL "https"
#define HOST_BASE_PATH "/receive/update"

AsyncWebServer server(SERVER_PORT);
ESP8266React esp8266React(&server);
RestClient client(HOST_ADDRESS, HOST_PORT, HOST_PROTOCOL, HOST_BASE_PATH);
Sensor sensor(&client);

void setup() {
  Serial.begin(SERIAL_BAUD_RATE);
  esp8266React.begin();  // TODO: change demo project
  server.begin();
  sensor.begin();
}

void loop() {
  esp8266React.loop();
  sensor.loop();
}