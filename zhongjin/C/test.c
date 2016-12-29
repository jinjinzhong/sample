#include <stdio.h>
// #include <conio.h>	//getch() kbhit() 
#include <stdlib.h>	//system() 
// #include <windows.h>	//Sleep() 
#include <string.h>
int main(void){
	//char ch;
	//"ESC"按键等于27 
	//while(ch != 27){
	//		printf("按ESC键退出！\n");
	//		if(kbhit()){
	//			ch = getch();
	//		}
	//		//Sleep(1000);
	//	}
	//	printf("END!\n");
	//	system("pause");
	
	//if(!kbhit()){
		//getch();
		//ch = getch();
	//}
	//printf("%d\n",ch);
	
	//int x = 1;
//	int y = 9;
//	int i,j;
//	for(j = 0;j < 10;j ++){
//		for(i = 0;i < 10;i ++){
//			if(i == x && j == y){
//				putchar('@');
//			}else{
//				putchar('!');
//			}
//		}
//		putchar('\n');
//	}
	
	//COORD cor;
//    HANDLE hout;
//    cor.X = 10;
//    cor.Y = 20;
//    hout = GetStdHandle(STD_OUTPUT_HANDLE);
//    SetConsoleCursorPosition(hout, cor);
//	printf("zhongjin\n");

	//typedef struct node{
		//COORD是Windows API中定义的一种结构，表示一个字符在控制台屏幕上的坐标
		//COORD cor;
		//struct node * next;
	// } snake_node;
	

	/*
FILE * stream;
	char msg[] = "this is a test";
	char buf[20];

	if((stream = fopen("DUMMY.FIL","w+")) == NULL){
		fprintf(stderr,"Can't open output file\n");
		return 0;
	}
	fwrite(msg,1,strlen(msg) + 1,stream);

	fseek(stream,0,SEEK_SET);

	fread(buf,1,strlen(msg) + 1,stream);

	printf("%s\n",buf);
	fclose(stream);*/

	return 0;
}

