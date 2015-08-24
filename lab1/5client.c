#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#define MAXDATA 1025
int main(int argc, char** argv){
	int sfd,n;
	char bufr[MAXDATA];
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
	else printf("connected\n");

	fd_set clfds;
	FD_ZERO(&clfds);
	FD_SET(sfd, &clfds);
	FD_SET(0, &clfds);
	char buf[MAXDATA];
	while(1){
		FD_ZERO(&clfds);
		FD_SET(0, &clfds);
		FD_SET(sfd, &clfds);
		int r = select(sfd+1, &clfds, NULL, NULL, NULL);
		if(r>0){
			if(FD_ISSET(0, &clfds)){
				printf("me: ");
				if (fgets(buf,MAXDATA-1, stdin)){
					if((n=send(sfd, buf,MAXDATA-10 , 0)) < 0) printf("Error in sending message\n");	
					//printf("%d bytes sent.\n", n);
            				if (strncmp(buf, "exit", 4) == 0)
                  				exit(0);
           			}
				memset(&buf, sizeof(buf), 0);
           			//printf("Me: ");		
			}
			if(FD_ISSET(sfd, &clfds)){
				//printf("Recieving mode\n");
				n = recv(sfd, bufr, MAXDATA-1,0);
				//printf("%d bytes recieved. \n", n);
				if(n<0) printf("Error in recv\n");
				if(n>0){
					bufr[n] = '\0';
					printf("in: %s",bufr); 
					memset(&bufr, sizeof(bufr), 0);
				}
			}
		}
		else if(r==-1) printf("Error in select!\n");
	}
	close(sfd);
}
