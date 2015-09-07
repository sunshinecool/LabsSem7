#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h> /* memset */
#include <unistd.h>
int main(int argc, char* argv[])
{
	struct sockaddr_in sa; // could be IPv4 if you want
	char host[1024];
	char service[20];

	if(argc < 3){
		printf("Enter Ip and port seperately!");
		return 0;
	}
	int portnumber = atoi(argv[2]);
	memset(&sa, 0, sizeof(sa));                /* zero the struct */
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = inet_addr(argv[1]); 
	sa.sin_port = htons(portnumber);

	getnameinfo(&sa, sizeof sa, host, sizeof host, service, sizeof service, 0);

	printf("   host: %s\n", host);    // e.g. "www.example.com"
	printf("service: %s\n", service);	
}
