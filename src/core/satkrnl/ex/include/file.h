#pragma once
#include "../../include/system.h"

// FileVolumeObject <- SystemObject
typedef struct tagFileVolumeObject {
	SystemObject;

} FileVolumeObject;

// FileSystemObject <- SystemObject
typedef struct tagFileSystemObject {
	SystemObject;

} FileSystemObject;

// FileObject <- SystemObject
typedef struct tagFileObject {
	SystemObject;

	uint64_t fid;
	const char* name;
	char* owner_domain;
	char* owner_user;
	SystemObject* aux_object;
} FileObject;

extern uint64_t file_next_fid;
extern FileObject file_root;

bool ExIsValidFilePath(const char* path);
FileObject ExCreateNullFile();
FileObject* ExOpenFile(const char* path, int share);
void ExDeleteFile(FileObject* fobj);
void ExCloseFile(FileObject* fobj);
void ExReadFile(FileObject* fobj, uint8_t* buf, uint64_t start, uint64_t len);
void ExWriteFile(FileObject* fobj, uint8_t* buf, uint64_t start, uint64_t len);