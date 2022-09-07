
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <sys/time.h>

int Update_Sdi_ltc(char * p, int ltc_info)
{
    struct timeval tv;
    char*stamp = "%";
    char utc[20];
    gettimeofday(&tv, NULL);
	long long timestamp = tv.tv_sec*1000 + tv.tv_usec/1000;
    memset(utc, 0, sizeof(utc));
	sprintf(utc, "%ld", timestamp);

    char ltc[256]={0};
    int cHour = ((ltc_info >> 24) & 0xff);
    int cMinute = ((ltc_info >> 16) & 0xff);
    int cSecond = ((ltc_info >> 8) & 0xff);
    int cFrame = (ltc_info & 0xff);
    sprintf(ltc, "%d:%d:%d.%d",cHour, cMinute, cSecond, cFrame);

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
    return strlen(p);
}


int main() {
    int ltc=12345678;
    char s[256] = "%utc% %ltc% %123utc% %%ltc%% %%%utc%%%";
    char *p;
    int r,n,i;

    printf("输入文本：%s\n", s);
    p=s;

    int len = Update_Sdi_ltc(p, ltc);

    printf("%s\n",s);
    printf("%d\n",len);

    return 0;
}



