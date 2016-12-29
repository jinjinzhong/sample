/*list.h -- 简单链表类型的头文件 */
/*用于防止重复包含一个文件，避免重复定义的错误 */
#ifndef LIST_H_
#define LIST_H_
#include <stdbool.h> 

/* 特定程序的声明 */
#define TSIZE 5	/*存储电影名的数组大小*/ 
struct film{
	char title[TSIZE];
	int rating;		
}; 

//typedef enum{false = 0,true = 1} bool;

/*一般类型定义*/
typedef struct film Item;

//链表结点
typedef struct node{
	Item item;
	struct node * next;
} Node;

//链表 
typedef Node * List;

/*函数原形*/

//初始化链表
void InitializeList(List * pList); 

//判断链表是否为空
bool ListIsEmpty(const List * pList);

//判断链表是否已满
bool ListIsFull(const List * pList);

//确定链表中的项目数 
unsigned int ListItemCount(const List * pList);

//在链表末尾添加项
bool AddItem(Item item,List * pList);

//把函数作用与链表中的每一项
void Traverse(const List * pList,void (*pfun)(Item item)); 

//释放已分配的内存
void EmptyTheList(List * pList); 

#endif;