#pragma once
#include "../../include/system.h"

#define FILE_SHARE_READ 0
#define FILE_SHARE_WRITE 1
#define FILE_SHARE_DEL 2

#define FILE_ACCESS_READ 0
#define FILE_ACCESS_READWRITE 1

#define FILE_QUERY_FILESIZE 0
#define FILE_QUERY_READONLY 1
#define FILE_QUERY_ENCRYPTED 2
#define FILE_QUERY_PERMTABLE 3

struct tagFileObject;

typedef status (*FileObjectRead)(struct tagFileObject* /*this*/, uint8_t* /*buf*/, uint64_t /*start*/, uint64_t /*len*/);
typedef status (*FileObjectWrite)(struct tagFileObject* /*this*/, uint8_t* /*buf*/, uint64_t /*start*/, uint64_t /*len*/);
typedef status (*FileObjectClose)(struct tagFileObject* /*this*/);
typedef status (*FileObjectDelete)(struct tagFileObject* /*this*/);
typedef status (*FileObjectQuery)(struct tagFileObject* /*this*/, int /*what*/, int* /*out*/);

// FileObject "<-" SystemObject
typedef struct tagFileObject {
	uint64_t fid;
	const char* path;
	FileObjectRead read;
	FileObjectWrite write;
	FileObjectClose close;
	FileObjectDelete del;
	FileObjectQuery query;
	struct tagFileObject* next;
} FileObject;

extern uint64_t file_next_fid;
extern FileObject file_null;
extern FileObject* file_first;
extern FileObject* file_last;

bool ExIsValidFilePath(const char* path);
FileObject ExCreateNullFile();
FileObject* ExOpenFile(const char* path, int share);
void ExDeleteFile(FileObject* fobj);
void ExCloseFile(FileObject* fobj);
void ExReadFile(FileObject* fobj, uint8_t* buf, uint64_t start, uint64_t len);
void ExWriteFile(FileObject* fobj, uint8_t* buf, uint64_t start, uint64_t len);