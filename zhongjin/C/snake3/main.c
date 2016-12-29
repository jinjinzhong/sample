#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

//72,80,75,77是方向键对应的键值
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define SNAKE 1
#define FOOD 2
#define BAR 3

//用链表实现 
 
//蛇结点 
typedef struct node{
	//COORD是Windows API中定义的一种结构，表示一个字符在控制台屏幕上的坐标
	COORD cor;
	struct node * next;
}snake_node;

//初始化食物坐标
COORD food = {3,5};

//初始化蛇头
snake_node * snake_head;

//蛇长
char len = 1; 

//坐标比较函数(程序中有多次的坐标比较)
int cor_cmp(COORD pt1,COORD pt2); 
//将光标移动到命令行的 （x，y）位置，参数是一个坐标结构体 
void gotoxy(COORD pt);
//初始化游戏
void init_game(void);
//生成食物坐标
COORD generate_food(void); 
//移动蛇 
void move_snake(int dir); 
//释放申请的内存空间 
void free_node(snake_node * n);
//获取方向函数（注意当蛇身长度超过一节时不能回头）
int get_dir(int old_dir);
//判断蛇死活的函数(判断了蛇是否撞到边界或者自食)
int isalive(void);

int main(void) {
	int dir = UP;	//初始方向默认向上，UP是我们定义的宏
	init_game();	//初始化游戏 
	while(1){
		dir = get_dir(dir);		//获取方向(我们摁下的方向)
		move_snake(dir);		//移动蛇身
		if(!isalive()){			//判断蛇的生命状态
			break;
		}
	}
	//清除屏幕 
	system("cls");
	printf("Game Over!\n");
	//释放申请的内存空间 
	free_node(snake_head); 
	
	return 0;
}

void init_game(void){
	//初始化蛇头 
	snake_head = (snake_node *)malloc(sizeof(snake_node));
	(snake_head->cor).X = 3;
	(snake_head->cor).Y = 9;
	snake_head->next= NULL;
	
	int i,j;	//i,j对应x,y轴  
	for(j = 0;j < 17;j ++){
		for (i = 0; i<17; i++) {
            if (i == 0 || i == 16 || j == 0 || j == 16)
            {
            	putchar('#');
            }
            else if (i == (snake_head->cor).X&&j == (snake_head->cor).Y)
            {
            	putchar('*');
            }
            else if (i == food.X&&j == food.Y)
            {
            	putchar('$');
            }
            else
            {
            	putchar(' ');
            }
        }
        putchar('\n');
	}
}

COORD generate_food(void){
	COORD food_;
    snake_node * p = NULL;		//把定义的指针初始为NULL是一个好习惯
    int in_snake = 0;
    //以当前时间为参数提供种子供rand()函数生成更为随机的数
    srand((unsigned int)time(NULL));
    //循环产生在边界内且不在蛇身上的食物
    do {
        food_.X = rand() % 16;
        food_.Y = rand() % 16;
        for (p = snake_head; p != NULL; p = p->next){
        	//在蛇身上 
            if (cor_cmp(food_,p->cor)){
         		in_snake = 1;   	
            }
        }
                
    } while (food_.X == 0 || food_.X == 16 || food_.Y == 0 || food_.Y == 16 || in_snake);
    
	return food_;
}

int cor_cmp(COORD pt1, COORD pt2)
{
    return (pt1.X == pt2.X && pt1.Y == pt2.Y);
}

void gotoxy(COORD pt)
{
	//句柄 
    HANDLE hout;
    //GetStdHandle函数获取一个指向特定标准设备的句柄，包括标准输入，标准输出和标准错误。
	//STD_OUTPUT_HANDLE正是代表标准输出（也就是显示屏）的宏 
    hout = GetStdHandle(STD_OUTPUT_HANDLE);
    //SetConsoleCursorPosition函数用于设置控制台光标的位置
    SetConsoleCursorPosition(hout, pt);
}

