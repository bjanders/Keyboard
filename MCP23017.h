// MCP23017.h

#ifndef _MCP23017_h
#define _MCP23017_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#endif
const int MCP23017_ADDR = 0x20;
const byte MCP23017_IODIRA = 0x00;
const byte MCP23017_IPOLA = 0x02;
const byte MCP23017_GPINTENA = 0x04;
const byte MCP23017_DEFVALA = 0x06;
const byte MCP23017_INTCONA = 0x08;
const byte MCP23017_IOCONA = 0x0A;
const byte MCP23017_GPPUA = 0x0C;
const byte MCP23017_INTFA = 0x0E;
const byte MCP23017_INTCAPA = 0x10;
const byte MCP23017_GPIOA = 0x12;
const byte MCP23017_OLATA = 0x14;


const byte MCP23017_IODIRB = 0x01;
const byte MCP23017_IPOLB = 0x03;
const byte MCP23017_GPINTENB = 0x05;
const byte MCP23017_DEFVALB = 0x07;
const byte MCP23017_INTCONB = 0x09;
const byte MCP23017_IOCONB = 0x0B;
const byte MCP23017_GPPUB = 0x0D;
const byte MCP23017_INTFB = 0x0F;
const byte MCP23017_INTCAPB = 0x11;
const byte MCP23017_GPIOB = 0x13;
const byte MCP23017_OLATB = 0x15;

class MCP23017
{
public:
	MCP23017(int address);
	void writeRegister(byte reg, byte val);
	byte readRegister(byte reg);
private:
	int _address;
};