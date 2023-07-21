#pragma once
#include "../../include/system.h"

#define COM_PORT1 (uint16_t)0x03F8

typedef uint8_t(*serial_port_read)(uint8_t num);
typedef void(*serial_port_write)(uint8_t num, uint8_t val);

typedef struct tagSerialPort {
	uint8_t num;
	serial_port_read read;
	serial_port_write write;
	struct tagSerialPort* next;
} SerialPort;

extern SerialPort* serial_first;
extern SerialPort* serial_last;
extern int serial_port_count;

void HALSetupSerialPorts();
void HALWriteSerialPortString(const char* str, SerialPort* port);
SerialPort* HALGetSerialPortNumbered(uint8_t num);