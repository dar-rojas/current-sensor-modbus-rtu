/**
 * @file main.cpp
 * @author Dario Rojas
 * @brief Reads data from a current sensor and makes it available over Modbus RTU
 * @version 0.1
 * @date 2025-08-06
 * 
 */

#include <ArduinoRS485.h>
#include <ArduinoModbus.h>

int analogPin0 = A0;
int voltageRead = 0; /// voltage read from current sensor
uint16_t current;

void setup() {

  /// integrated user led
  pinMode(LED_BUILTIN, OUTPUT);

  /// start the Modbus RTU client
  /// @note baudrate: 19200, parity: even, 8 bits 1 stop bit
  if (!ModbusRTUServer.begin(20, 19200, SERIAL_8E1)) {
    while (1);
    digitalWrite(LED_BUILTIN, HIGH);
  }
  if (!ModbusRTUServer.configureHoldingRegisters(0x00, 1)) {
    while (1);
    digitalWrite(LED_BUILTIN, HIGH);
  }
}

void loop() {
  voltageRead = analogRead(analogPin0);
  current = round((voltageRead / 1023.0)*1000); // current in dA
  
  ModbusRTUServer.holdingRegisterWrite(0, uint16_t(current));
  ModbusRTUServer.poll();
}