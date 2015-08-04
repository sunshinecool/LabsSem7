#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
int main(){
	pid_t pid = fork();
	if(pid == 0){
		printf("Child\n");
		exit(1);
	}
	if(pid>0){
		printf("Parent\n");
		exit(1);
	}
}
