#ifndef LIST_H_
#define LIST_H_
#include <stdbool.h> 

/* �ض���������� */
#define NSIZE 10	/*�洢��ҵ���������С*/ 
struct JCB{
	//��� 
	int jobNum;
	//��ҵ�� 
	char jobName[NSIZE];
	//�ύʱ�䣬ת��Ϊ���� 
	int submitTime;
	//����ʱ�� 
	int runTime;
	//�洢�ռ� 
	int jobSpace;	
}; 

//typedef enum{false = 0,true = 1} bool;

/*һ�����Ͷ���*/
typedef struct JCB Item;

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

//ɾ�����
bool DeleteNode(List * pList,Node * delNode); 

//�Ѻ��������������е�ÿһ��
void Traverse(const List * pList,void (*pfun)(Item item)); 

//�ͷ��ѷ�����ڴ�
void EmptyTheList(List * pList); 

#endif;