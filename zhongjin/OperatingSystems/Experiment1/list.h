//#ifndef LIST_H_
//#define LIST_H_
#include <stdbool.h> 

/* �ض���������� */
#define TSIZE 10	/*�洢��ҵ���������С*/ 
struct task{
	char title[TSIZE];
	int ComeTime;
	int ServerTime;	
	double Priority;
}; 

//typedef enum{false = 0,true = 1} bool;

/*һ�����Ͷ���*/
typedef struct task Item;

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

//#endif;