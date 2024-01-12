#include <string.h>

void pre(char* _) {
    char* str = _;
    char* end = str + strlen(str);
    while (str < end) {
        while (str[0] != '/') {
            str++;
            if (str >= end) return;
        }
        if (str[1] == '/') {
            char* begin = str;
            while (str[0] != '\n') {
                if (str >= end) break;
                str++;
            }

            memset(begin, ' ', str-begin);
        } else if (str[1] == '*') {
            char* begin = str;
            while (str[0] != '*' && str[1] != '/') {
                if (str + 1 >= end) break;
                str++;
            }
            str += 1;

            memset(begin, ' ', str-begin);
        }
    }
}