#include <Arduino.h>
#include <Wire.h>

#define I2C_SLAVE_ADDRESS 0x42

#define CMD_GET_DATA                0x00
#define CMD_GET_ALL_DATA            0x01
#define CMD_SET_TIME                0x02
#define CMD_GET_TIME                0x03
#define CMD_GET_UNIT                0x04
#define CMD_GET_VERSION             0x05

String mockSpeed = "12.5";
String mockDir = "NW";
String mockTemp = "25.3";
String mockHumi = "60.2";
String mockPressure = "1013.25";
String mockUnitSpeed = "km/h";
String mockUnitTemp = "C";
String mockUnitHumi = "%";
String mockUnitPressure = "hPa";

// Handle incoming I2C commands
void onReceive(int numBytes) {
  if (numBytes > 0) {
    byte command = Wire.read(); // Read the command byte
    Serial.print("Received Command: ");
    Serial.println(command, HEX);

    switch (command) {
      case CMD_GET_DATA:
        // Return a specific data (mock example)
        Wire.write(mockSpeed.c_str());
        Serial.println("Sent Speed Data");
        break;
      case CMD_GET_ALL_DATA:
        // Return all data as a concatenated string (mock example)
        Wire.write((mockSpeed + "," + mockDir + "," + mockTemp + "," + mockHumi + "," + mockPressure).c_str());
        Serial.println("Sent All Sensor Data");
        break;
      case CMD_GET_TIME:
        // Return a mock timestamp
        Wire.write("2024-08-16 12:34:56");
        Serial.println("Sent Timestamp Data");
        break;
      case CMD_GET_UNIT:
        // Return mock units (could be based on previous data requested)
        Wire.write((mockUnitSpeed + "," + mockUnitTemp + "," + mockUnitHumi + "," + mockUnitPressure).c_str());
        Serial.println("Sent Unit Data");
        break;
      case CMD_GET_VERSION:
        // Return a mock version
        Wire.write("LARK 1.0");
        Serial.println("Sent Version Data");
        break;
      default:
        // Handle unknown commands
        Wire.write("UNKNOWN");
        Serial.println("Sent UNKNOWN for unrecognized command");
        break;
    }
  }
}

// Handle I2C master data requests
void onRequest() {
  // Data response handled in onReceive based on command
}



void setup() {
  Wire.begin(I2C_SLAVE_ADDRESS); // Initialize I2C as a slave device
  Wire.onRequest(onRequest); // Register a callback function for when data is requested
  Wire.onReceive(onReceive); // Register a callback function for when data is received
  Serial.begin(115200);
  Serial.println("I2C Slave Device Ready to Emulate LARK Hardware");
}

void loop() {
  // No need to do anything here, everything is handled by interrupts
}
