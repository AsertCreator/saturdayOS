#include "../include/pci.h"

uint16_t HALPciConfigReadWord(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset) {
    uint32_t address;
    uint32_t lbus = (uint32_t)bus;
    uint32_t lslot = (uint32_t)slot;
    uint32_t lfunc = (uint32_t)func;
    uint16_t tmp = 0;

    address = (uint32_t)((lbus << 16) | (lslot << 11) | (lfunc << 8) | (offset & 0xFC) | ((uint32_t)0x80000000));

    HALOutputToPortDWord(0xCF8, address);

    tmp = (uint16_t)((HALInputFromPortDWord(0xCFC) >> ((offset & 2) * 8)) & 0xFFFF);
    return tmp;
}
uint16_t HALPciCheckVendorId(uint8_t bus, uint8_t slot, uint8_t func) {
    uint16_t vendor;

    if ((vendor = HALPciConfigReadWord(bus, slot, func, 0)) != 0xFFFF)
        return vendor;

    return 0xFFFF;
}
uint16_t HALPciCheckDeviceId(uint8_t bus, uint8_t slot, uint8_t func) {
    uint16_t vendor, device;

    if ((vendor = HALPciConfigReadWord(bus, slot, func, 0)) != 0xFFFF) {
        device = HALPciConfigReadWord(bus, slot, func, 2);
        return device;
    }

    return 0xFFFF;
}
uint8_t HALPciGetDeviceClass(uint8_t bus, uint8_t slot, uint8_t func) {
    return (uint8_t)(HALPciConfigReadWord(bus, slot, func, 0x8) & 0xFF00);
}
uint8_t HALPciGetDeviceSubclass(uint8_t bus, uint8_t slot, uint8_t func) {
    return (uint8_t)(HALPciConfigReadWord(bus, slot, func, 0x7) & 0xFF00);
}
uint8_t HALPciGetDeviceHeaderType(uint8_t bus, uint8_t slot, uint8_t func) {
    return (uint8_t)(HALPciConfigReadWord(bus, slot, func, 0xB) & 0xFF00);
}
uint8_t HALPciGetDeviceSecondaryBus(uint8_t bus, uint8_t slot, uint8_t func) {
    return (uint8_t)(HALPciConfigReadWord(bus, slot, func, 0x16) & 0xFF00);
}
void HALPciScanEverything() {
    uint8_t headerType = HALPciGetDeviceHeaderType(0, 0, 0);
    if ((headerType & 0x80) == 0) {
        HALPciScanBus(0);
    }
    else {
        uint8_t bus;

        // Multiple PCI host controllers
        for (uint8_t function = 0; function < 8; function++) {
            if (HALPciCheckVendorId(0, 0, function) != 0xFFFF) break;
            bus = function;
            HALPciScanBus(bus);
        }
    }
}
void HALPciScanBus(uint8_t bus) {
    for (uint8_t device = 0; device < 32; device++) {
        HALPciScanDevice(bus, device);
    }
    TtyMgrLog(SUCCESS, "pci", "scanned bus %x", (int)bus);
}
void HALPciScanDevice(uint8_t bus, uint8_t device) {
    uint8_t function = 0;
    uint16_t vendorID = HALPciCheckVendorId(bus, device, function);

    if (vendorID == 0xFFFF) return; // Device doesn't exist

    TtyMgrLog(SUCCESS, "pci", "scanning device %x:%x, vendorId %x", (int)bus, (int)HALPciCheckDeviceId(bus, device, 0), (int)vendorID);

    HALPciScanFunction(bus, device, function);

    uint8_t headerType = HALPciGetDeviceHeaderType(bus, device, function);
    if ((headerType & 0x80) != 0) {
        // It's a multi-function device, so check remaining functions
        for (function = 1; function < 8; function++) {
            if (HALPciCheckVendorId(bus, device, function) != 0xFFFF) {
                HALPciScanFunction(bus, device, function);
            }
        }
    }
}
void HALPciScanFunction(uint8_t bus, uint8_t device, uint8_t function) {
    uint8_t baseClass;
    uint8_t subClass;
    uint8_t secondaryBus;

    baseClass = HALPciGetDeviceClass(bus, device, function);
    subClass = HALPciGetDeviceSubclass(bus, device, function);
    if ((baseClass == 0x6) && (subClass == 0x4)) {
        secondaryBus = HALPciGetDeviceSecondaryBus(bus, device, function);
        HALPciScanBus(secondaryBus);
    }

    TtyMgrLog(SUCCESS, "pci", "scanned function %x:%x:%x", (int)bus, (int)HALPciCheckDeviceId(bus, device, function), (int)function);
}