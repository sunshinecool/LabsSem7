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
	int sockbufsize = 0; int size = sizeof(int); 
	int err = getsockopt(skt, SOL_SOCKET, SO_RCVBUF, (char *)&sockbufsize, &size);
	printf("%d\n", sockbufsize);
	int sndsize = 100000;
	err = setsockopt(skt, SOL_SOCKET, SO_RCVBUF, (char *)&sndsize, (int)sizeof(sndsize));
	err = getsockopt(skt, SOL_SOCKET, SO_RCVBUF, (char *)&sockbufsize, &size);
	printf("%d\n", sockbufsize);
}
