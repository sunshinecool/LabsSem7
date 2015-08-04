#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
int glob = 6;
int main(){
	int var = 100;
	pid_t pid = fork();
	if(pid == 0){
		printf("Child\n");
		glob++;
		var++;
		//_exit(1);
	}
	if(pid>0){
		printf("Parent\n");
		sleep(2);
	}
	printf("pid = %d, glob = %d, var = %d\n", getpid(), glob, var);
	_exit(1);
}
