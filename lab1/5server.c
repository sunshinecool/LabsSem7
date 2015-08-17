#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<string.h>
#include<unistd.h>
#include<time.h>
#include<stdlib.h>
#define MLT 200
int main(int argc, char** argv){
	int sfd, cfd;
	time_t t;
	printf("%d\n", atoi(argv[1]));
	int portnumber = atoi(argv[1]);
	struct sockaddr_in serv_addr;
	struct sockaddr_in client_addr;
	struct tm *tm;
	char tmsg[MLT];
	memset(&tmsg, MLT, 0);
	if((sfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		printf("Socket not created\n");
		return 1;
	}

	bzero(&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(portnumber);
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	memset(&(serv_addr.sin_zero), '\0', 8);

	if(bind(sfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
		printf("Bind failed.\n");
		return 1;
	}

	listen(sfd, 4);
	
	while(1){
		int b = sizeof(client_addr);
		if(cfd = accept(sfd, (struct sockaddr *)&client_addr, &b) < 0){
			printf("Error in accept.\n");
		}
		
		printf("%d\n", client_addr.sin_port);
		printf("%d\n", b);
		t = time(NULL);

		tm = localtime(&t);

		sprintf(tmsg, "%.4i-%.2i-%.2i %.2i:%.2i:%.2i %s\n", 
	      		tm->tm_year + 1900,
	      		tm->tm_mon + 1,
	      		tm->tm_mday,
	     		tm->tm_hour,
	      		tm->tm_min,
	      		tm->tm_sec,
	      		tm->tm_zone);

		printf("%s", tmsg);	
		send(cfd, tmsg, strlen(tmsg), 1);

		close(cfd);
	}
	close(sfd);
}
