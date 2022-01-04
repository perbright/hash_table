#include <map>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "hash_table.h"
using namespace std;

int main(int argc, char* argv[])
{
	struct hash_table* t = create_hash_table(1024);

	hash_insert(t, "xiaoming", (void*)12);
	hash_insert(t, "xiaohong", (void*)36);
	hash_insert(t, "xiaowang", (void*)"shanghai");

	int ret = (int)hash_find(t,"xiaoming");
	printf("xiaoming = %d\n",ret);

	char* address = (char*)hash_find(t,"xiaowang");
	printf("address = %s\n",address);

	hash_delete(t,"xiaohong");
	void* value = hash_find(t,"xiaohong");
	if (value == NULL)
	{
		printf("查不到对应的值！\n");
	}

	destroy_hash_table(t);	//删除对象

	system("PAUSE");
	return 0;
}