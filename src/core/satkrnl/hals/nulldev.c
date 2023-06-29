#include "include/nulldev.h"

status NullDevStart(DeviceBaseObject* dev) {
	NEVER_REFERENCED(dev);
	return FAILED_NOTALLW;
}
status NullDevStop(DeviceBaseObject* dev) {
	NEVER_REFERENCED(dev);
	return FAILED_NOTALLW;
}
status NullDevPing(DeviceBaseObject* dev) {
	NEVER_REFERENCED(dev);
	return SUCCESS;
}
status NullDevPreciseDeviceType(DeviceBaseObject* dev, int* out) {
	NEVER_REFERENCED(dev);
	*out = NULL_DEV_TYPE;
	return SUCCESS;
}