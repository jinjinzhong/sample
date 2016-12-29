#include <stdio.h> 
#include <stdbool.h>
#include <ctype.h>
#include <CONIO.H>	//提供getch() 
#define M 5	/*进程数*/
#define N 3	/*资源数*/

/*M个进程对N类资源最大资源需求量*/
int MAX[M][N]={{7,5,3},{3,2,2},{9,0,2},{2,2,2},{4,3,3}};
/*系统可用资源数*/
int AVAILABLE[N]={10,5,7};
/*M个进程已经得到N类资源的资源量*/
int ALLOCATION[M][N]={{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}};
/*M个进程还需要N类资源的资源量*/
int NEED[M][N]={{7,5,3},{3,2,2},{9,0,2},{2,2,2},{4,3,3}};
//申请资源向量 
int Request[N]={0,0,0};

//显示相关数组的数据情况 
void showdata();
/*系统对进程k请求响应，资源向量改变*/
void changdata(int k);
/*系统拒绝进程k的请求，恢复资源向量*/
void rstordata(int k);
/*安全性检查函数*/
bool chkerr();

int main(void){
	int i = 0,j = 0; 
	bool loop = true;
	char flag = 'y';
	
	//先显示初始数据 
	showdata();
	
	//循环为进程申请资源 
	while(tolower(flag) == 'y'){
		printf("请输入需申请资源的进程号（从0到");
		printf("%d",M-1);
		printf("）:");
		scanf("%d",&i);
		while(i < 0 || i > M-1){
			printf("输入的进程号不存在，重新输入!\n");
			printf("请输入需申请资源的进程号（从0到");
			printf("%d",M-1);
			printf("）:");
			scanf("%d",&i);
		}
	
		printf("请输入进程");
		printf(" %d ",i);
		printf("申请的资源数\n");
		printf("类别:A B C\n");
		printf("");
	 
	 	loop = true;
	 	
		//如果申请的资源数量不规范，要求用户重新输入 
		while(loop){
		
			for(j=0;j<N;j++)
			{	
				scanf("%d",&Request[j]);
			
				if(Request[j]>NEED[i][j])
				{	
					printf(" %d ",i);
					printf("号进程");
					printf("申请的资源数 > 进程");
					printf(" %d ",i);
					printf("还需要");
					printf(" %c ",j + 65);
					printf("类资源的资源量!申请不合理，出错!请重新选择!\n");
				
					printf("请输入进程");
					printf(" %d ",i);
					printf("申请的资源数\n");
					printf("类别:A B C\n");
					printf("");
					
					//清除输入项
					while(getchar() != '\n'){
						continue;
					} 
				
					break;
				}
				else if(Request[j]>AVAILABLE[j])
				{
					printf("进程");
					printf(" %d ",i);
					printf("申请的资源数大于系统可用");
					printf(" %c ",j + 65);
					printf("类资源的资源量!申请不合理，出错!请重新选择!\n");
						
					printf("请输入进程");
					printf(" %d ",i);
					printf("申请的资源数\n");
					printf("类别:A B C\n");
					printf("");
					
					//清除输入项
					while(getchar() != '\n'){
						continue;
					} 
					
					break;
				}else{
					//如果所有的资源数已经读取完毕，则不用再循环了 
					if(j == N - 1){
						loop = false;
					}
				}
			}
		}
		
		changdata(i);
		
		//如果不符合安全状态，则必须恢复已经分配的资源 
		if(chkerr())
		{	
			rstordata(i);
			showdata();
		}
		else{ 
			showdata();
		} 
		printf("\n");
		
		printf("按'y'或'Y'键继续,否则退出\n");
		flag=getch();
	}
	
	return 0;
}

/*显示数组*/
void showdata()
{
	int i,j;
	printf("系统可用资源向量:\n");
	printf("***Available***\n");
	printf("资源类别:A B C\n");
	printf("资源数目:");
	for(j=0;j<N;j++)
	{
		printf("%d ",AVAILABLE[j]);
	}
	printf("\n");
	printf("\n");
	printf("各进程还需要的资源量:\n");
	printf("******Need******\n");
	printf("资源类别:A B C\n");
	for(i=0;i<M;i++)
	{
		printf("");
		printf("%d",i);
		printf("号进程:");
		for(j=0;j<N;j++)
		{
			printf("%d ",NEED[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	printf("各进程已经得到的资源量:\n");
	printf("***Allocation***\n");
	printf("资源类别:A B C\n");
	for(i=0;i<M;i++)
	{
		printf("");
		printf("%d",i);
		printf("号进程:");
		for(j=0;j<N;j++)
		{
			printf("%d ",ALLOCATION[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

/*系统对进程k请求响应，资源向量改变*/
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
/*系统拒绝进程k的请求，恢复资源向量*/
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

/*安全性检查函数*/
//在假定分配资源的情况下检查系统的安全性
//不安全返回true 
bool chkerr()
{
	//WORK 表示系统可提供进程继续运行所需要的各类资源数目
	//FINISH 表示系统是否有足够的资源分配给进程，使之运行完成，开始时先做Finish[i]:=false;当有足够资源分配给进程时，令Finish[i]:=true
	int WORK[N],FINISH[M],temp[M];//temp[]用来记录进程安全执行的顺序
	int i,j,m,k=0,count;
	for(i=0;i<M;i++)
 		FINISH[i]=false;	//所有进程finish初始化为false (当有足够资源分配给进程时，令Finish[i]:=true)
	for(j=0;j<N;j++)
		WORK[j]=AVAILABLE[j];//将work数组初始化为Available 
	for(i=0;i<M;i++)
	{
		count=0;
		for(j=0;j<N;j++){
			if(FINISH[i]==false && NEED[i][j]<=WORK[j]){	
				count++;
			}
		}
		if(count==N)//当进程各类资源都满足NEED<=WORK时
		{
			for(m=0;m<N;m++){ 
				//执行资源回收 
				WORK[m]=WORK[m]+ALLOCATION[i][m];
			} 
			//进程得到足够的资源 
			FINISH[i]=true;
			temp[k]=i;//记录下满足条件的进程
			k++;
			//为什么要使i=-1呢？是因为第一个进程不一定会首先满足。 
			i=-1;
		}
	}
	//只有所有的进程的finish都是true时，则表示系统处于安全状态 
	for(i=0;i<M;i++){ 
		if(FINISH[i]==false)
		{
			printf("系统不安全!!!本次资源申请不成功!!!\n");
			return true;
		}
	} 
	printf("\n");
	printf("经安全性检查，系统安全，本次分配成功。\n");
	printf("\n");
	printf("本次安全序列：");
	for(i=0;i<M;i++)//打印安全系统的进程调用顺序
	{
		printf("进程");
		printf("%d",temp[i]);
		if(i<M-1)
			printf("->");
	}
	printf("\n");
	//系统处于安全状态 
	return false;

}
