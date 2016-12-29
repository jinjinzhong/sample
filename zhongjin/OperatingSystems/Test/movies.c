/* list.c -- 使用抽象数据类型（ADT）风格的链表 */
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
	
	/*初始化链表*/
	InitializeList(&movies);
	if(ListIsFull(&movies)){
		fprintf(stderr,"No memory available!Bye!\n");
		exit(1);
	}
	
	/*获取用户输入并存储*/
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
	/*显示*/
	if(ListIsEmpty(&movies)){
		printf("No data entered!\n");
	}else{
		printf("Here is the movies list:\n");
		Traverse(&movies,showMovies);
	}
	printf("You entered %d movies.\n",ListItemCount(&movies));
	
	
	/*清理*/
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
		find = strchr(sh,'\n');	//查找换行符
		if(find){
			*find = '\0';
		}else{
			while(getchar() != '\n'){
				continue;	//清除输入行的剩余内容 
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