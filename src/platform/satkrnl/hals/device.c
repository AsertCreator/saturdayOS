#include "include/device.h"
#include "include/nulldev.h"

DeviceBaseObject* first_device;
uint32_t device_count = 1;
uint32_t next_dynmid = 0;

void DevMgrInitialize() {
	SystemDeviceObject* nulldev = (SystemDeviceObject*)HeapAlloc(&system_heap, sizeof(SystemDeviceObject));
	nulldev->next = (DeviceBaseObject*)nulldev;
	nulldev->pc_deviceid = 0;
	nulldev->pc_vendorid = 0;
	nulldev->dynmid = next_dynmid++;
	nulldev->start = NullDevStart;
	nulldev->stop = NullDevStop;
	nulldev->get_precise_device_type = NullDevPreciseDeviceType;
	first_device = (DeviceBaseObject*)nulldev;

	DriveMgrInitialize();
}
void DevMgrStopAllDevices() {
	DeviceBaseObject* dev = first_device;
	for (size_t i = 0; i < device_count; i++) {
		dev->stop(dev);
		dev = dev->next;
	}
}
DeviceBaseObject* DevMgrGetDeviceByDynmID(uint32_t dynmid) {
	DeviceBaseObject* dev = first_device;
	for (size_t i = 0; i < device_count; i++) {
		if (dev->dynmid == dynmid) return dev;
		dev = dev->next;
	}
	return 0;
}
DeviceBaseObject* DevMgrGetDeviceOfType(uint32_t type, int n) {
	DeviceBaseObject* dev = first_device;
	int j = 0;
	for (size_t i = 0; i < device_count; i++) {
		if (dev->devtype == type && j == n) return dev;
		if (dev->devtype == type) j++;
		dev = dev->next;
	}
	return 0;
}
void DevMgrAppendDevice(DeviceBaseObject* after, DeviceBaseObject* which) {
	DeviceBaseObject* dev = first_device;
	for (size_t i = 0; i < device_count; i++) {
		if (dev->dynmid == after->dynmid) {
			DeviceBaseObject* next = dev->next;
			dev->next = which;
			which->next = next;
			which->dynmid = next_dynmid++;
			device_count++;
			return;
		}
		dev = dev->next;
	}
}