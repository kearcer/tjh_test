
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <malloc.h>
char buf[1024] = "1234123412341234{\"uuid\":\"7eed1fd0b70d11ec91d2037c03653db8\"";
char s[32];
char *p;
char *result;
int n,r;
int main() {
    result = (char *)malloc(500);
    p=buf;
    r=sscanf(p+16,"{\"uuid\":\"%32[^\"]%n",s,&n);
    
    // memcpy(result, "{\"uuid\":\"", 9);
    strcpy(result,"{\"uuid\":\"");
    strcat(result, s);
    strcat(result, "\",\"utc\":1649402961833,\"user_data\":{\"19\":{\"audioTrackList\":[{\"audioTrackInfo\":{\"title\":\"\",\"language\":\"chi\",\"extension\":\"\",\"subtitle\":{\"language\":\"chi\",\"originalText\":\"\",\"translateTextList\":[{\"translateText\":\"\",\"language\":\"eng\"}],\"startTime\":0,\"endTime\":0,\"duration\":0,\"profiles\":\"\",\"extension\":\"\"}}}]}}}");

    printf("[%s]\n",result);

    FILE *fp1 = fopen("./out.bin", "ab");
    fwrite(result, 500, 1, fp1);
    fflush(fp1);

    return 0;
}

