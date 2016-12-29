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
	//存储图像向量 
	int arr[LENGTH]; 
	int content[3][2][LENGTH];
	//文件存储信息结构体 
    struct _finddata_t fa;
    //保存文件句柄 
    long fHandle;
    int i = 0;
    int j = 0;
    int ch;	
    int key;	//保存文件名的第一个字符，代表数字 
    int temp = 0;
    char dir[PATH] = "./test/";
    char path[PATH];
	sprintf(path,"%s*.txt",dir);
    
    FILE * pf;
    
    if( (fHandle=_findfirst(path, &fa))==-1L )
    {
        printf( "当前目录下没有txt文件\n");
        return 0;
    }else{
    	do{
        	//printf( "找到文件:%s,文件大小：%d\n", fa.name,fa.size);
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
    //关闭文件 
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