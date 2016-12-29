#ifndef LIST_C_
#define LIST_C_

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "list.h"

//��ʼ������
void InitializeList(List * pList){
	*pList = NULL;
}

//�ж������Ƿ�Ϊ��
bool ListIsEmpty(const List * pList){
	return (*pList == NULL)?true:false;
}

//�ж������Ƿ�����
bool ListIsFull(const List * pList){
	Node * pn;
	bool full;
	pn = (Node *)malloc(sizeof(Node));
	full = (pn == NULL)?true:false;
	free(pn);
	return full;
}

//����������������item�е�distance���� 
bool AddItem(Item item,List * pList){
	Node * prev,* current;
	//�½ڵ�
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
		//��������ĩβ 
		if(current == NULL){
			prev->next = pnew;
		}
	}
	return true;
}

//�ͷ��ѷ�����ڴ�
void EmptyTheList(List * pList){
	Node * current = *pList;
	while(current != NULL){
		*pList = current->next;
		free(current);
		current = *pList;
	}
}

#endif
