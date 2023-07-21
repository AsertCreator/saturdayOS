#pragma once
#include "../../include/system.h"

enum PciDeviceClass {
	PCI_CLASS_UNCLASSIFIED                  = (uint8_t)0x00,
	PCI_CLASS_MASS_STORAGE_CONTROLLER       = (uint8_t)0x01,
	PCI_CLASS_NETWORK_CONTROLLER            = (uint8_t)0x02,
	PCI_CLASS_DISPLAY_CONTROLLER            = (uint8_t)0x03,
	PCI_CLASS_MULTIMEDIA_CONTROLLER         = (uint8_t)0x04,
	PCI_CLASS_MEMORY_CONTROLLER             = (uint8_t)0x05,
	PCI_CLASS_BRIDGE                        = (uint8_t)0x06,
	PCI_CLASS_SIMPLE_COMMS_CONTROLLER       = (uint8_t)0x07,
	PCI_CLASS_BASE_SYSTEM_PERIPHERAL        = (uint8_t)0x08,
	PCI_CLASS_INPUT_DEVICE_CONTROLLER       = (uint8_t)0x09,
	PCI_CLASS_DOCKING_STATION               = (uint8_t)0x0A,
	PCI_CLASS_CENTRAL_PROCESSING_UNIT       = (uint8_t)0x0B,
	PCI_CLASS_SERIAL_BUS_CONTROLLER         = (uint8_t)0x0C,
	PCI_CLASS_WIRELESS_CONTROLLER           = (uint8_t)0x0D,
	PCI_CLASS_INTELLIGENT_CONTROLLER        = (uint8_t)0x0E,
	PCI_CLASS_SATELLITE_COMMS_CONTROLLER    = (uint8_t)0x0F,
	PCI_CLASS_ENCRYPTION_CONTROLLER         = (uint8_t)0x10,
	PCI_CLASS_SIGNAL_PROCESSING_CONTROLLER  = (uint8_t)0x11,
	PCI_CLASS_PROCESSING_ACCELERATOR        = (uint8_t)0x12,
	PCI_CLASS_NON_ESSENTIAL_INSTRUMENTATION = (uint8_t)0x13,
	PCI_CLASS_CO_PROCESSOR                  = (uint8_t)0x40
};

uint16_t HALPciConfigReadWord(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset);
uint16_t HALPciCheckVendorId(uint8_t bus, uint8_t slot, uint8_t func);
uint16_t HALPciCheckDeviceId(uint8_t bus, uint8_t slot, uint8_t func);
uint8_t HALPciGetDeviceClass(uint8_t bus, uint8_t slot, uint8_t func);
uint8_t HALPciGetDeviceSubclass(uint8_t bus, uint8_t slot, uint8_t func);
uint8_t HALPciGetDeviceHeaderType(uint8_t bus, uint8_t slot, uint8_t func);
uint8_t HALPciGetDeviceSecondaryBus(uint8_t bus, uint8_t slot, uint8_t func);
void HALPciScanEverything();
void HALPciScanBus(uint8_t bus);
void HALPciScanDevice(uint8_t bus, uint8_t device);
void HALPciScanFunction(uint8_t bus, uint8_t device, uint8_t function);