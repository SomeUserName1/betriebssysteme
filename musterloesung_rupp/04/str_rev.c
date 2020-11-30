#include <stdio.h>
#include <string.h>

void string_reverse_inplace(char* str);

int main(void) {
    char test[] = "Hello World";

    string_reverse_inplace(test);

    printf("%s", test);

    return 0;
}

void string_reverse_inplace(char* str) {
    char *end = str;
    char temp;

    for (; *end != '\0'; ++end) ; 

    for (; str < --end; ++str) {
        temp = *str;
        *str = *end;
        *end = temp;
    }
}
