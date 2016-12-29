#include <stdio.h> 
#include <stdlib.h>
#include "list.h"
#include "list.c"

//输入作业信息 
void InputTask(List * pList);
//更新链表中各个作业的优先级
void UpdatePriority(List * pList,int T); 
//获取在T时刻应该处理的作业
Node * getTask(List * pList,int T); 
//高响应比优先(HRRN)调度算法
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
	
	//释放内存 
	EmptyTheList(&taskList);
	return 0;
}

void InputTask(List * pList){
	char ch;
	Item temp;
	
	puts("task_name come_time server_time (Empty line to finish!)");
	do{
		//空行退出 
		if((ch = getchar()) == '\n'){
			break;
		}
		temp.title[0] = ch;
		//scanf("%s %d %d",&(temp.title[1]),&(temp.ComeTime),&(temp.ServerTime));
		scanf("%d %d",&(temp.ComeTime),&(temp.ServerTime));
	
		//清除输入项 
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
 *	算法规则：1、若干作业同时到达，短作业优先调入执行
 *			  2、若干作业要求执行时间相同，先到作业优先执行
 *			  3、按照优先级调入执行 
 */
Node * getTask(List * pList,int T){
	if(ListIsEmpty(pList)){
		//fprintf(stderr,"You have not enter any task!\n");
		//exit(2);
		return NULL;
	}
	
	//更新优先级
 	UpdatePriority(pList,T); 
	
	Node * temp = *pList;
	Node * current = temp->next;
	while(current != NULL){
		//作业还没到达 
		if((current->item).ComeTime > T){
			current = current->next;
			continue;
		}
		//情况1、若干作业同时到达，短作业优先调入执行
		if((temp->item).ComeTime == (current->item).ComeTime && (temp->item).ServerTime > (current->item).ServerTime){
			temp = current; 
			current = current->next;
			continue; 
		}
		//情况2、若干作业要求执行时间相同，先到作业优先执行
		if((temp->item).ServerTime	== (current->item).ServerTime && (temp->item).ComeTime > (current->item).ComeTime){
			temp = current; 
			current = current->next;
			continue;
		}
		
	    //情况3、按照优先级调入执行 
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