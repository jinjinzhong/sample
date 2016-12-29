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

//���� 
typedef Node * List;

//��ʼ������
void InitializeList(List * pList);

//�ж������Ƿ�Ϊ��
bool ListIsEmpty(const List * pList);

//�ж������Ƿ�����
bool ListIsFull(const List * pList);

//������������� 
bool AddItem(Item item,List * pList);

//�ͷ��ѷ�����ڴ�
void EmptyTheList(List * pList);

#endif