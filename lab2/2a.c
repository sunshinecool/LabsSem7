#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h> /* memset */
#include <unistd.h>
int main()
{
	struct sockaddr_in sa; // could be IPv4 if you want
	char host[1024];
	char service[20];

	// pretend sa is full of good information about the host and port...
	memset(&sa, 0, sizeof(sa));                /* zero the struct */
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = inet_addr("127.0.0.1"); 
	sa.sin_port = htons(10000);

	getnameinfo(&sa, sizeof sa, host, sizeof host, service, sizeof service, 0);

	printf("   host: %s\n", host);    // e.g. "www.example.com"
	printf("service: %s\n", service);	
}
