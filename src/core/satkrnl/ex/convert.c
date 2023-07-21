#include "include/convert.h"

bool StdStringSame(const char* str, const char* str2) {
    int len = StdStringLength(str);
    for (int i = 0; i < len; i++)
        if (str[i] != str2[i]) return false;
    return true;
}
bool StdStringContains(const char* str, const char* find) {
    size_t sizes = StdStringLength(str);
    size_t sized = StdStringLength(find);
    size_t e = 0;
    for (size_t i = 0; i < sizes; i++)
        if (str[i] == find[e++]) {
            if (e == sized)
                return true;
        }
        else
            e = 0;
    return false;
}
size_t StdStringLength(const char* str) {
    size_t len = 0;
    while (str[len]) len++;
    return len;
}
void StdStringConcat(const char* str0, const char* str1, char* dst) {
    size_t i = 0;
    for (; i < StdStringLength(str0); i++) {
        dst[i] = str0[i];
    }
    for (size_t e = 0; e < StdStringLength(str1); e++) {
        dst[i] = str1[e];
        i++;
    }
}
void StdStringReverse(char* str, int len) {
    int start = 0;
    int end = len - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        end--;
        start++;
    }
}
char* StdLongToString(int64_t num, char* str, int base) {
    int i = 0;
    bool isNegative = false;

    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }

    if (num < 0 && base == 10) {
        isNegative = true;
        num = -num;
    }

    while (num != 0) {
        int rem = num % base;
        str[i++] = (rem > 9) ? (rem - 10) + 'A' : rem + '0';
        num = num / base;
    }

    if (isNegative)
        str[i++] = '-';

    str[i] = '\0';

    StdStringReverse(str, i);

    return str;
}
char* StdIntToString(int num, char* str, int base) {
    return StdLongToString((int64_t)num, str, base);
}