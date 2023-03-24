#include <SPI.h>
#include <mcp_can.h>
#include <mcp_can_dfs.h>

const int SPI_CS_PIN = 10; // set the chip select pin
MCP_CAN CAN(SPI_CS_PIN);   // create a CAN object
unsigned long rxId;
unsigned char len = 0;
unsigned char rxBuf[8];

void setup() {
  Serial.begin(9600);     // initialize serial communication
  while (!Serial) {
    ;                     // wait for serial port to connect
  }

  // initialize MCP2515 shield
  if (CAN_OK == CAN.begin(MCP_STDEXT, CAN_500KBPS, MCP_8MHZ)) {
    Serial.println("MCP2515 Initialized Successfully!");
  } else {
    Serial.println("Error Initializing MCP2515...");
    delay(100);
    return;
  }

  // set MCP2515 to normal mode
  CAN.setMode(MCP_NORMAL);
}

void loop() {
  // read engine RPM
  float rpm = readRPM();
  Serial.print("Engine RPM: ");
  Serial.println(rpm);

  // read engine temperature
  float temp = readTemperature();
  Serial.print("Engine Temperature: ");
  Serial.println(temp);

  // read total distance traveled
  float distance = readDistance();
  Serial.print("Total Distance Traveled: ");
  Serial.println(distance);

  delay(1000);
}

float readRPM() {
  if (CAN_MSGAVAIL == CAN.checkReceive()) {
    CAN.readMsgBuf(&rxId, &len, rxBuf); // read CAN message

    // extract RPM data from CAN message
    int rpm_high = rxBuf[3] << 8;
    int rpm_low = rxBuf[4];
    float rpm = (rpm_high | rpm_low) / 4.0;

    return rpm;
  }
}

float readTemperature() {
  if (CAN_MSGAVAIL == CAN.checkReceive()) {
    CAN.readMsgBuf(&rxId, &len, rxBuf); // read CAN message

    // extract temperature data from CAN message
    float temp = rxBuf[4] - 40;

    return temp;
  }
}

float readDistance() {
  if (CAN_MSGAVAIL == CAN.checkReceive()) {
    CAN.readMsgBuf(&rxId, &len, rxBuf); // read CAN message

    // extract distance data from CAN message
    int distance_high = rxBuf[1] << 24;
    int distance_mid_high = rxBuf[2] << 16;
    int distance_mid_low = rxBuf[3] << 8;
    int distance_low = rxBuf[4];
    float distance = (distance_high | distance_mid_high | distance_mid_low | distance_low) / 1000.0;

    return distance;
  }
}
