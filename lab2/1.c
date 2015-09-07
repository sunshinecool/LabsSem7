#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<string.h>
#include<unistd.h>
#include<time.h>
#include<stdlib.h>
int main(){
	int skt = socket(AF_INET, SOCK_STREAM, 0);
	int sockrcvsize = 0; int size = sizeof(int); 
	int socksndsize = 0;
	int newsize, err;
	while(1){
		int t;
		printf("1. Set \n2. Get\nSelect one option: ");
		scanf("%d", &t);
		switch(t){
			case 1: 
				err = getsockopt(skt, SOL_SOCKET, SO_SNDBUF, (char *)&socksndsize, &size);
				err = getsockopt(skt, SOL_SOCKET, SO_RCVBUF, (char *)&sockrcvsize, &size);
				printf("Present size \nsend: %d\nrecv: %d\n", socksndsize, sockrcvsize);
				printf("Enter the new size in bits: ");
				scanf("%d", &newsize);
				err = setsockopt(skt, SOL_SOCKET, SO_RCVBUF, (char *)&newsize, (int)sizeof(newsize));
				err = setsockopt(skt, SOL_SOCKET, SO_SNDBUF, (char *)&newsize, (int)sizeof(newsize));
				err = getsockopt(skt, SOL_SOCKET, SO_SNDBUF, (char *)&socksndsize, &size);
				err = getsockopt(skt, SOL_SOCKET, SO_RCVBUF, (char *)&sockrcvsize, &size);
				printf("Updated size \nsend: %d\nrecv: %d\n", socksndsize, sockrcvsize);
				break;
		
			case 2:
				err = getsockopt(skt, SOL_SOCKET, SO_SNDBUF, (char *)&socksndsize, &size);
				err = getsockopt(skt, SOL_SOCKET, SO_RCVBUF, (char *)&sockrcvsize, &size);
				printf("Present size \nsend: %d\nrecv: %d\n", socksndsize, sockrcvsize);
				break;
				
		}
	}
}
