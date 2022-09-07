
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <malloc.h>
#include<stdlib.h>

char buf[1024] = "1234123412341234{\"uuid\":\"7eed1fd0b70d11ec91d2037c03653db8\"";
char s[1024];
char s1[1024];
char s2[1024];
char *p;
int n,r;
char *BefUuid_Ctx;
char *AftUuid_Ctx;

int mystrlen1(char *p)
{
    int length = 0;
    char *match1 = strstr(p, "[{\"translateText\":\"");   //查找文件中的"home_dir="字符串
    char *match2 = strstr(p, "\",\"language\":\"eng\"");   //查找文件中的"home_dir="字符串
    int a = strlen("[{\"translateText\":\"");
    if (strlen(match1) - strlen(match2) != strlen("[{\"translateText\":\""))
    {
        length = strlen(match1)-strlen(match2)-strlen("[{\"translateText\":\"");
        printf("the size of translateText %d\n", length);
    } 
    else 
    {
        printf("this is an emopty translateText\n");
    }
    return length;
}

int mystrlen2(char *p)
{
    int length = 0;
    int Stamp_duration_len = strlen("\"duration\":");
    char *match1 = strstr(p, "\"duration\":");   //查找文件中的"home_dir="字符串
    char *match2 = strstr(p, ",\"profiles\":");   //查找文件中的"home_dir="字符串
    char zero[1];
    // &match1[1]==0;
    // sscanf(match1+Stamp_duration_len, "%1s", zero);
    if (match1[Stamp_duration_len] == '0')
    {
        printf("duration is 0\n");
    }
    else
    {
        length = strlen(match1)-strlen(match2)-Stamp_duration_len;
        printf("the size of duration %d\n", length);
    }
    return length;
    return length;
}

int mystrlen3(char *p)
{
    int length = 0;
    char *match1 = strstr(p, "\"originalText\":\"");   //查找文件中的"home_dir="字符串
    char *match2 = strstr(p, "\",\"translateTextList\"");   //查找文件中的"home_dir="字符串
    int a = strlen("\"originalText\":");
    if (strlen(match1)-strlen(match2) != (strlen("\"originalText\":")))
    {
        length = strlen(match1)-strlen(match2)-strlen("\"originalText\":\"");
        printf("the size of originalText %d\n", length);
    } 
    else 
    {
        printf("this is an emopty duration\n");
    }

    return length;
}

int Update_duration(char* result, char *p,char *Stamp,int len)
{
    char *temp;
    temp=strstr(p,Stamp);
    if(
        temp!=NULL)
        {
            strncpy(result,p,temp-p);
            result[temp-p]='\0';
            strcat(result, Stamp);
            strcat(result, "0");
            strcat(result,temp+strlen(Stamp)+len);
            
        }
        else
            printf("要删除字字串未找到!\n");
}

int Update(char* result, char *p,char *Stamp,int len)
{
    char *temp;
    temp=strstr(p,Stamp);
    // printf("result:%s\n",temp);
    if(
        temp!=NULL)
        {
            strncpy(result,p,temp-p);
            result[temp-p]='\0';
            // printf("result:%s\n",result);
            // printf("Stamp:%s\n",Stamp);
            strcat(result, Stamp);
            // printf("result:%s\n",result);
            // printf("Stamp:%s\n",temp+strlen(Stamp)+len);
            strcat(result,temp+strlen(Stamp)+len);
            
        }
        else
            printf("要删除字字串未找到!\n");
}

int Update_Subtitle_Sei(char *p, int length, char * result)
{
    char *Stamp_title = "[{\"translateText\":\"";
    char *Stamp_duration = "\"duration\":";
    char *Stamp_origiontxt = "\"originalText\":\"";

    // break;
    int len1 = mystrlen1(p);
    int len2 = mystrlen2(p);
    int len3 = mystrlen3(p);
    if (len1 == 0 && len2 == 0)
    {
        result=strstr(p,Stamp_title);
        memcpy(result, p, strlen(p));
        printf("mugu sei context is empty");
    }
    else
    {
        Update(result, p,Stamp_title,len1);
        Update_duration(result, result,Stamp_duration,len2);
        Update(result, result,Stamp_origiontxt,len3);
    }
}

int main() {
    char *result;
    
    p = (char *)malloc(491);
    FILE *fp1 = fopen("/home/tjh_test/test10/no.279-1output.bin", "rb");
    fread(p, 491, 1, fp1);
    printf("len of result: %d\n", strlen(p));

    // char *Stamp_title = "[{\"translateText\":\"";
    // char *Stamp_duration = "\"duration\":";
    // char *Stamp_origiontxt = "\"originalText\":\"";
    // BefUuid_Ctx = "{\"uuid\":\"";
    // AftUuid_Ctx = "\",\"utc\":1649402961833,\"user_data\":{\"19\":{\"audioTrackList\":[{\"audioTrackInfo\":{\"title\":\"\",\"language\":\"chi\",\"extension\":\"\",\"subtitle\":{\"language\":\"chi\",\"originalText\":\"\",\"translateTextList\":[{\"translateText\":\"\",\"language\":\"eng\"}],\"startTime\":0,\"endTime\":0,\"duration\":0,\"profiles\":\"\",\"extension\":\"\"}}}]}}}";
    result = (char *)malloc(491);
    Update_Subtitle_Sei(p, 491, result);
    // // break;
    // int len1 = mystrlen1(p);
    // int len2 = mystrlen2(p);
    // int len3 = mystrlen3(p);
    // if (len1 == 0 && len2 == 0)
    // {
    //     result=strstr(p,Stamp_title);
    //     memcpy(result, p, strlen(p));
    //     printf("mugu sei context is empty");
    // }
    // else
    // {
    //     Update(result, p,Stamp_title,len1);
    //     Update_duration(result, result,Stamp_duration,len2);
    //     Update(result, result,Stamp_origiontxt,len3);
    // }


    printf("[%s]\n",result);
    printf("len of result: %d\n", strlen(result));

    FILE *fp2 = fopen("./out.bin", "ab");
    fwrite(result, 491, 1, fp2);
    fflush(fp2);
    return 0;
}

