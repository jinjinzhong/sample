#include <stdio.h> 
#include <stdlib.h>
#include "list.h"
#include "list.c"

//������ҵ��Ϣ 
void InputTask(List * pList);
//���������и�����ҵ�����ȼ�
void UpdatePriority(List * pList,int T); 
//��ȡ��Tʱ��Ӧ�ô������ҵ
Node * getTask(List * pList,int T); 
//����Ӧ������(HRRN)�����㷨
void HRRN(List * pList);

int main(void){
	List taskList;
	
	InitializeList(&taskList);
	if(ListIsFull(&taskList)){
		fprintf(stderr,"No memory available!Bye!\n");
		exit(1);
	}
	
	InputTask(&taskList);
	
	HRRN(&taskList);
	
	//�ͷ��ڴ� 
	EmptyTheList(&taskList);
	return 0;
}

void InputTask(List * pList){
	char ch;
	Item temp;
	
	puts("task_name come_time server_time (Empty line to finish!)");
	do{
		//�����˳� 
		if((ch = getchar()) == '\n'){
			break;
		}
		temp.title[0] = ch;
		//scanf("%s %d %d",&(temp.title[1]),&(temp.ComeTime),&(temp.ServerTime));
		scanf("%d %d",&(temp.ComeTime),&(temp.ServerTime));
	
		//��������� 
		while(getchar() != '\n'){
			continue;
		}
		
		
		if(AddItem(temp,pList) == false){
			fprintf(stderr,"Problem allocating memory\n");
			break;
		}
		if(ListIsFull(pList)){
			puts("The list is now full!");
			break;
		}
	}while(true);
}
void UpdatePriority(List * pList,int T){
	Node * current = *pList;
	while(current != NULL){
		(current->item).Priority = (double)(T - (current->item).ComeTime + (current->item).ServerTime)/(current->item).ServerTime;
		current = current->next;
	} 
}


/**
 *	�㷨����1��������ҵͬʱ�������ҵ���ȵ���ִ��
 *			  2��������ҵҪ��ִ��ʱ����ͬ���ȵ���ҵ����ִ��
 *			  3���������ȼ�����ִ�� 
 */
Node * getTask(List * pList,int T){
	if(ListIsEmpty(pList)){
		//fprintf(stderr,"You have not enter any task!\n");
		//exit(2);
		return NULL;
	}
	
	//�������ȼ�
 	UpdatePriority(pList,T); 
	
	Node * temp = *pList;
	Node * current = temp->next;
	while(current != NULL){
		//��ҵ��û���� 
		if((current->item).ComeTime > T){
			current = current->next;
			continue;
		}
		//���1��������ҵͬʱ�������ҵ���ȵ���ִ��
		if((temp->item).ComeTime == (current->item).ComeTime && (temp->item).ServerTime > (current->item).ServerTime){
			temp = current; 
			current = current->next;
			continue; 
		}
		//���2��������ҵҪ��ִ��ʱ����ͬ���ȵ���ҵ����ִ��
		if((temp->item).ServerTime	== (current->item).ServerTime && (temp->item).ComeTime > (current->item).ComeTime){
			temp = current; 
			current = current->next;
			continue;
		}
		
	    //���3���������ȼ�����ִ�� 
	    if((temp->item).Priority < (current->item).Priority){
    		temp = current;
    	}
    	current = current->next;
	}
	return ((temp->item).ComeTime > T)?NULL:temp;
}
void HRRN(List * pList){
	int T = 0;
	Node * temp;
	printf("Time = %d\n",T);
	while(!ListIsEmpty(pList)){
		temp = getTask(pList,T);
		//printf("%s %d %d %d\n",(temp->item).title,(temp->item).ComeTime,(temp->item).ServerTime,(temp->item).Priority);
		if(temp == NULL){ 
			T ++;
			continue;
		}else{
			printf("Task %s begin.\n",(temp->item).title); 
			T += (temp->item).ServerTime;
			printf("Time = %d\nTask %s finish.\n",T,(temp->item).title);
			DeleteNode(pList,temp);
		}
	}
}