#ifndef UTILITY_H
#define UTILITY_H
#include "kernel.hpp"

#define is_letter(c) (c <= 0x5A && c >= 0x41) || (c <= 0x7A && c >= 0x61)
#define is_number(c) (c <= 0x39 && c >= 0x30)

uint32_t findoccurr(const char* str, char f);
size_t strlen(const char* str);
void reverse(char* str, int length);
char* itoa(int num, char* str, int base);
char* ltoa(long num, char* str, int base);
void make_log_block(const char* name);
void make_enable_msg(const char* msg);
void make_error_msg(const char* msg);

#endif