#include <stdio.h>
#include <io.h>
#include <string.h>
#define COL 32 
#define ROW 32 
#define LENGTH COL*ROW 
#define K 3
#define PATH 50
int main(void)
{
	//�洢ͼ������ 
	int arr[LENGTH]; 
	int content[3][2][LENGTH];
	//�ļ��洢��Ϣ�ṹ�� 
    struct _finddata_t fa;
    //�����ļ���� 
    long fHandle;
    int i = 0;
    int j = 0;
    int ch;	
    int key;	//�����ļ����ĵ�һ���ַ����������� 
    int temp = 0;
    char dir[PATH] = "./test/";
    char path[PATH];
	sprintf(path,"%s*.txt",dir);
    
    FILE * pf;
    
    if( (fHandle=_findfirst(path, &fa))==-1L )
    {
        printf( "��ǰĿ¼��û��txt�ļ�\n");
        return 0;
    }else{
    	do{
        	//printf( "�ҵ��ļ�:%s,�ļ���С��%d\n", fa.name,fa.size);
        	key = (int)((fa.name)[0] - '0'); 
        	if(key == temp + 1){
	        	i = 0;
	        } 
        	sprintf(path,"%s%s",dir,fa.name);
        	if((pf=fopen(path,"r")) == NULL){
	        	fprintf(stderr,"%s\n","fail to open file!");
	        }
	        j = 0;
	        while((ch = getc(pf)) != EOF){
	        	if(ch == '\n'){
	        		continue;
	        	}
        		content[key][i][j++] = (int)(ch - '0');
        	}
        	
        	i ++;
        	temp = key;
        	fclose(pf);
        	
    	}while( _findnext(fHandle,&fa)==0);
    }
    //�ر��ļ� 
    _findclose( fHandle );
    
    int m,n,p;
    for(m = 0;m < 3;m ++){
    	printf("%d=>\n",m);
    	for(n = 0;n < 2;n ++){
    		printf("    %d=>",n);
	    	for(p = 0;p < LENGTH;p ++){
	    		printf("%d ",content[m][n][p]);
	    	}
	    	printf("\n");
	    }
	    printf("\n");
    } 
    system("pause");
    return 0;
}