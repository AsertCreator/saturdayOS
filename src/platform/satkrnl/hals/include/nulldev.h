#pragma once
#include "../../include/system.h"

/*
	nulldev - system device
*/

#define NULL_DEV_TYPE -1

status NullDevStart(DeviceBaseObject* dev);
status NullDevStop(DeviceBaseObject* dev);
status NullDevPing(DeviceBaseObject* dev);
status NullDevPreciseDeviceType(DeviceBaseObject* dev, int* out);