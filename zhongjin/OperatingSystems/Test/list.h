/*list.h -- ���������͵�ͷ�ļ� */
/*���ڷ�ֹ�ظ�����һ���ļ��������ظ�����Ĵ��� */
#ifndef LIST_H_
#define LIST_H_
#include <stdbool.h> 

/* �ض���������� */
#define TSIZE 5	/*�洢��Ӱ���������С*/ 
struct film{
	char title[TSIZE];
	int rating;		
}; 

//typedef enum{false = 0,true = 1} bool;

/*һ�����Ͷ���*/
typedef struct film Item;

//������
typedef struct node{
	Item item;
	struct node * next;
} Node;

//���� 
typedef Node * List;

/*����ԭ��*/

//��ʼ������
void InitializeList(List * pList); 

//�ж������Ƿ�Ϊ��
bool ListIsEmpty(const List * pList);

//�ж������Ƿ�����
bool ListIsFull(const List * pList);

//ȷ�������е���Ŀ�� 
unsigned int ListItemCount(const List * pList);

//������ĩβ�����
bool AddItem(Item item,List * pList);

//�Ѻ��������������е�ÿһ��
void Traverse(const List * pList,void (*pfun)(Item item)); 

//�ͷ��ѷ�����ڴ�
void EmptyTheList(List * pList); 

#endif;