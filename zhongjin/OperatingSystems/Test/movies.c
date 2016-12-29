/* list.c -- ʹ�ó����������ͣ�ADT���������� */
#include <stdio.h> 
#include <stdlib.h>
#include "list.h"
#include "list.c"

void showMovies(Item item);
char * s_gets(char * st,int n);
void InputMovies(List * pList);

int main(void){
	List movies;
	Item temp;
	char ch;
	
	/*��ʼ������*/
	InitializeList(&movies);
	if(ListIsFull(&movies)){
		fprintf(stderr,"No memory available!Bye!\n");
		exit(1);
	}
	
	/*��ȡ�û����벢�洢*/
	puts("Enter first movie title");
	
	
	while(s_gets(temp.title,TSIZE) != NULL && temp.title[0] != '\0'){
		puts("Enter your rating <0-10>:");
		scanf("%d",&temp.rating);
		while(getchar() != '\n'){
			continue;
		}
		if(AddItem(temp,&movies) == false){
			fprintf(stderr,"Problem allocating memory\n");
			break;
		}
		if(ListIsFull(&movies)){
			puts("The list is now full!");
			break;
		}
		puts("Enter next movie title (empty line to stop!):");
	} 
	
	
	//InputMovies(&movies);
	/*��ʾ*/
	if(ListIsEmpty(&movies)){
		printf("No data entered!\n");
	}else{
		printf("Here is the movies list:\n");
		Traverse(&movies,showMovies);
	}
	printf("You entered %d movies.\n",ListItemCount(&movies));
	
	
	/*����*/
	EmptyTheList(&movies);
	printf("Bye!\n");

	return 0;	
}

void showMovies(Item item){
	printf("Movie:%s Rating:%d.\n",item.title,item.rating);
}

char * s_gets(char * sh,int n){
	char * ret_val;
	char * find;
	
	ret_val = fgets(sh,n,stdin);
	if(ret_val){
		find = strchr(sh,'\n');	//���һ��з�
		if(find){
			*find = '\0';
		}else{
			while(getchar() != '\n'){
				continue;	//��������е�ʣ������ 
			}
		}
	}
	return ret_val; 
}

void InputMovies(List * pList){
	Item temp;
	char ch;
	
	puts("movie rating(empty line to stop):");
	
	do{
		if((ch = getchar()) == '\n'){
			break;
		}
		temp.title[0] = ch;
		scanf("%s %d",&(temp.title[1]),&(temp.rating));
	
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