#ifndef LIST_C_
#define LIST_C_

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "list.h"

//初始化链表
void InitializeList(List * pList){
	*pList = NULL;
}

//判断链表是否为空
bool ListIsEmpty(const List * pList){
	return (*pList == NULL)?true:false;
}

//判断链表是否已满
bool ListIsFull(const List * pList){
	Node * pn;
	bool full;
	pn = (Node *)malloc(sizeof(Node));
	full = (pn == NULL)?true:false;
	free(pn);
	return full;
}

//往链表中添加项（按照item中的distance排序） 
bool AddItem(Item item,List * pList){
	Node * prev,* current;
	//新节点
	Node * pnew = (Node *)malloc(sizeof(Node));	 
	if(pnew == NULL){
		return false;
	}
	
	pnew->item = item;
	pnew->next = NULL;
	
	if(*pList == NULL){
		*pList = pnew;
	}else{
		prev = NULL;
		current = *pList;
		while(current != NULL){
			if(item.distance <= (current->item).distance){
				pnew->next = current;
				if(current == *pList){
					*pList = pnew;
				}else{
					prev->next = pnew;
				}
				break;
			}
			prev = current;
			current = current->next;
		}
		//到达链表末尾 
		if(current == NULL){
			prev->next = pnew;
		}
	}
	return true;
}

//释放已分配的内存
void EmptyTheList(List * pList){
	Node * current = *pList;
	while(current != NULL){
		*pList = current->next;
		free(current);
		current = *pList;
	}
}

#endif
