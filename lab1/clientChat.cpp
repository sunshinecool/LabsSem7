#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <iostream>
#define MAXDATA 1024
using namespace std;

string rooms[1];
string alias;
void sendMessage(int sfd, string msg){
	if((send(sfd, msg.c_str() ,MAXDATA-10 , 0)) < 0){ 
		printf("Error in sending message\n");
	}
}
void parseChatRoomNames(string chat_names){
	rooms[0] = chat_names;
}
void RecieveChatMessages(int sfd){
	cout<<"Start chatting!"<<endl;
	cout<<"==================================="<<endl;
	int n;
	fd_set clfds;
	FD_ZERO(&clfds);
	FD_SET(sfd, &clfds);
	FD_SET(0, &clfds);
	char buf[MAXDATA];
	char bufr[MAXDATA];
	while(1){
		FD_ZERO(&clfds);
		FD_SET(0, &clfds);
		FD_SET(sfd, &clfds);
		int r = select(sfd+1, &clfds, NULL, NULL, NULL);
		if(r>0){
			if(FD_ISSET(0, &clfds)){
				//printf("me: ");
				int len;
				fflush(stdin);
				if (fgets(buf,MAXDATA-1, stdin)){
					fflush(stdin);
					string msg_to_send = buf;
					int k;
					msg_to_send = "c#" + alias + ": " + msg_to_send;
					sendMessage(sfd, msg_to_send);
					//printf("%d bytes sent.\n", k);
            				if(strncmp(buf, "exit", 4) == 0)
                  				exit(0);
           			}
				memset(&buf, sizeof(buf), 0);
           			//printf("Me: ");		
			}
			if(FD_ISSET(sfd, &clfds)){
				//printf("Recieving mode\n");
				n = recv(sfd, bufr, MAXDATA-1,0);
			//	printf("%d bytes recieved. \n", n);
				if(n<0) printf("Error in recv\n");
				if(n>0){
					bufr[n] = '\0';
					printf("%s",bufr); 
					memset(&bufr, sizeof(bufr), 0);
				}
			}
		}
		else if(r==-1) printf("Error in select!\n");
	}
}

string recieveMessage(int sfd){
	char buf[MAXDATA];
	if((recv(sfd, buf, MAXDATA-1, 0)) < 0) {
		cout<<"Error in recv!"<<endl;
	}
	return buf;

}
int main(int argc, char** argv){
	if(argc!=2){
		cout<<"Enter IP and port seperately!"<<endl;
		return 0;
	}

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

	cout<<recieveMessage(sfd)<<endl;;
	cout<<"Enter your alias: ";	
	cin>>alias;
	cout<<"==================================="<<endl;
	int choice;
	cout<<"1. Join a chat room"<<endl;
	cout<<"2. Create a new chat room"<<endl;
	cout<<"Select either of the options: ";
	cin>>choice;
	cout<<"==================================="<<endl;
	char buf[MAXDATA];
	switch(choice){
		case 1:
			sendMessage(sfd, "a#");
			string chat_room_names = recieveMessage(sfd);
			parseChatRoomNames(chat_room_names);
			//cout<<chat_room_names<<" "<<rooms[0]<<endl;
			cout<<"Rooms available!"<<endl;
			for(int i=0; i< 1; i++){
				cout<<i<<". "<<rooms[i]<<endl;
			}
			cout<<"Select one of the room: ";
			char room_to_enter;
			cin>>room_to_enter;
			string tmp_msg = "b#";
			tmp_msg+=room_to_enter;
			sendMessage(sfd, tmp_msg);
			string conformation = recieveMessage(sfd);
			if(conformation == "y") {
				cout<<"==================================="<<endl;
				cout<<"Welcome to the chat room!"<<endl;
				RecieveChatMessages(sfd);
			}
	}	
}
