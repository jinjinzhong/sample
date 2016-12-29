#include <stdio.h>
unsigned int DJBHash(char * str);
int main(void){
	char str[10] = "zhongjin";
	unsigned int a = DJBHash(str);
	printf("%d\n",a);
	return 0;
} 
unsigned int DJBHash(char * str){
	unsigned int hash = 5381;
	while(*str){
		hash += (hash << 5)+(*(str ++));
	}
	return (hash & 0x7FFFFFFF);
}
