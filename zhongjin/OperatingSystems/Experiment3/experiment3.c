#include <stdio.h> 
#include <stdbool.h>
#include <ctype.h>
#include <CONIO.H>	//�ṩgetch() 
#define M 5	/*������*/
#define N 3	/*��Դ��*/

/*M�����̶�N����Դ�����Դ������*/
int MAX[M][N]={{7,5,3},{3,2,2},{9,0,2},{2,2,2},{4,3,3}};
/*ϵͳ������Դ��*/
int AVAILABLE[N]={10,5,7};
/*M�������Ѿ��õ�N����Դ����Դ��*/
int ALLOCATION[M][N]={{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}};
/*M�����̻���ҪN����Դ����Դ��*/
int NEED[M][N]={{7,5,3},{3,2,2},{9,0,2},{2,2,2},{4,3,3}};
//������Դ���� 
int Request[N]={0,0,0};

//��ʾ��������������� 
void showdata();
/*ϵͳ�Խ���k������Ӧ����Դ�����ı�*/
void changdata(int k);
/*ϵͳ�ܾ�����k�����󣬻ָ���Դ����*/
void rstordata(int k);
/*��ȫ�Լ�麯��*/
bool chkerr();

int main(void){
	int i = 0,j = 0; 
	bool loop = true;
	char flag = 'y';
	
	//����ʾ��ʼ���� 
	showdata();
	
	//ѭ��Ϊ����������Դ 
	while(tolower(flag) == 'y'){
		printf("��������������Դ�Ľ��̺ţ���0��");
		printf("%d",M-1);
		printf("��:");
		scanf("%d",&i);
		while(i < 0 || i > M-1){
			printf("����Ľ��̺Ų����ڣ���������!\n");
			printf("��������������Դ�Ľ��̺ţ���0��");
			printf("%d",M-1);
			printf("��:");
			scanf("%d",&i);
		}
	
		printf("���������");
		printf(" %d ",i);
		printf("�������Դ��\n");
		printf("���:A B C\n");
		printf("");
	 
	 	loop = true;
	 	
		//����������Դ�������淶��Ҫ���û��������� 
		while(loop){
		
			for(j=0;j<N;j++)
			{	
				scanf("%d",&Request[j]);
			
				if(Request[j]>NEED[i][j])
				{	
					printf(" %d ",i);
					printf("�Ž���");
					printf("�������Դ�� > ����");
					printf(" %d ",i);
					printf("����Ҫ");
					printf(" %c ",j + 65);
					printf("����Դ����Դ��!���벻��������!������ѡ��!\n");
				
					printf("���������");
					printf(" %d ",i);
					printf("�������Դ��\n");
					printf("���:A B C\n");
					printf("");
					
					//���������
					while(getchar() != '\n'){
						continue;
					} 
				
					break;
				}
				else if(Request[j]>AVAILABLE[j])
				{
					printf("����");
					printf(" %d ",i);
					printf("�������Դ������ϵͳ����");
					printf(" %c ",j + 65);
					printf("����Դ����Դ��!���벻��������!������ѡ��!\n");
						
					printf("���������");
					printf(" %d ",i);
					printf("�������Դ��\n");
					printf("���:A B C\n");
					printf("");
					
					//���������
					while(getchar() != '\n'){
						continue;
					} 
					
					break;
				}else{
					//������е���Դ���Ѿ���ȡ��ϣ�������ѭ���� 
					if(j == N - 1){
						loop = false;
					}
				}
			}
		}
		
		changdata(i);
		
		//��������ϰ�ȫ״̬�������ָ��Ѿ��������Դ 
		if(chkerr())
		{	
			rstordata(i);
			showdata();
		}
		else{ 
			showdata();
		} 
		printf("\n");
		
		printf("��'y'��'Y'������,�����˳�\n");
		flag=getch();
	}
	
	return 0;
}

