#include <ESP8266React.h>
#include <RestClient.h>
#include <Sensor.h>
#include <PrettyDebug.h>

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
  ATTACH_DEBUG_STREAM(&Serial);
  DEBUG_OK("Serial debug stream attached");
  esp8266React.begin();  // TODO: change demo project
  DEBUG_OK("ESP8266React initialized");
  server.begin();
  DEBUG_OK("Server initialized");
  sensor.begin();
  DEBUG_OK("Sensor initialized");
}

void loop() {
  esp8266React.loop();
  sensor.loop();
}