#ifndef LIST_H_
#define LIST_H_
#include <stdbool.h>
struct num_info{
	int key;
	int distance;	
};

typedef struct num_info Item;

typedef struct node{
	Item item;
	struct node * next;
} Node;

//链表 
typedef Node * List;

//初始化链表
void InitializeList(List * pList);

//判断链表是否为空
bool ListIsEmpty(const List * pList);

//判断链表是否已满
bool ListIsFull(const List * pList);

//往链表中添加项 
bool AddItem(Item item,List * pList);

//释放已分配的内存
void EmptyTheList(List * pList);

#endif