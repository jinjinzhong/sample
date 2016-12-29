#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "list.h"
#include "list.c"

//ÊäÈë×÷ÒµÐÅÏ¢ 
void InputTask(List * pList);
//×ª»»Ê±¼ä
int StrToTime(char * str_time); 
void TimeToStr(int int_time,char * str_time);
//ÅÐ¶ÏÄ³¸ö node ÊÇ·ñ´æÔÚÔÚÁ´±íÖÐ
bool NodeIsInList(Node * pNode,List * pList); 
//ÏÈÀ´ÏÈ·þÎñµ÷¶ÈËã·¨
void FCFS(List * pList); 
//°´×î¶Ì×÷ÒµÓÅÏÈ
void SJF(List * pList); 
//×îÐ¡×÷ÒµÓÅÏÈ
void MINJF(List * pList);

int main(void){
	List taskList;
	
	InitializeList(&taskList);
	if(ListIsFull(&taskList)){
		fprintf(stderr,"No memory available!Bye!\n");
		exit(1);
	}
	
	InputTask(&taskList);
	
	//ÏÈÀ´ÏÈ·þÎñ 
	FCFS(&taskList);
	//°´×î¶Ì×÷ÒµÓÅÏÈ
	//SJF(&taskList); 
	//°´×îÐ¡×÷ÒµÓÅÏÈ
	//MINJF(&taskList); 
	
	//ÊÍ·ÅÄÚ´æ 
	EmptyTheList(&taskList);
	return 0;
}

