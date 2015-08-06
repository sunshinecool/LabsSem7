#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <iostream>

using namespace std;

void connectToServer(int sfd,const struct sockaddr_in &serv_addr, int addr_size){
	if(connect(sfd, (struct sockaddr *)&serv_addr, addr_size) < 0){
		printf("Error in connecting to server.\n");
		return -1;
	}
}
int main(int argc, char** argv[]){
	if(argc!=3){
		cout<<"Enter IP and port seperately!"<<endl;
		return 0;
	}
	string ip_addr = argv[1];
	int serv_port = atoi(argv[2]);

	int sfd;
	struct sockaddr_in serv_addr;
	int addr_size = sizeof(serv_addr);
	/* Needs to be done for external IP*/
	bzero(&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(portnumber);
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	if((sfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		printf("Error in socket creating\n");
		return 1;
	}
	string alias;
	cout<<"Enter your alias: "<<endl;	
	cin>>alias;

	int choice;
	cout<<"Select either of the options:"<<endl;
	cout<<"1. Join a chat room"<<endl;
	cout<<"2. Create a new chat room"<<endl;
	cin>>choice;
	
	switch(choice){
		case 1:
			string room_name;
			cout<<"Enter the exact name of the chat room: ";
			cin>>room_name;
			if(connetToServer(sfd, serv_addr, addr_size) < 0)
				return 1;
			sendMessage(sfd, "			

	}

}
