#pragma once
#include "../../include/system.h"

bool StdStringSame(const char* str, const char* str2);
bool StdStringContains(const char* str, const char* find);
size_t StdStringLength(const char* str);
void StdStringConcat(const char* str0, const char* str1, char* dst);
void StdStringReverse(char* str, int len);
char* StdIntToString(int num, char* str, int base);
char* StdLongToString(int64_t num, char* str, int base);