#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

//72,80,75,77�Ƿ������Ӧ�ļ�ֵ
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define SNAKE 1
#define FOOD 2
#define BAR 3

//������ʵ�� 
 
//�߽�� 
typedef struct node{
	//COORD��Windows API�ж����һ�ֽṹ����ʾһ���ַ��ڿ���̨��Ļ�ϵ�����
	COORD cor;
	struct node * next;
}snake_node;

//��ʼ��ʳ������
COORD food = {3,5};

//��ʼ����ͷ
snake_node * snake_head;

//�߳�
char len = 1; 

//����ȽϺ���(�������ж�ε�����Ƚ�)
int cor_cmp(COORD pt1,COORD pt2); 
//������ƶ��������е� ��x��y��λ�ã�������һ������ṹ�� 
void gotoxy(COORD pt);
//��ʼ����Ϸ
void init_game(void);
//����ʳ������
COORD generate_food(void); 
//�ƶ��� 
void move_snake(int dir); 
//�ͷ�������ڴ�ռ� 
void free_node(snake_node * n);
//��ȡ��������ע�⵱�����ȳ���һ��ʱ���ܻ�ͷ��
int get_dir(int old_dir);
//�ж�������ĺ���(�ж������Ƿ�ײ���߽������ʳ)
int isalive(void);

int main(void) {
	int dir = UP;	//��ʼ����Ĭ�����ϣ�UP�����Ƕ���ĺ�
	init_game();	//��ʼ����Ϸ 
	while(1){
		dir = get_dir(dir);		//��ȡ����(�������µķ���)
		move_snake(dir);		//�ƶ�����
		if(!isalive()){			//�ж��ߵ�����״̬
			break;
		}
	}
	//�����Ļ 
	system("cls");
	printf("Game Over!\n");
	//�ͷ�������ڴ�ռ� 
	free_node(snake_head); 
	
	return 0;
}

void init_game(void){
	//��ʼ����ͷ 
	snake_head = (snake_node *)malloc(sizeof(snake_node));
	(snake_head->cor).X = 3;
	(snake_head->cor).Y = 9;
	snake_head->next= NULL;
	
	int i,j;	//i,j��Ӧx,y��  
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
    snake_node * p = NULL;		//�Ѷ����ָ���ʼΪNULL��һ����ϰ��
    int in_snake = 0;
    //�Ե�ǰʱ��Ϊ�����ṩ���ӹ�rand()�������ɸ�Ϊ�������
    srand((unsigned int)time(NULL));
    //ѭ�������ڱ߽����Ҳ��������ϵ�ʳ��
    do {
        food_.X = rand() % 16;
        food_.Y = rand() % 16;
        for (p = snake_head; p != NULL; p = p->next){
        	//�������� 
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
	//��� 
    HANDLE hout;
    //GetStdHandle������ȡһ��ָ���ض���׼�豸�ľ����������׼���룬��׼����ͱ�׼����
	//STD_OUTPUT_HANDLE���Ǵ����׼�����Ҳ������ʾ�����ĺ� 
    hout = GetStdHandle(STD_OUTPUT_HANDLE);
    //SetConsoleCursorPosition�����������ÿ���̨����λ��
    SetConsoleCursorPosition(hout, pt);
}

/*
//������һ���ƶ���
//ͨ������ͷԭ�������긳���ڶ��ڣ�ԭ���ĵڶ��ڸ��������ڣ�������ȥ�����������ĸ��� 
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
    
    //�߳Ե�ʳ�� 
    if (cor_cmp(snake_head->cor,food)) {
        grow = 1;
        //�����µ�ʳ�� 
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
        //�ҵ���β p
        p = snake_head;
        while(p->next != NULL){
        	p = p->next;
        }
        
        p->next = (snake_node *)malloc(sizeof(snake_node));		//����β׷�ӽڵ�
        p->next->cor = last;
        p->next->next = NULL;
        
        len++;
        
        //��ӡ�µ�ʳ�� 
        gotoxy(food);
        putchar('$');
    }else {
	//����Ϊ�˱��⵱������Ƴ�һ��Ȧ��ʱ����ͷ������β��ûҧ�����������β˳��Ҳ����ͷ������� 
		if(!cor_cmp(snake_head->cor,last)){
        	gotoxy(last);
        	putchar(' ');
        }
    }

	//������һֱ������β����ʳ�� ��
	COORD foot = {0,17};	//������������½� 
    gotoxy(foot);
    
    Sleep(500);
}*/


//��һ�ָ�������ķ�����ÿ���ƶ�ʱ����һ���µ��ڴ�ռ�洢�ƶ������ͷ���겢��snake_headָ��ָ������
//����߲����ڵĻ����ͷ���β���ڴ�ռ䣬ͨ����˵������ͷȥβ,�����ͱ��������м�ڵ���ƶ����� 

void move_snake(int dir)
{
    snake_node * p,* t = NULL;
    snake_node * newh = NULL;
    newh = (snake_node *)malloc(sizeof(snake_node));	//Ϊ����ͷ�����ڴ�ռ�
    newh->cor = snake_head->cor;	//�Ѿ�ͷ�����긳����ͷ
    newh->next = snake_head;		//����ͷ��nextָ��ָ���ͷ
    snake_head = newh;				//��ͷָ��ָ���¿��ٵ��ڴ�ռ�
    
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
    //�߳Ե���ʳ�� 
    if (cor_cmp(snake_head->cor,food)) {
        grow = 1;
        //�����µ�ʳ�� 
        food = generate_food();
    }
    
    gotoxy(snake_head->cor);
    putchar('*');
    
    //������ڵĻ����ٶ�������в���
    if (grow) {
        len ++;
        gotoxy(food);
        putchar('$');
    }
    //�����ڵĻ��͵�ɾ����β
    else {
    	//�ҵ������ڶ���
        p = snake_head;
		while(p->next->next != NULL){
			p = p->next;
		} 
		//��¼�����һ�ڵĵ�ַ
        t = p->next;
        //�������ڶ��ڵ�nextָ�븳ֵΪNULL
        p->next = NULL;
        
        //����Ϊ�˱��⵱������Ƴ�һ��Ȧ��ʱ����ͷ������β��ûҧ�����������β˳��Ҳ����ͷ������� 
        if(!cor_cmp(snake_head->cor,t->cor)){
        	gotoxy(t->cor);
        	putchar(' ');
        }
        
        free(t);		//�ͷ���β���ڴ�ռ�
    }
    
    //������һֱ������β����ʳ�� ��
	COORD foot = {0,17};	//������������½� 
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
	
	//��kbhit()��getch()���ʵ�ּ�����Ӧ
	//kbhit() ��鵱ǰ�Ƿ��м������룬�����򷵻�һ����0ֵ�����򷵻�0
	//getch() ��ch=_getch();��ȴ��㰴�������֮�󣬰Ѹü��ַ�����Ӧ��ASCII�븳��ch,��ִ���������䡣 
	if(_kbhit()){
		_getch();
		new_dir = _getch();		//getch()����Ҫʹ������,ԭ������Ϊ��һ�η��ص�ֵָʾ�ü���չ���ַ����ڶ��ε��òŷ���ʵ�ʵļ�����
		
		//��������ȴ���1�����ܻ�ͷ���������ͷ������ԭ�������� 
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
