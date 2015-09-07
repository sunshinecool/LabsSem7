#define _GNU_SOURCE     /* To get defns of NI_MAXSERV and NI_MAXHOST */
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <ifaddrs.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/if_link.h>

int main(int argc, char* argv[]){
	struct ifaddrs *ifaddr, *ifa;
	int n, family;
	if(getifaddrs(&ifaddr) == -1){
		perror("getifaddrs");
	}

	for(ifa = ifaddr, n=0; ifa!=NULL; ifa=ifa->ifa_next, n++){
		if(ifa->ifa_addr == NULL) continue;
		
		family = ifa->ifa_addr->sa_family;

		if(family == AF_INET) 
			printf("AF_INET : %s\n", ifa->ifa_name);
		else if(family == AF_INET6) 
			printf("AF_INET6: %s\n", ifa->ifa_name);
	}
	
	freeifaddrs(ifaddr);
}
