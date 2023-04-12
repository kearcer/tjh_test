#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 100

//定义哈希表中的键值对
typedef struct
{
    char *key;   //键
    char *value; //值
} hash_pair;

//定义哈希表
typedef struct
{
    hash_pair **pairs; //键值对数组
    unsigned int size; //哈希表大小
} hash_table;

//创建哈希表
hash_table *create_hash_table()
{
    hash_table *new_table = (hash_table *)malloc(sizeof(hash_table));         //分配哈希表内存
    new_table->pairs = (hash_pair **)calloc(TABLE_SIZE, sizeof(hash_pair *)); //分配键值对数组内存
    new_table->size = TABLE_SIZE;                                             //设置哈希表大小
    return new_table;
}

//哈希函数
unsigned int hash(char *key)
{
    unsigned long int value = 0; //哈希值
    unsigned int i = 0;
    unsigned int key_len = strlen(key); //键的长度

    for (; i < key_len; ++i)
    {
        value = value * 37 + key[i]; //计算哈希值
    }

    value = value % TABLE_SIZE; //取模运算

    return value;
}

//创建键值对
hash_pair *create_pair(char *key, char *value)
{
    hash_pair *new_pair = (hash_pair *)malloc(sizeof(hash_pair)); //分配键值对内存
    new_pair->key = strdup(key);                                  //复制键
    new_pair->value = strdup(value);                              //复制值
    return new_pair;
}

//设置键值对
void set(hash_table *table, char *key, char *value)
{
    unsigned int index = hash(key); //计算哈希值

    if (table->pairs[index] != NULL) //如果该位置已经有键值对
    {
        free(table->pairs[index]); //释放该位置的键值对内存
    }

    table->pairs[index] = create_pair(key, value); //创建新的键值对并存储到该位置
}

//获取键对应的值
char *get(hash_table *table, char *key)
{
    unsigned int index = hash(key); //计算哈希值

    if (table->pairs[index] == NULL) //如果该位置没有键值对
    {
        return NULL; //返回空指针
    }
    else
    {
        return table->pairs[index]->value; //返回该位置的值
    }
}

//主函数
int main()
{
    hash_table *my_table = create_hash_table(); //创建哈希表

    set(my_table, "apple", "a sweet fruit"); //设置键值对

    printf("%s\n", get(my_table, "apple")); //获取键对应的值

    return 0;
}
