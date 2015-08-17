#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <vector>
#define MAXDATA 1024
using namespace std;
/*

#a - Send the names of the chat rooms!
#b - Take chat room as input and send conformation as y/n.
#c - Send messages to chat room!

*/

vector<int> chat_rooms[10];
map<int, int> present_in;
map<int, string> cr_names;
string cr_names_string;
int number_of_rooms = 0;

void test_initialize(){
	number_of_rooms = 1;
	cr_names_string = "test_room";	
}

void sendMessage(int cfd, string msg){
	if((send(cfd, msg.c_str(), 21, 0))<0) {
		cout<<"Error in send!"<<endl;
	}
}

void handleMessages(string buf, int cfd ){
	int chat_room_number = (int)buf[2];
	int room_present_in = present_in[cfd];
	cout<<"Message recieved at server: "<<buf<<endl;
	switch(buf[0]){
		case 'a': 
			sendMessage(cfd, cr_names_string);
			break;
		case 'b':
			present_in[cfd] = chat_room_number;
			chat_rooms[chat_room_number].push_back(cfd);
			sendMessage(cfd, "y");
			break;
		case 'c':
			for(int j=0; j<chat_rooms[room_present_in].size(); j++){
				if(chat_rooms[room_present_in][j]!=cfd){
					string chat_msg = buf.substr(2, buf.length()-2);
					cout<<chat_msg<<" Message sent to "<<chat_rooms[room_present_in][j]<<endl;
					//int k;
					sendMessage(chat_rooms[room_present_in][j], chat_msg);
					//cout<<k<<endl;
				}
			}
			break;
	}	
}

int main(int argc, char** argv){
	if(argc!=2){
		cout<<"Enter IP and port seperately!"<<endl;
		return 0;
	}
	test_initialize();
	int serv_port = atoi(argv[1]);
	cout<<serv_port<<endl;
	int sfd,cfd;
	struct sockaddr_in serv_addr;
	struct sockaddr_in client_addr;
	int addr_size = sizeof(serv_addr);
	socklen_t sin_size= sizeof(serv_addr);
	bzero(&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(serv_port);
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	memset(&(serv_addr.sin_zero), '\0', 8);

	int b = sizeof(client_addr);
	if((sfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		printf("Error in socket creating\n");
		return 1;
	}
	int opt = 1;
	if( setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0){
        	perror("setsockopt");
        	exit(EXIT_FAILURE);
    	}
	cout<<sfd<<" SFD"<<endl;
	if(bind(sfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
		printf("Bind failed.\n");
		return 1;
	}

	listen(sfd, 10);
	
	fd_set readfds, tempfds;
	FD_ZERO(&readfds);
	FD_SET(sfd, &readfds);
	int n_select = sfd + 1;
	int n;
	int j=0, k=0;
	vector<int> clientfd;
	int rv;
	char buf[1024];

	struct timeval timeout;
	timeout.tv_sec = 2;
	timeout.tv_usec = 0;
	while(1){
		tempfds = readfds;
		rv = select(n_select, &tempfds, NULL, NULL,NULL);
		if(rv == -1){
			printf("Error in select!\n");
			return 1;
		}
		else if(rv == 0){
			fflush(stdout);
		}
		else{
			if(FD_ISSET(sfd, &tempfds)){
				cout<<"New client connected"<<endl;
				if((cfd = accept(sfd, (struct sockaddr *)&client_addr,&sin_size )) < 0){
					printf("Error in accept.\n");
				}
				FD_SET(cfd, &readfds);
				clientfd.push_back(cfd);
				string welcm_msg = "Welcome to the chat!\n";
				int r;
				if((r=send(cfd, welcm_msg.c_str(), 21, 0))<0) cout<<"Error in send!"<<endl;
				if(cfd >= n_select) n_select = cfd+1;	
			}
			else{
				for(int i=0; i<clientfd.size(); i++){
					if(FD_ISSET(clientfd[i], &tempfds)){
						n=recv(clientfd[i], buf, sizeof(buf), 0);
						if(n==0){
							cout<<"Client disconnected"<<endl;
							if(clientfd[i]+1 == n_select) n_select--;
							FD_CLR(clientfd[i], &readfds);
							clientfd.erase(clientfd.begin()+i);
							close(clientfd[i]);
						}
						else if(n>0){
							handleMessages(buf, clientfd[i]);
						}
						else{
							cout<<"Error in recv."<<endl;
						}
					}		
				}
			}
		}
	}
}