/*��ʾ����*/
void showdata()
{
	int i,j;
	printf("ϵͳ������Դ����:\n");
	printf("***Available***\n");
	printf("��Դ���:A B C\n");
	printf("��Դ��Ŀ:");
	for(j=0;j<N;j++)
	{
		printf("%d ",AVAILABLE[j]);
	}
	printf("\n");
	printf("\n");
	printf("�����̻���Ҫ����Դ��:\n");
	printf("******Need******\n");
	printf("��Դ���:A B C\n");
	for(i=0;i<M;i++)
	{
		printf("");
		printf("%d",i);
		printf("�Ž���:");
		for(j=0;j<N;j++)
		{
			printf("%d ",NEED[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	printf("�������Ѿ��õ�����Դ��:\n");
	printf("***Allocation***\n");
	printf("��Դ���:A B C\n");
	for(i=0;i<M;i++)
	{
		printf("");
		printf("%d",i);
		printf("�Ž���:");
		for(j=0;j<N;j++)
		{
			printf("%d ",ALLOCATION[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

/*ϵͳ�Խ���k������Ӧ����Դ�����ı�*/
void changdata(int k)
{
	int j;
	for(j=0;j<N;j++)
	{
		AVAILABLE[j]=AVAILABLE[j]-Request[j];
		ALLOCATION[k][j]=ALLOCATION[k][j]+Request[j];
		NEED[k][j]=NEED[k][j]-Request[j];
	}
}
/*ϵͳ�ܾ�����k�����󣬻ָ���Դ����*/
void rstordata(int k)
{
	int j;
	for(j=0;j<N;j++)
	{
		AVAILABLE[j]=AVAILABLE[j]+Request[j];
		ALLOCATION[k][j]=ALLOCATION[k][j]-Request[j];
		NEED[k][j]=NEED[k][j]+Request[j];
	}
}

/*��ȫ�Լ�麯��*/
//�ڼٶ�������Դ������¼��ϵͳ�İ�ȫ��
//����ȫ����true 
bool chkerr()
{
	//WORK ��ʾϵͳ���ṩ���̼�����������Ҫ�ĸ�����Դ��Ŀ
	//FINISH ��ʾϵͳ�Ƿ����㹻����Դ��������̣�ʹ֮������ɣ���ʼʱ����Finish[i]:=false;�����㹻��Դ���������ʱ����Finish[i]:=true
	int WORK[N],FINISH[M],temp[M];//temp[]������¼���̰�ȫִ�е�˳��
	int i,j,m,k=0,count;
	for(i=0;i<M;i++)
 		FINISH[i]=false;	//���н���finish��ʼ��Ϊfalse (�����㹻��Դ���������ʱ����Finish[i]:=true)
	for(j=0;j<N;j++)
		WORK[j]=AVAILABLE[j];//��work�����ʼ��ΪAvailable 
	for(i=0;i<M;i++)
	{
		count=0;
		for(j=0;j<N;j++){
			if(FINISH[i]==false && NEED[i][j]<=WORK[j]){	
				count++;
			}
		}
		if(count==N)//�����̸�����Դ������NEED<=WORKʱ
		{
			for(m=0;m<N;m++){ 
				//ִ����Դ���� 
				WORK[m]=WORK[m]+ALLOCATION[i][m];
			} 
			//���̵õ��㹻����Դ 
			FINISH[i]=true;
			temp[k]=i;//��¼�����������Ľ���
			k++;
			//ΪʲôҪʹi=-1�أ�����Ϊ��һ�����̲�һ�����������㡣 
			i=-1;
		}
	}
	//ֻ�����еĽ��̵�finish����trueʱ�����ʾϵͳ���ڰ�ȫ״̬ 
	for(i=0;i<M;i++){ 
		if(FINISH[i]==false)
		{
			printf("ϵͳ����ȫ!!!������Դ���벻�ɹ�!!!\n");
			return true;
		}
	} 
	printf("\n");
	printf("����ȫ�Լ�飬ϵͳ��ȫ�����η���ɹ���\n");
	printf("\n");
	printf("���ΰ�ȫ���У�");
	for(i=0;i<M;i++)//��ӡ��ȫϵͳ�Ľ��̵���˳��
	{
		printf("����");
		printf("%d",temp[i]);
		if(i<M-1)
			printf("->");
	}
	printf("\n");
	//ϵͳ���ڰ�ȫ״̬ 
	return false;

}