/*
//像数组一样移动蛇
//通过将蛇头原来的坐标赋给第二节，原来的第二节赋给第三节，依次下去，完成蛇坐标的更新 
void move_snake(int dir)
{
    snake_node * p = NULL;
    COORD last = snake_head->cor, current;
    int grow = 0;
    
    switch (dir) {
	    case UP:
	        (snake_head->cor).Y--;
	        break; 
	    case DOWN:
	        (snake_head->cor).Y++;
	        break;
	    case LEFT:
	        (snake_head->cor).X--;
	        break;
	    case RIGHT:
	        (snake_head->cor).X++;
	        break;
    }
    
    //蛇吃到食物 
    if (cor_cmp(snake_head->cor,food)) {
        grow = 1;
        //生成新的食物 
        food = generate_food();
    }
    
    for (p = snake_head->next; p != NULL; p = p->next) {
        current = p->cor;
        p->cor = last;
        last = current;
    }
    
    gotoxy(snake_head->cor);
    putchar('*');
    
    if (grow) {
        //找到蛇尾 p
        p = snake_head;
        while(p->next != NULL){
        	p = p->next;
        }
        
        p->next = (snake_node *)malloc(sizeof(snake_node));		//在蛇尾追加节点
        p->next->cor = last;
        p->next->next = NULL;
        
        len++;
        
        //打印新的食物 
        gotoxy(food);
        putchar('$');
    }else {
	//这是为了避免当你把蛇绕成一个圈的时候（蛇头紧跟蛇尾，没咬到），清除蛇尾顺便也把蛇头清除掉了 
		if(!cor_cmp(snake_head->cor,last)){
        	gotoxy(last);
        	putchar(' ');
        }
    }

	//避免光标一直跟着蛇尾（或食物 ）
	COORD foot = {0,17};	//将光标置于左下角 
    gotoxy(foot);
    
    Sleep(500);
}*/


//另一种更新坐标的方法是每次移动时申请一块新的内存空间存储移动后的蛇头坐标并让snake_head指针指向它，
//如果蛇不长节的话就释放蛇尾的内存空间，通俗来说就是添头去尾,这样就避免了蛇中间节点的移动过程 

void move_snake(int dir)
{
    snake_node * p,* t = NULL;
    snake_node * newh = NULL;
    newh = (snake_node *)malloc(sizeof(snake_node));	//为新蛇头开辟内存空间
    newh->cor = snake_head->cor;	//把旧头的坐标赋给新头
    newh->next = snake_head;		//把新头的next指针指向旧头
    snake_head = newh;				//让头指针指向新开辟的内存空间
    
	int grow = 0;
    
    switch (dir) {
	    case UP:
	        (snake_head->cor).Y--;
	        break; 
	    case DOWN:
	        (snake_head->cor).Y++;
	        break;
	    case LEFT:
	        (snake_head->cor).X--;
	        break;
	    case RIGHT:
	        (snake_head->cor).X++;
	        break;
    }
    //蛇吃到了食物 
    if (cor_cmp(snake_head->cor,food)) {
        grow = 1;
        //生成新的食物 
        food = generate_food();
    }
    
    gotoxy(snake_head->cor);
    putchar('*');
    
    //如果长节的话不再对链表进行操作
    if (grow) {
        len ++;
        gotoxy(food);
        putchar('$');
    }
    //不长节的话就得删除蛇尾
    else {
    	//找到倒数第二节
        p = snake_head;
		while(p->next->next != NULL){
			p = p->next;
		} 
		//记录下最后一节的地址
        t = p->next;
        //将倒数第二节的next指针赋值为NULL
        p->next = NULL;
        
        //这是为了避免当你把蛇绕成一个圈的时候（蛇头紧跟蛇尾，没咬到），清除蛇尾顺便也把蛇头清除掉了 
        if(!cor_cmp(snake_head->cor,t->cor)){
        	gotoxy(t->cor);
        	putchar(' ');
        }
        
        free(t);		//释放蛇尾的内存空间
    }
    
    //避免光标一直跟着蛇尾（或食物 ）
	COORD foot = {0,17};	//将光标置于左下角 
    gotoxy(foot);
    
    Sleep(500);
}

void free_node(snake_node * h){
	snake_node * p = h,* q;
    while(p != NULL){
    	q = p;
		p = p->next;
		free(q);	
    }
}

int get_dir(int old_dir){
	
	int new_dir = old_dir;
	
	//用kbhit()与getch()组合实现键盘响应
	//kbhit() 检查当前是否有键盘输入，若有则返回一个非0值，否则返回0
	//getch() 用ch=_getch();会等待你按下任意键之后，把该键字符所对应的ASCII码赋给ch,再执行下面的语句。 
	if(_kbhit()){
		_getch();
		new_dir = _getch();		//getch()函数要使用两次,原因是因为第一次返回的值指示该键扩展的字符，第二次调用才返回实际的键代码
		
		//如果蛇身长度大于1，则不能回头，如果摁回头方向，则按原来方向走 
		if(len > 1 && (abs(new_dir - old_dir) == 2 || abs(new_dir - old_dir) == 8)){
			new_dir = old_dir;
		}
	}
	return new_dir;
}

int isalive(void){
	int self_eat = 0;
    snake_node * p = NULL;
    for (p = snake_head->next; p != NULL; p = p->next)
    {
    	if (cor_cmp(p->cor, snake_head->cor))
     	{
			self_eat = 1; 
 		} 
    }
    
    return ((snake_head->cor).X == 0 || (snake_head->cor).X == 16 || (snake_head->cor).Y == 0 || (snake_head)->cor.Y >= 16 || self_eat) ? 0 : 1;
}
