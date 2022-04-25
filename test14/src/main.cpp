
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <sys/time.h>

char*utc="1650354981418";
char*ltc="12:34:56.17";


int main() {

    // char s[256] = "123456:%utc%:%ltc%:%%utc%%:%%%utc%%%";
    char s[256] = "123456:%utc%789%ltc%1011; ltc utc";
    char *p;
    int r,n,i;

    printf("将一个文字中的\"utc\"替换成\"1650354981418\";并且将\"utc\"替换为\"ltc\"\n");
    p=s;
    while (1) 
    {
        p=strstr(p,"utc");
        if (p) 
        {
            int a = strlen(utc);
            memmove(p+a,p+3,strlen(p)-3+1);
            memcpy(p, utc, a);
        } 
        else 
            break;
    }
    p=s;
    while (1) 
    {
        p=strstr(p,"ltc");
        if (p) 
        {
            int a = strlen(ltc);
            int b = strlen(p);
            memmove(p+a,p+3,b-3+1);
            // for (i=0;i<6;i++) p[i]='X';
            memcpy(p, ltc, a);
        } 
        else 
            break;

    }
    printf("%s\n",s);

    return 0;
}



