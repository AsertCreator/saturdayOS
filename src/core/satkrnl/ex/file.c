#include "include/file.h"

uint64_t file_next_fid;
FileObject file_null;
FileObject* file_first;
FileObject* file_last;

// null file implementation

status NullFileClose(struct tagFileObject* fo) { 
	NEVER_REFERENCED(fo);
	return FAILED_NOTALLW; 
}
status NullFileDelete(struct tagFileObject* fo) {
	NEVER_REFERENCED(fo);
	return FAILED_NOTALLW; 
}
status NullFileRead(struct tagFileObject* fo, uint8_t* b, uint64_t s, uint64_t sz) {
	NEVER_REFERENCED(fo);
	NEVER_REFERENCED(b);
	NEVER_REFERENCED(s);
	NEVER_REFERENCED(sz);
	return FAILED_NOTALLW; 
}
status NullFileWrite(struct tagFileObject* fo, uint8_t* b, uint64_t s, uint64_t sz) {
	NEVER_REFERENCED(fo);
	NEVER_REFERENCED(b);
	NEVER_REFERENCED(s);
	NEVER_REFERENCED(sz);
	return FAILED_NOTALLW; 
}
status NullFileQuery(struct tagFileObject* fo, int what, int* out) {
	NEVER_REFERENCED(fo);
	switch (what) {
	case FILE_QUERY_FILESIZE:
		*out = 0;
		return SUCCESS;
	case FILE_QUERY_READONLY:
		*out = 1;
		return SUCCESS;
	case FILE_QUERY_ENCRYPTED:
		*out = 0;
		return SUCCESS;
	case FILE_QUERY_PERMTABLE:
		*out = -1;
		return SUCCESS;
	default:
		return FAILED_NOTIMPL;
	}
}

// end of null file implementation

// kargs file implementation

status KernelArgsFileClose(struct tagFileObject* fo) {
	NEVER_REFERENCED(fo);
	return FAILED_NOTALLW; 
}
status KernelArgsFileDelete(struct tagFileObject* fo) {
	NEVER_REFERENCED(fo);
	return FAILED_NOTALLW; 
}
status KernelArgsFileRead(struct tagFileObject* fo, uint8_t* buf, uint64_t start, uint64_t len) {
	NEVER_REFERENCED(fo);

	uint64_t strlen = (uint64_t)StdStringLength(system_cmdline) + 1;
	if (start > strlen || start + len > strlen) return FAILED_NOTALLW;

	for (uint64_t i = start; i < start + len; i++) {
		buf[i] = system_cmdline[i];
	}

	return SUCCESS;
}
status KernelArgsFileWrite(struct tagFileObject* fo, uint8_t* b, uint64_t s, uint64_t sz) {
	NEVER_REFERENCED(fo);
	NEVER_REFERENCED(b);
	NEVER_REFERENCED(s);
	NEVER_REFERENCED(sz);
	return FAILED_NOTALLW; 
}
status KernelArgsFileQuery(struct tagFileObject* fo, int what, int* out) {
	NEVER_REFERENCED(fo);
	switch (what) {
	case FILE_QUERY_FILESIZE:
		*out = StdStringLength(system_cmdline);
		return SUCCESS;
	case FILE_QUERY_READONLY:
		*out = 1;
		return SUCCESS;
	case FILE_QUERY_ENCRYPTED:
		*out = 0;
		return SUCCESS;
	case FILE_QUERY_PERMTABLE:
		*out = -1;
		return SUCCESS;
	default:
		return FAILED_NOTIMPL;
	}
}

// end of kargs file implementation

bool ExIsValidFilePath(const char* path) {
	// todo: make this more efficient

	if (StdStringContains(path, "?::/")) {
		// kernel namespace, sort of

		if (StdStringSame(path, "?::/null")) return true;
		if (StdStringSame(path, "?::/kmod")) return true;
		if (StdStringSame(path, "?::/kargs")) return true;
		if (StdStringSame(path, "?::/kpath")) return true;

		return false;
	}

	// todo: does file exist?
	return false;
}
FileObject ExCreateNullFile() {
	file_null.path = "?::/null";
	file_null.fid = file_next_fid++;
	file_null.close = NullFileClose;
	file_null.del = NullFileDelete;
	file_null.read = NullFileRead;
	file_null.write = NullFileWrite;
	file_null.query = NullFileQuery;
	file_null.next = &file_null;

	return file_null;
}
FileObject* ExOpenFile(const char* path, int share) {
	// i don't like that whole file access thing, i'm 
	// giving control access to libc. kernel already can 
	// automatically block reading or writing, so its 
	// somewhat implemented

	NEVER_REFERENCED(share);

	if (!ExIsValidFilePath(path)) return (FileObject*)0;

	FileObject* obj = (FileObject*)HeapAlloc(&system_heap, sizeof(obj));

	if (StdStringContains(path, "?::/")) {
		// kernel namespace, sort of

		if (StdStringSame(path, "?::/kmod")) {

		}
		if (StdStringSame(path, "?::/kargs")) {
			obj->close = KernelArgsFileClose;
			obj->del = KernelArgsFileDelete;
			obj->read = KernelArgsFileRead;
			obj->write = KernelArgsFileWrite;
			obj->query = KernelArgsFileQuery;
			obj->path = path;
			obj->fid = file_next_fid++;
			obj->next = file_first;
			file_last->next = obj;

			return obj;
		}
		if (StdStringSame(path, "?::/kpath")) {

		}

		HeapFree(&system_heap, obj);
		return (FileObject*)0;
	}

	HeapFree(&system_heap, obj);
	return (FileObject*)0;
}
void ExDeleteFile(FileObject* fobj) {
	fobj->del(fobj);
}
void ExCloseFile(FileObject* fobj) {
	fobj->close(fobj);
}
void ExReadFile(FileObject* fobj, uint8_t* buf, uint64_t start, uint64_t len) {
	fobj->read(fobj, buf, start, len);
}
void ExWriteFile(FileObject* fobj, uint8_t* buf, uint64_t start, uint64_t len) {
	fobj->write(fobj, buf, start, len);
}