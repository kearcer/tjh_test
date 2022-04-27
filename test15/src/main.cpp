
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <sys/time.h>

int Update(char * p, char *ltc)
{
    struct timeval tv;
    char*stamp = "%";
    char utc[20];
    gettimeofday(&tv, NULL);
	long long timestamp = tv.tv_sec*1000 + tv.tv_usec/1000;
    memset(utc, 0, sizeof(utc));
	sprintf(utc, "%ld", timestamp);

    while (1) 
    {
        p=strstr(p,"%");
        if(p)
        {
            if(p[1] == '%')
            {
                memmove(p+1,p+2,strlen(p)-2+1);
                memcpy(p, stamp, 1);
                p++;
            }
            else if (p[1] == 'u' && p[2] == 't' && p[3] == 'c' && p[4] == '%')
            {
                int a = strlen(utc);
                memmove(p+a,p+5,strlen(p)-5+1);
                memcpy(p, utc, a); 
                p = p + a;
            }
            else if (p[1] == 'l' && p[2] == 't' && p[3] == 'c' && p[4] == '%')
            {
                int a = strlen(ltc);
                memmove(p+a,p+5,strlen(p)-5+1);
                memcpy(p, ltc, a);
                p = p + a;
            }
            else
                memmove(p,p+1,strlen(p));
        }
        else
            break;
    }
    return 0;
}


int main() {
    char*ltc="12:34:56.17";
    char s[256] = "%utc% %ltc% %123utc% %%ltc%% %%%utc%%%";
    char *p;
    int r,n,i;

    printf("输入文本：%s\n", s);
    p=s;

    Update(p, ltc);

    printf("%s\n",s);

    return 0;
}



