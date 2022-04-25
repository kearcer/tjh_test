
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <sys/time.h>

typedef unsigned long int uint8;

char buf[1024] = "1234123412341234{\"uuid\":\"7eed1fd0b70d11ec91d2037c03653db8\"";
int datalen = 256;
char s[1024];
char s1[1024];
char s2[1024];
char *p;
int n,r;
char *BefUuid_Ctx;
char *AftUuid_Ctx;


unsigned long int VMF_GetTime()
{
    struct timespec time;
    unsigned long int lltime;
    clock_gettime(CLOCK_MONOTONIC, &time);
    lltime = ((unsigned long int)time.tv_sec) * 1000000 + time.tv_nsec / 1000;
    return lltime;
}

char* get_local_timestamp()
{
	/* 获取本地utc时间 */
	struct timeval tv;
    gettimeofday(&tv, NULL);
    
    /* utc时间 单位 秒*/
    long timestamp1 = tv.tv_sec;
    
	/* utc时间 单位 毫秒 */
	long long timestamp2 = tv.tv_sec*1000 + tv.tv_usec/1000;
	
	/* utc时间 单位 微秒 */
	long long timestamp3 = tv.tv_sec*1000*1000 + tv.tv_usec;

	/* utc时间字符串 */
	char timeStr1[20];
    char timeStr2[20];
    char timeStr3[20];
	memset(timeStr1, 0, sizeof(timeStr1));
    memset(timeStr2, 0, sizeof(timeStr2));
    memset(timeStr3, 0, sizeof(timeStr3));
	sprintf(timeStr1, "%d", timestamp1);		// int
	sprintf(timeStr2, "%ld", timestamp2);		// long
	sprintf(timeStr3, "%lld", timestamp3);	// long long
    printf("[%s]\n",timeStr1);
    printf("[%s]\n",timeStr2);
    printf("[%s]\n",timeStr3);

	/* utc时间字符串转换为整型 */
	int timeInt = atoi(timeStr1);			// 转成整型 int
	long timeLong = atol(timeStr2);			// 转成长整型 long 
	long long timeLLong = atoll(timeStr3);	// 转成长长整型 long long
    printf("[%d]\n",timeInt);
    printf("[%d]\n",timeLong);
    printf("[%d]\n",timeLLong);
    return timeStr2;
}


int main() {
    char *result;
    unsigned long int a = VMF_GetTime();
    // get_local_timestamp();
    printf("a:%d\n", a);

    p = (char *)malloc(256);
    FILE *fp1 = fopen("/home/tjh_test/test13/sei_61_0_91874152.sei", "rb");
    
    fread(p, 256, 1, fp1);
    printf("len of result: %d\n", strlen(p));


    // printf("[%s]\n",result);
    // printf("len of result: %d\n", strlen(result));

    // FILE *fp2 = fopen("./out.bin", "ab");
    // fwrite(result, 491, 1, fp2);
    // fflush(fp2);
    return 0;
}

