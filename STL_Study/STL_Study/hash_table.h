#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdio.h>
#include <string>
#include <stdlib.h>

#define my_malloc malloc
#define my_free free

//hash结构体
struct hash_node{
	char* key;
	void* value;
	struct hash_node* next;
};

struct hash_table{
	struct hash_node** hash_set;		//每个集合的链表头指针
	int n;								//hash_table里面有多少集合
};

//创建hash对象
struct hash_table* create_hash_table(int n);

//经典算法
static unsigned int hash_index(char *str);
unsigned int hash_index_static(char *str);

//插入一个key:value，不判断是否重复
void hash_insert(struct hash_table* t,char* key,void* value);

//删除表
void hash_delete(struct hash_table* t,char* key);

//清理所有的hash表的数据
void hash_clear(struct hash_table* t);

//删除hash对象
void destroy_hash_table(struct hash_table* t);

//插入/修改key:value
void hash_set(struct hash_table* t,char* key, void* value);

//在hash表里查找我们的值
void* hash_find(struct hash_table* t, char* key);

#endif