// 
// 
// 

#include "MCP23017.h"
#include <Wire.h>

MCP23017::MCP23017(int address) {
	_address = address;
}

void MCP23017::writeRegister(byte reg, byte val) {
	Wire.beginTransmission(_address);
	Wire.write(reg);
	Wire.write(val);
	Wire.endTransmission();
}

byte MCP23017::readRegister(byte reg) {
	Wire.beginTransmission(_address);
	Wire.write(reg);
	Wire.endTransmission();
	Wire.requestFrom(_address, 1);
	return Wire.read();
}