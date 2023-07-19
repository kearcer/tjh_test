#include <stdio.h>
#include <string.h>

int main()
{
    char string_json[4096];
    char* sei = "%lld and %lld and %lld";
    long long int number = 120832138621346LL;
    int offset = 0;

    // Calculate the number of %lld
    char *ptr = sei;
    int count = 0;
    while((ptr = strstr(ptr, "%lld")) != NULL) {
        count++;
        ptr++;
    }

    // Replace each %lld with number
    char* tmp = sei;
    for(int i = 0; i < count; i++) {
        char* next = strstr(tmp, "%lld");
        if(next) {
            int len = next - tmp;
            memmove(string_json + offset, tmp, len);
            offset += len;
            char num_str[21];  // maximum length of a long long int in decimal
            int num_len = snprintf(num_str, sizeof(num_str), "%lld", number);
            memmove(string_json + offset, num_str, num_len);
            offset += num_len;
            tmp = next + strlen("%lld");
        }
    }

    // Append the remaining string
    memmove(string_json + offset, tmp, strlen(tmp)+1);  // including null terminator

    printf("result:%s\n", string_json);
    return 0;
}
