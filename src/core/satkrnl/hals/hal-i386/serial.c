#include "../include/port.h"
#include "../include/serial.h"
#include "../../ex/include/std.h"
#include "../../ex/include/heap.h"

SerialPort* serial_first;
SerialPort* serial_last;
int serial_port_count;

static uint8_t COMPortRead(uint8_t num) {
	NEVER_REFERENCED(num);
	return 0;
}
static void COMPortWrite(uint8_t num, uint8_t val) {
	NEVER_REFERENCED(num);
	while ((HALInputFromPort(COM_PORT1 + 5) & 0x20) == 0);
	HALOutputToPort(COM_PORT1, val);
}
static void COMPortInit(uint16_t port) {
	HALOutputToPort(port + 1, 0x00);
	HALOutputToPort(port + 3, 0x80);
	HALOutputToPort(port + 0, 0x03);
	HALOutputToPort(port + 1, 0x00);
	HALOutputToPort(port + 3, 0x03);
	HALOutputToPort(port + 2, 0xC7);
	HALOutputToPort(port + 4, 0x0B);
	HALOutputToPort(port + 4, 0x1E);
	HALOutputToPort(port + 0, 0xAE);

	if (HALInputFromPort(port + 0) != 0xAE) {
		return;
	}

	HALOutputToPort(port + 4, 0x0F);
	return;
}
void HALSetupSerialPorts() {
	SerialPort* port = (SerialPort*)HeapAlloc(&system_heap, sizeof(SerialPort));

	serial_first = port;
	serial_last = port;

	// com1
	COMPortInit(COM_PORT1);
	port->next = serial_first;
	port->num = 1;
	port->read = COMPortRead;
	port->write = COMPortWrite;
	serial_port_count++;
}
void HALWriteSerialPortString(const char* str, SerialPort* port) {
	int len = StdStringLength(str);
	for (int i = 0; i < len; i++) {
		port->write(port->num, str[i]);
	}
}
SerialPort* HALGetSerialPortNumbered(uint8_t num) {
	SerialPort* port = serial_first;
	for (uint8_t i = 0; i < serial_port_count; i++) {
		if (i == num) return port;
		port = port->next;
	}
	return (SerialPort*)-1;
}