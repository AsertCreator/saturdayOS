#pragma once
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

// KeyInfo "<-" SystemObject
typedef struct {
	int kbduscode;
	char keychar;
} KeyInfo;

// DeviceBaseObject "<-" SystemObject
typedef struct tag_kernel_device {
	const char* devname;
	uint32_t devtype;
	uint32_t dynmid;
	uint32_t pc_vendorid;
	uint32_t pc_deviceid;
	struct tag_kernel_device* next;
	uint32_t (*start)(struct tag_kernel_device*);
	uint32_t (*stop)(struct tag_kernel_device*);
	uint32_t (*ping)(struct tag_kernel_device*);
} DeviceBaseObject;

// KeyboardDeviceObject <- DeviceBaseObject "<-" SystemObject
typedef struct {
	DeviceBaseObject;

	uint32_t (*is_key_avail)(DeviceBaseObject*, /*out*/ int*); // int* = amount of keys in buffer
	uint32_t (*read_key)(DeviceBaseObject*, /*out*/ KeyInfo*);
} KeyboardDeviceObject;

// BlockDeviceObject <- DeviceBaseObject "<-" SystemObject
typedef struct {
	DeviceBaseObject;

	uint32_t (*get_block_device_id)(DeviceBaseObject*, /*out*/ uint32_t*); // uint32_t* = connection type
	uint32_t (*get_device_type)(DeviceBaseObject*, /*out*/ int*); // int* = block device type
	uint32_t (*get_device_connection_type)(DeviceBaseObject*, /*out*/ int*); // int* = connection type
	uint32_t (*get_block_count)(DeviceBaseObject*, /*out*/ int*); // int* = block count
	uint32_t (*write_block)(DeviceBaseObject*, int, /*out*/ uint8_t*); // uint8_t* = block buffer, int = block number
	uint32_t (*read_block)(DeviceBaseObject*, int, /*out*/ uint8_t*); // uint8_t* = block buffer, int = block number
} BlockDeviceObject;

// MouseDeviceObject <- DeviceBaseObject "<-" SystemObject
typedef struct {
	DeviceBaseObject;

	uint32_t (*get_mouse_position)(DeviceBaseObject*, /*out*/ int*, /*out*/ int*); // int* = x & y respectively
	uint32_t (*get_scroll_delta)(DeviceBaseObject*, /*out*/ int*); // int* = scroll delta
} MouseDeviceObject;

// SystemDeviceObject <- DeviceBaseObject "<-" SystemObject
typedef struct {
	DeviceBaseObject;

	uint32_t(*get_precise_device_type)(DeviceBaseObject*, /*out*/ int*); // int* = type
} SystemDeviceObject;

#include "../../include/system.h"

#define DEVTYPE_GENERAL (uint32_t)0
#define DEVTYPE_KEYBORD (uint32_t)1
#define DEVTYPE_MOUSE   (uint32_t)2
#define DEVTYPE_SYSTEM  (uint32_t)3

#define DEVTYPE_BLOCKDEVICE_RAM (int)0
#define DEVTYPE_BLOCKDEVICE_IDE (int)1

#define DEVTYPE_BLOCKDEVICE_TYPE_DRIVE (int)0
#define DEVTYPE_BLOCKDEVICE_TYPE_CDROM (int)1
#define DEVTYPE_BLOCKDEVICE_TYPE_REMOV (int)2
#define DEVTYPE_BLOCKDEVICE_TYPE_RAMDS (int)3

extern DeviceBaseObject* first_device;
extern KeyboardDeviceObject* primary_keyboard_device;
extern MouseDeviceObject* primary_mouse_device;
extern uint32_t device_count;

void DevMgrInitialize();
void DevMgrStopAllDevices();
DeviceBaseObject* DevMgrGetDeviceByDynmID(uint32_t dynmid);
DeviceBaseObject* DevMgrGetDeviceOfType(uint32_t type, int n);
void DevMgrAppendDevice(DeviceBaseObject* after, DeviceBaseObject* which);
void HALCallFirmwareFunction(int funcnum, uint32_t arg0, uint32_t arg1);