#include "arduino_secrets.h"
#include <Wire.h>
#include <ConnectionHandlerDefinitions.h>
#include <ConnectionHandlerInterface.h>
#include <WiFiConnectionHandler.h>
#include <WiFi.h>
#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>

#define SLAVE_ADDR 16
#define ANSWERSIZE 12  // Fixed passcode length

const char SSID[] = SECRET_SSID;             // Network SSID
const char PASS[] = SECRET_OPTIONAL_PASS;    // Network password

bool readyToSend = true;  // Flag to indicate when slave is ready
String random_passcode;
WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, PASS);

void initProperties() {
  ArduinoCloud.addProperty(random_passcode, READ, ON_CHANGE, NULL);
}

void setup() {
  Serial.begin(9600);
  delay(1500);  // Allow time for serial monitor to connect

  WiFi.begin(SSID, PASS);

  initProperties();
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  setDebugMessageLevel(4);
  ArduinoCloud.printDebugInfo();

  Wire.begin(SLAVE_ADDR);
  Wire.setClock(50000);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  static unsigned long lastUpdate = 0;
  unsigned long currentMillis = millis();

  ArduinoCloud.update();
  readyToSend = true;
  // Generate a new passcode every hour (3600000 ms) and send it to the cloud
  if (currentMillis - lastUpdate >= 3600000 || lastUpdate == 0) {
    lastUpdate = currentMillis;

    String random_passcode1 = String(random(10000, 99999));
    String random_passcode2 = String(random(10000, 99999));
    String random_passcode3 = String(random(10, 99));
    random_passcode = random_passcode1 + random_passcode2 + random_passcode3;

    Serial.println("Generated passcode: " + random_passcode);
    ArduinoCloud.update();
  }
}

void receiveEvent(int numBytes) {
  while (Wire.available()) {
    char c = Wire.read();
  }
}

void requestEvent() {
  // Ensure that the passcode is properly converted to a byte array
  Wire.write(random_passcode.c_str());  // Send the passcode as bytes
}

void resetI2C() {
  Wire.end();         // End the current I2C session
  delay(50);          // Short delay to avoid bus contention
  Wire.begin(SLAVE_ADDR);  // Reinitialize I2C
}
