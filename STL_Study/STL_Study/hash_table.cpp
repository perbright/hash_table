#include "hash_table.h"

//����hash����
//n -- ���ٸ�����
struct hash_table* create_hash_table(int n)
{
	struct hash_table* t = (struct hash_table*)my_malloc(sizeof(struct hash_table));		//����ṹ�ڴ�
	memset(t,0,sizeof(struct hash_table));													//��ʼ�ڴ�

	//n�����ϵ��ڴ棬��ŵ�������ͷ��ָ��
	t->hash_set = (hash_node**)my_malloc(n * sizeof(struct hash_node*));					//����ṹ�弯���ڴ�
	memset(t->hash_set,0,sizeof(struct hash_node*)*n);										
	t->n = n;																				//��¼���ϸ���
	return t;
}

//����hash�㷨
static unsigned int hash_index(char *str)
{
	register unsigned int h;
	register unsigned char *p;

	for (h = 0, p = (unsigned char*)str ; *p;*p++)
	{
		h = 31*h + *p;
	}
	return h;
}

unsigned int hash_index_static(char *str)
{
	unsigned int a;
	a = hash_index(str);
	return a;
}

void hash_insert(struct hash_table* t,char* key,void* value)
{
	struct hash_node* node = (hash_node*)my_malloc(sizeof(struct hash_node));
	memset(node, 0, sizeof(struct hash_node));
	node->key = _strdup(key);
	node->value =  value;

	//ʹ��hash������key�������ĸ�����
	int index = (hash_index(key)%t->n);	//ģ���㣬����ȡ��[0,0-1]
	struct hash_node* header = t->hash_set[index];

	node->next = header;
	t->hash_set[index] = node;
}

void hash_delete(struct hash_table* t,char* key)
{
	int index = (hash_index(key)%t->n);		//ģ���㣬����ȡ��[0,0-1]
	struct hash_node** walk = &(t->hash_set[index]);
	while(*walk)
	{
		if (strcmp((*walk)->key,key) == 0)
		{
			struct hash_node* rm_node = *walk;
			*walk = (*walk)->next;

			rm_node->next = NULL;

			//key,hash_node�ͷŽڵ�
			my_free(rm_node->key);
			my_free(rm_node);
		}
		else
		{
			walk = &((*walk)->next);
		}
	}
}

void hash_clear(struct hash_table* t)
{
	for (int i = 0; i < t->n; i++)
	{
		struct hash_node* walk = t->hash_set[i];
		t->hash_set[i] = NULL;

		while(walk)
		{
			struct hash_node* rm_node = walk;
			walk = walk->next;
			rm_node->next = NULL;

			my_free(rm_node->key);
			my_free(rm_node);
		}
	}
}

void destroy_hash_table(struct hash_table* t)
{
	//ɾ�����е�Ԫ��
	hash_clear(t);
	if (t->hash_set)
	{
		my_free(t->hash_set);
		t->hash_set = NULL;
	}
	my_free(t);
}

void hash_set(struct hash_table* t,char* key, void* value)
{
	//ʹ��hash������key�������ĸ�����
	int index = (hash_index(key)%t->n);
	struct hash_node** walk = &(t->hash_set[index]);

	while(*walk)
	{
		if (strcmp((*walk)->key,key) == 0)
		{
			(*walk)->value = value;
			return;
		}
		walk = &((*walk)->next);
	}
	//������key,value
	struct hash_node* node = (hash_node*)my_malloc(sizeof(struct hash_node));
	memset(node, 0, sizeof(struct hash_node));
	node->key = _strdup(key);
	node->value = value;
	*walk = node;
}

void* hash_find(struct hash_table* t, char* key)
{
	int index = (hash_index(key)%t->n);
	struct hash_node* walk = (t->hash_set[index]);

	while(walk)
	{
		if (strcmp((walk)->key,key) == 0)
		{
			return walk->value;
		}
		walk = walk->next;
	}
	return NULL;
}