#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<string.h>
#include<unistd.h>

#define MAXDATA 255
int main(int argc, char** argv){
	int sfd,n;
	char buf[MAXDATA];
	struct sockaddr_in serv_addr;
	int portnumber = atoi(argv[1]);

	if((sfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		printf("Error in socket creating\n");
	}

	bzero(&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(portnumber);
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	if(connect(sfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
		printf("Error in connecting to server.\n");
	}

	while((n = recv(sfd, buf, MAXDATA-1,0)) > 0){
		buf[n] = '\0';
		printf("%s",buf); 
		memset(&buf, sizeof(buf), 0);
	}
	close(sfd);
}
