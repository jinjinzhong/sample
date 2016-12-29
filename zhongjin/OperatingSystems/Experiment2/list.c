/*֧����������ĺ���*/
#ifndef LIST_C_
#define LIST_C_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "list.h"

//�ֲ�����ԭ��
static void CopyToNode(Item item,Node * pNode); 

//�ӿں���
//����������Ϊ��
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
	//�����Ƿ��������ؼ��ǿ����ɲ����������ڴ�
	Node * pt;
	bool full;
	
	pt = (Node *)malloc(sizeof(Node)); 
	//�����ڴ�ʧ�ܣ����ʾ��������
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
	Node * pNode = *pList;//��������Ŀ�ʼ
	while(pNode != NULL){
		count ++;
		pNode = pNode->next;	//������һ���ڵ� 
	} 
	
	return count; 
} 

bool AddItem(Item item,List * pList){
	Node * pnew;
	Node * scan = *pList;	//��������Ŀ�ʼ
	
	pnew = (Node *)malloc(sizeof(Node));
	if(pnew == NULL){
		return false;	//�ڴ�����ʧ�ܣ� 
	}
	CopyToNode(item,pnew);
	pnew->next= NULL;
	
	//������
	if(scan == NULL){
		*pList = pnew;	
	} else{
		while(scan->next != NULL){
			scan = scan->next;
		}
		scan->next = pnew;	//���½ڵ���ӵ�����ĩβ 
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


//�ֲ���������
static void CopyToNode(Item item,Node * pNode){
	pNode->item= item;
} 

#endif