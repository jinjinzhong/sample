#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

//72,80,75,77�Ƿ������Ӧ�ļ�ֵ
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define SNAKE 1
#define FOOD 2
#define BAR 3

//��ʼ����ͼ
char map[17][17] = {0};
//��ʼ����ͷ����
unsigned char snake[50] = {77};
//��ʼ��ʳ������
unsigned char food = 68;
//�߳�
char len = 1;

//�洢����������x��y��ת������
void tran(unsigned char num,unsigned char * x,unsigned char * y);
//��ʼ����Ϸ
void init_game(void); 
//��ȡ��������ע�⵱�����ȳ���һ��ʱ���ܻ�ͷ��
int get_dir(int old_dir);
//�ƶ�������(��Ϸ�󲿷�����������)
void move_snake(int dir);
//�����и�����ʳ��ĺ�����generate_food()����������������ɺ�������ʳ������
unsigned char generate_food(void); 
//�ж�������ĺ���(�ж������Ƿ�ײ���߽������ʳ)
int isalive(void);
//������ƶ��������е� ��x��y��λ��
void gotoxy(unsigned char x,unsigned char y); 


int main(void){
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
	return 0;
}

//������num�洢x/y���꣬num��char���ͣ�ռ8λ��xռǰ��λ��yռ����λ��x/y��Χ��0-15�� 
//���������Ե���17*17��ĵ�ͼ�������ͼ������num�����Ϳ�����int,long
//��Ȼ��x/y����������洢�� 
void tran(unsigned char num,unsigned char * x,unsigned char * y){
	*x = num >> 4;	
	*y = (unsigned char)(num << 4) >> 4;	//ע������Ҫ����ǿ������ת��
}

//��ʼ����Ϸ ����ӡ��ʼ״̬�� 
void init_game(void)
{
    int i, j;
    unsigned char x, y, fx, fy;
    tran(snake[0], &x, &y);
    tran(food, &fx, &fy);
    for (j = 0; j<17; j++) {
        for (i = 0; i<17; i++) {
        	//��ӡΧǽ 
            if (i == 0 || i == 16 || j == 0 || j == 16){
                putchar('#');
            }
            //��ӡ��ͷ 
            else if (i == x&&j == y){
            	putchar('*');
            }
            //��ӡʳ�� 
            else if (i == fy&&j == fx){	
            	putchar('$');
            }
            //�հ׵ط� 
            else{
                putchar(' ');
            }
        }
        putchar('\n');
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

void move_snake(int dir){
	int last = snake[0],current;	//last��current����֮��������ĸ���
    int i;
    int grow=0;		//�ж��Ƿ�Ҫ������
    unsigned char x, y, fx, fy;		//��������ʳ������
    tran(food, &fx, &fy);	//ʳ������ 
    tran(snake[0], &x, &y);	//��ͷ���� 
    switch (dir){			//������ͷ���꣨����ԭ�������Ͻǣ� 
	    case UP:
	        y--;
	        break;
	    case DOWN:
	        y++;
	        break;
	    case LEFT:
	        x--;
	        break;
	    case RIGHT:
	        x++;
	        break;
    }
    //��λ�ֻ���� 
    snake[0] = ((x ^ 0) << 4) ^ y;		//��x,y����һ����
    
    //�߳Ե���ʳ�� 
    if (snake[0] == food) {
        grow = 1;
        food = generate_food();		//������ʳ��
    }
    
    for (i = 0; i<len; i++) {		//���ƶ��Ĺؼ���ͨ������ͷԭ�������긳���ڶ��ڣ�ԭ���ĵڶ��ڸ��������ڣ�������ȥ�����������ĸ���
        if (i == 0)		//���ֻ��ͷ����������Ϊǰ���Ѹ�����ͷ����
            continue;
        current = snake[i];		//����ǰ�������߽�����洢��current��
        snake[i] = last;		//��ɵ�ǰ�����߽�����ĸ���
        last = current;		//last��¼������һ�β����߽ڵ����꣬��β����Ѿ��������ʰ�current����last
    }
    
    gotoxy(x, y);		//������ƶ���ָ��λ�� 
    putchar('*');		//��ӡ�µ���ͷ
	
	if (grow) {			//���Ҫ���ڵĻ��Ͳ�ȥ���ɵ���β
        snake[len] = last;
        len++;
        tran(food, &fx, &fy);	// ��ӡʳ��(�����Ѿ������µ�ʳ������)
        gotoxy(fx,fy);
        putchar('$');
    }else {
    	//����Ϊ�˱��⵱������Ƴ�һ��Ȧ��ʱ�������β˳��Ҳ����ͷ������� 
    	if(snake[0] != last){
	    	tran(last, &x, &y);
        	gotoxy(x, y);
        	putchar(' ');	//ȥ���ɵ���β
	    }
    }
    //������һֱ������β����ʳ�� �� 
    gotoxy(0,17);
	Sleep(500);
}

unsigned char generate_food(void)
{
    unsigned char food_,fx,fy;
    int in_snake=0,i;
    //�Ե�ǰʱ��Ϊ�����ṩ���ӹ�rand()�������ɸ�Ϊ�������
    srand((unsigned int)time(NULL));
    //ѭ�������ڱ߽����Ҳ��������ϵ�ʳ�� 
    do {
        food_ = rand() % 255;
        tran(food_, &fx, &fy);
        for (i = 0; i < len; i++){ 
            if (food_ == snake[i]){ 
                in_snake = 1;
            }
		} 
    } while (fx == 0 || fx == 16 || fy == 0 || fy == 16 || in_snake);
    return food_;
}

int isalive(void)
{    
    int self_eat = 0, i;
    unsigned char x, y;
    tran(snake[0], &x, &y);
    for (i = 1; i < len; i++){
        if (snake[0] == snake[i]){
            self_eat = 1;
        }
    }
    //��ͷײ�߽���߳Ե��Լ� �������� 
    return (x == 0 || x == 16 || y == 0 || y >= 16 || self_eat) ? 0 : 1;
}

void gotoxy(unsigned char x,unsigned char y){
	//COORD��Windows API�ж����һ�ֽṹ����ʾһ���ַ��ڿ���̨��Ļ�ϵ�����
	COORD cor;
	//��� 
    HANDLE hout;
    //�趨����Ҫ��λ�������� 
    cor.X = x;
    cor.Y = y;
    //GetStdHandle������ȡһ��ָ���ض���׼�豸�ľ����������׼���룬��׼����ͱ�׼����
	//STD_OUTPUT_HANDLE���Ǵ����׼�����Ҳ������ʾ�����ĺ� 
    hout = GetStdHandle(STD_OUTPUT_HANDLE);
    //SetConsoleCursorPosition�����������ÿ���̨����λ��
    SetConsoleCursorPosition(hout, cor);
}