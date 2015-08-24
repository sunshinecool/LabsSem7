#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
int main(){
	int i,pidp;
	pidp = getpid();
	printf("Parent process: %d\n", pidp);
	for(i=0; i<2; i++){
		int pid;
		//printf("%d\n",i);
		pid = vfork();
		if(pid){
			//printf("%d\n", pid);
			continue;
		}
		else if(pid == 0){
			int j;
			printf("Child %d pid: %d\n", i, getpid());
			for(j=0; j<2; j++){
				int pidc;
				pidc = vfork();
				if(pidc){
					//sleep(2);
					continue;
				}
				else if(pidc==0){
					printf("Grandchild %d of child %d pid: %d\n", j,i, getpid());	
					_exit(1);
				}
			}
			_exit(2);
		}
		else{
			printf("error in fork");	
		}
	}
}
