/*支持链表操作的函数*/
#ifndef LIST_C_
#define LIST_C_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "list.h"

//局部函数原型
static void CopyToNode(Item item,Node * pNode); 

//接口函数
//把链表设置为空
void InitializeList(List * pList) {
	*pList = NULL;
}

bool ListIsEmpty(const List * pList){
	if(*pList == NULL){
		return true;
	}else{
		return false;
	}
}

bool ListIsFull(const List * pList){
	//链表是否已满，关键是看还可不可以申请内存
	Node * pt;
	bool full;
	
	pt = (Node *)malloc(sizeof(Node)); 
	//申请内存失败，则表示链表已满
	if(pt == NULL){
		full = true;
	} else{
		full = false;
	}
	free(pt);
	return full;
}

unsigned int ListItemCount(const List * pList){
	unsigned int count = 0;
	Node * pNode = *pList;//设置链表的开始
	while(pNode != NULL){
		count ++;
		pNode = pNode->next;	//设置下一个节点 
	} 
	
	return count; 
} 

bool AddItem(Item item,List * pList){
	Node * pnew;
	Node * scan = *pList;	//设置链表的开始
	
	pnew = (Node *)malloc(sizeof(Node));
	if(pnew == NULL){
		return false;	//内存申请失败！ 
	}
	CopyToNode(item,pnew);
	pnew->next= NULL;
	
	//空链表
	if(scan == NULL){
		*pList = pnew;	
	} else{
		while(scan->next != NULL){
			scan = scan->next;
		}
		scan->next = pnew;	//将新节点添加到链表末尾 
	}
	
	return true; 
}

bool DeleteNode(List * pList,Node * delNode){
	Node * current = *pList;
	
	if(delNode == current){
		*pList = delNode->next;
		free(delNode);
		return true;
	}
	
	while(current->next != NULL){
		if(current->next == delNode){
			current->next= delNode->next;
			free(delNode);
			return true;
		}else{
			current = current->next;
		}
	}
	return false;
}

void Traverse(const List * pList,void(*pfun)(Item item)){
	Node * pNode = *pList;
	while(pNode != NULL){
		(*pfun)(pNode->item);
		pNode = pNode->next; 
	}
}

void EmptyTheList(List * pList){
	Node * current = *pList;
	while(current != NULL){
		*pList = current->next;
		free(current);
		current = *pList;
	}
}


//局部函数定义
static void CopyToNode(Item item,Node * pNode){
	pNode->item= item;
} 

#endif