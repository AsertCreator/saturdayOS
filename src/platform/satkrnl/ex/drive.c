#include "../hals/include/device.h"

BlockDeviceObject* boot_drive_device;
BlockDeviceObject* system_drive_device;
BlockDeviceObject* user_drive_device;

void DriveMgrInitialize() {
	DriveMgrRescanDrives();
}
void DriveMgrRescanDrives() {

}