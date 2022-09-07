#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *s1;
int main()
{
    char temp[1048];
    s1 = (char *)malloc(491);
    FILE *fp1 = fopen("/home/tjh_test/test10/no.73-1output.bin", "rb");
    fread(s1, 491, 1, fp1);
    printf("len of result: %d\n", strlen(s1));

    char *Stamp_title = "\":[{\"translateText\"";
    char *Stamp_duration = "\"duration\":";
    char*p;
    printf("请输入一字串");
    p=strstr(s1,Stamp_duration);
    if(
        p!=NULL)
        {
            strncpy(temp,s1,p-s1);
            // printf("删除后的字串为:%s\n",temp);
            temp[p-s1]='\0';
            // printf("temp:%s\n",temp);
            // printf("p:%s\n",p);
            strcat(temp, Stamp_duration);
            strcat(temp, "0");
            strcat(temp,p+strlen(Stamp_duration)+4);
            printf("删除后的字串为:%s\n",temp);
        }
        else
            printf("要删除字字串未找到!\n");
        return 0;
}