void InputTask(List * pList){
	Item temp;
	char str_time[10]; 
	int num = 0;
	char ch;
	
	puts("job_name submit_time run_time job_space (Empty line to finish!)");
	do{
		//¿ÕÐÐÍË³ö 
		if((ch = getchar()) == '\n'){
			break;
		}
		
		num ++;
		temp.jobNum = num;
		temp.jobName[0] = ch;
		scanf("%s %s %d %d",&(temp.jobName[1]),str_time,&(temp.runTime),&(temp.jobSpace));
	
		//Çå³ýÊäÈëÏî 
		while(getchar() != '\n'){
			continue;
		}
		
		temp.submitTime = StrToTime(str_time);
		//printf("%d %s %d %d %d\n",temp.jobNum,temp.jobName,temp.submitTime,temp.runTime,temp.jobSpace);
		
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

int StrToTime(char * str_time){
	int min,sec,sum = 0;
	sscanf(str_time,"%d:%d",&min,&sec);
	sum = 60 * min + sec;
	return sum;
}

void TimeToStr(int int_time,char * str_time){
	int min = int_time/60;
	int sec = int_time%60;
	sprintf(str_time,"%02d:%02d\0",min,sec);         
}

//ÅÐ¶ÏÄ³¸ö node ÊÇ·ñ´æÔÚÔÚÁ´±íÖÐ
bool NodeIsInList(Node * pNode,List * pList){
	Node * temp = *pList;
	while(temp != NULL){
		if((temp->item).jobNum == (pNode->item).jobNum){
			return true;
		}
		temp = temp->next;
	}
	return false;
}


//ÏÈÀ´ÏÈ·þÎñµ÷¶ÈËã·¨ 
void FCFS(List * pList){
	int T = 0;
	Node * temp;
	char str_submit_time[10];
	char str_wait_time[10];
	puts("job_num job_name submit_time run_time job_space wait_time:");
	while(!ListIsEmpty(pList)){
		temp = *pList;
		Node * current = temp->next;
		while(current != NULL){
			if((temp->item).submitTime > (current->item).submitTime){
				temp = current;
			}
			current = current->next;
		}
		if(T == 0 || T <= (temp->item).submitTime){
			T = (temp->item).submitTime;
		}
		
		TimeToStr((temp->item).submitTime,str_submit_time);
		TimeToStr(T-(temp->item).submitTime,str_wait_time);
		printf("%d %s %s %d %d %s\n",(temp->item).jobNum,(temp->item).jobName,str_submit_time,(temp->item).runTime,(temp->item).jobSpace,str_wait_time);
		T += (temp->item).runTime;
		DeleteNode(pList,temp);
	}
}

//°´×î¶Ì×÷ÒµÓÅÏÈ
void SJF(List * pList){
	int T = 0;
	//´æ·ÅÂú×ãµ±Ç°Ê±¼äÏÂÔËÐÐµÄ×÷Òµ 
 	List tempList;
 	InitializeList(&tempList);
	if(ListIsFull(&tempList)){
		fprintf(stderr,"No memory available!Bye!\n");
		exit(1);
	}
	
 	Node * temp;
 	char str_submit_time[10];
	char str_wait_time[10];
	puts("job_num job_name submit_time run_time job_space wait_time:");
	while(!ListIsEmpty(pList)){
		//½«Âú×ãµ±Ç°Ê±¼äÏÂÔËÐÐµÄ×÷Òµ´æµ½ÁÙÊ±ÁÐ±íÖÐ
		temp = *pList;
		while(temp != NULL){
			if((temp->item).submitTime <= T  && !NodeIsInList(temp,&tempList)){
				AddItem(temp->item,&tempList);
			}
			temp = temp->next;
		}
		
		//ÖØÖÃtemp 
		temp = NULL;
		Node * current;
		//Èç¹ûÁÙÊ±ÁÐ±íÖÐ²»´æÔÚ×÷Òµ£¬ÔòÌôÑ¡×îÔçÌá½»µÄ×÷Òµ 
		if(ListIsEmpty(&tempList)){
			temp = *pList;
			current = temp->next; 
			while(current != NULL){
				if((temp->item).submitTime > (current->item).submitTime){
					temp = current;
				}
				current = current->next;
			}
		}
		//Èç¹ûÁÙÊ±ÁÐ±íÖÐ´æÔÚ×÷Òµ£¬ÔòÌôÑ¡ÔËÐÐÊ±¼ä×î¶ÌµÄ×÷Òµ
		else{
			temp = tempList;
			current = temp->next;
			    
			while(current != NULL){
				if((temp->item).runTime > (current->item).runTime){
					temp = current;
				}
				current = current->next;
			}
			current = *pList;
			while((current->item).jobNum != (temp->item).jobNum){
				current = current->next;
			}
			Node * pt = temp;
			//½«tempÖ¸Ïò*pListÖÐµÄ½áµã¶ø²»ÊÇtempListÖÐµÄ½áµã 
			temp = current;
			DeleteNode(&tempList,pt); 
		}
		 
		if(T == 0 || T <= (temp->item).submitTime){
			T = (temp->item).submitTime;
		}
		
		TimeToStr((temp->item).submitTime,str_submit_time);
		TimeToStr(T-(temp->item).submitTime,str_wait_time);
		printf("%d %s %s %d %d %s\n",(temp->item).jobNum,(temp->item).jobName,str_submit_time,(temp->item).runTime,(temp->item).jobSpace,str_wait_time);
		T += (temp->item).runTime;
		DeleteNode(pList,temp);
	}
}
//×îÐ¡×÷ÒµÓÅÏÈ
void MINJF(List * pList){
	int T = 0;
	//´æ·ÅÂú×ãµ±Ç°Ê±¼äÏÂÔËÐÐµÄ×÷Òµ 
 	List tempList;
 	InitializeList(&tempList);
	if(ListIsFull(&tempList)){
		fprintf(stderr,"No memory available!Bye!\n");
		exit(1);
	}
	
 	Node * temp;
 	char str_submit_time[10];
	char str_wait_time[10];
	puts("job_num job_name submit_time run_time job_space wait_time:");
	while(!ListIsEmpty(pList)){
		//½«Âú×ãµ±Ç°Ê±¼äÏÂÔËÐÐµÄ×÷Òµ´æµ½ÁÙÊ±ÁÐ±íÖÐ
		temp = *pList;
		while(temp != NULL){
			if((temp->item).submitTime <= T  && !NodeIsInList(temp,&tempList)){
				AddItem(temp->item,&tempList);
			}
			temp = temp->next;
		}
		
		//ÖØÖÃtemp 
		temp = NULL;
		Node * current;
		//Èç¹ûÁÙÊ±ÁÐ±íÖÐ²»´æÔÚ×÷Òµ£¬ÔòÌôÑ¡×îÔçÌá½»µÄ×÷Òµ 
		if(ListIsEmpty(&tempList)){
			temp = *pList;
			current = temp->next; 
			while(current != NULL){
				if((temp->item).submitTime > (current->item).submitTime){
					temp = current;
				}
				current = current->next;
			}
		}
		//Èç¹ûÁÙÊ±ÁÐ±íÖÐ´æÔÚ×÷Òµ£¬ÔòÌôÑ¡ÄÚ´æµÄ×÷Òµ
		else{
			temp = tempList;
			current = temp->next;
			    
			while(current != NULL){
				if((temp->item).jobSpace > (current->item).jobSpace){
					temp = current;
				}
				current = current->next;
			}
			current = *pList;
			while((current->item).jobNum != (temp->item).jobNum){
				current = current->next;
			}
			Node * pt = temp;
			//½«tempÖ¸Ïò*pListÖÐµÄ½áµã¶ø²»ÊÇtempListÖÐµÄ½áµã 
			temp = current;
			DeleteNode(&tempList,pt); 
		}
		 
		if(T == 0 || T <= (temp->item).submitTime){
			T = (temp->item).submitTime;
		}
		
		TimeToStr((temp->item).submitTime,str_submit_time);
		TimeToStr(T-(temp->item).submitTime,str_wait_time);
		printf("%d %s %s %d %d %s\n",(temp->item).jobNum,(temp->item).jobName,str_submit_time,(temp->item).runTime,(temp->item).jobSpace,str_wait_time);
		T += (temp->item).runTime;
		DeleteNode(pList,temp);
	}
}