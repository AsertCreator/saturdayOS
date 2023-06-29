#pragma once
#include "../../include/system.h"
#include "../../hals/include/device.h"

extern BlockDeviceObject* boot_drive_device;
extern BlockDeviceObject* system_drive_device;
extern BlockDeviceObject* user_drive_device;

void DriveMgrInitialize();
void DriveMgrRescanDrives();