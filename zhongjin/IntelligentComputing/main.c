#include <stdio.h>
#include <io.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "list.h"
#include "list.c"
#define COL 32 
#define ROW 32 
#define LENGTH COL*ROW 
#define K 20

//KNN�㷨��������жϵ��������飬������������
int KNN(int arr[LENGTH]); 
//���������֮��ľ��� 
double getDistance(int arr1[],int arr2[]); 
//����
double Test();

int main(void){
	time_t begin_time;
	time_t end_time;
	
	begin_time = time(0);
	
	
	/*
int arr[LENGTH];
	char * file = "./testDigits/1_84.txt";
	FILE * pf;
	int j = 0;
	int tag;
	char ch;
	
	if((pf = fopen(file,"r")) == NULL){
		fprintf(stderr,"Fail to open  %s\n",file);
	}
	while((ch = getc(pf)) != EOF){
		//�������� 
 		if(ch == '\n'){
  			continue;
	   	}
   		arr[j++] = (int)(ch - '0');
	}
        	
	fclose(pf);
	tag = KNN(arr);
	printf("��ǩΪ��%d\n",tag);*/
	
	
	double percent = 0.0;
	percent = Test();
	
	end_time = time(0); 
	
	printf("��ȷ�ʣ�%f,����ʱ�䣺%d",percent,end_time - begin_time); 
	
	return 0;
} 
int KNN(int arr[LENGTH]){
	//�ļ���� 
	FILE * pf;
	//�ļ��洢��Ϣ�ṹ�� 
    struct _finddata_t fa;
    //�����ļ���� 
    long fHandle;
    //ѵ����Ŀ¼ 
    char dir[] = "./trainingDigits";
	char path[] = "./trainingDigits/*.txt"; 
	char temp_path[strlen(dir) + 10];
	//�����ʱͼ������ 
	int temp_arr[LENGTH];
	//��ž���
	double distance; 
	//��������
	List num_list; 
	Item item;
	//��ű�ǩ����
	int tag_arr[10] = {0,0,0,0,0,0,0,0,0,0};
	//��ʱ��ǩ 
	int key;
	char ch; 
	
	InitializeList(&num_list);
    
	if( (fHandle=_findfirst(path, &fa))==-1L )
    {
        printf( "ѵ����Ŀ¼��û��txt�ļ�\n");
        return -1;
    }else{
    	do{
    		//��ȡ������������֣� 
        	key = (int)((fa.name)[0] - '0'); 
        	int j = 0;
        	 
        	sprintf(temp_path,"%s/%s",dir,fa.name);
        	if((pf=fopen(temp_path,"r")) == NULL){
	        	fprintf(stderr,"%s\n","fail to open file!");
	        }
	        while((ch = getc(pf)) != EOF){
	        	//�������� 
	        	if(ch == '\n'){
	        		continue;
	        	}
        		temp_arr[j++] = (int)(ch - '0');
        	}
        	
        	fclose(pf);
        	
        	distance = getDistance(arr,temp_arr);
        	item.key = key;
        	item.distance = distance;
        	AddItem(item,&num_list);

    	}while( _findnext(fHandle,&fa)==0);
    }
    //�ر��ļ� 
    _findclose( fHandle );
    
    int loop = 0;
    Node * current = num_list;
    while(loop < K && current != NULL){
    	key = (current->item).key;
    	tag_arr[key] ++;
    	current = current->next;
    	loop ++;
    }
    
    EmptyTheList(&num_list);
    
    int m;
    int max_key = 0;
	int max = 0; 
    for(m = 0;m < 10;m ++){
    	if(max < tag_arr[m]){
	    	max_key = m;
	    }
    }
    return max_key;
}
double getDistance(int arr1[],int arr2[]){
	double distance = 0.0;
	int sum = 0;
	int i;
	for(i = 0;i < LENGTH;i ++){
		sum += pow(arr1[i] - arr2[i],2);
	} 
	distance = sqrt(sum);
	return distance;
} 
double Test(){
	//�ļ���� 
	FILE * pf;
	//�ļ��洢��Ϣ�ṹ�� 
    struct _finddata_t fa;
    //�����ļ���� 
    long fHandle;
    //ѵ����Ŀ¼ 
    char dir[] = "./testDigits";
	char path[] = "./testDigits/*.txt"; 
	char temp_path[strlen(dir) + 10];
	//�����ʱͼ������ 
	int temp_arr[LENGTH];
	
	char ch; 
	int knn_key;
	int key;
	int total = 0;
	int right = 0;
	
	if((fHandle=_findfirst(path, &fa))==-1L )
    {
        printf( "���Լ�Ŀ¼��û��txt�ļ�\n");
        return -1;
    }else{
    	do{
    		total ++;
    		//��ȡ������������֣�
        	key = (int)((fa.name)[0] - '0'); 
        	printf("key : %d ",key);
        	int j = 0;
        	sprintf(temp_path,"%s/%s",dir,fa.name);
        	if((pf=fopen(temp_path,"r")) == NULL){
	        	fprintf(stderr,"%s\n","fail to open file11!");
	        }
	        while((ch = getc(pf)) != EOF){
	        	//�������� 
	        	if(ch == '\n'){
	        		continue;
	        	}
        		temp_arr[j++] = (int)(ch - '0');
        	}
        	
        	fclose(pf);
        	
        	knn_key = KNN(temp_arr);
        	printf("knn_key : %d ",knn_key);
        	if(knn_key	== key){
	        	right ++;
	        }
        	
    	}while( _findnext(fHandle,&fa)==0);
    }
    //�ر��ļ� 
    _findclose( fHandle );
    return ((double)right)/total;
}
