#include<stdio.h>
#include<unistd.h>
int main(){
	printf("Infinite loop starts");
	while(1){
		sleep(1);
	}
	return 0;
}
