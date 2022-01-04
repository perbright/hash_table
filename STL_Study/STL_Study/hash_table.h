#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdio.h>
#include <string>
#include <stdlib.h>

#define my_malloc malloc
#define my_free free

//hash�ṹ��
struct hash_node{
	char* key;
	void* value;
	struct hash_node* next;
};

struct hash_table{
	struct hash_node** hash_set;		//ÿ�����ϵ�����ͷָ��
	int n;								//hash_table�����ж��ټ���
};

//����hash����
struct hash_table* create_hash_table(int n);

//�����㷨
static unsigned int hash_index(char *str);
unsigned int hash_index_static(char *str);

//����һ��key:value�����ж��Ƿ��ظ�
void hash_insert(struct hash_table* t,char* key,void* value);

//ɾ����
void hash_delete(struct hash_table* t,char* key);

//�������е�hash�������
void hash_clear(struct hash_table* t);

//ɾ��hash����
void destroy_hash_table(struct hash_table* t);

//����/�޸�key:value
void hash_set(struct hash_table* t,char* key, void* value);

//��hash����������ǵ�ֵ
void* hash_find(struct hash_table* t, char* key);

#endif