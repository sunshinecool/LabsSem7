# LabsSem7

Lab2.1
======
The send and recive buffers of both TCP and UDP sockets can be accessed and modified by *getsockopt* and *setsockopt* respectively.
* **getsockopt**: getsockopt(*socket, SOL_SOCKET, SO_SNDBUF/SO_RCVBUF, (char***)&socksndbuf, sizeof(int)*)
* **setsockopt**: setsockopt(*socket, SOL_SOCKET, SO_SNDBUF/SO_RCVBUF, (char***)&newbuf, sizeof(newbuf)*)

Depending on which buffer ie; send/recieve and which protocol buffers ie; TCP/UDP, we need to change the parameters of the *getsockopt*
and *setsockopt* functions.
* For getting/setting the value of send buffer in TCP, we need to make a TCP socket and use SO_SNDBUF.
* For getting/setting the value of receive buffer in TCP, we need to make a TCP socket and use SO_RCVBUF.
* For getting/setting the value of send buffer in UDP, we need to make a UDP socket and use SO_SNDBUF.
* For getting/setting the value of receive buffer in UDP, we need to make a UDP socket and use SO_RCVBUF.

In the code *only* setting and getting of TCP buffers is done, but it can be done for UDP buffers also by using the rules above.

>Input: option to get/set buffers and value of buffer in case of set.
>Output: The present value of the buffers in case of get and updated value of buffer size in case of set.

Lab2.2a
=======
In this question ***getnameinfo*** funtion is used to do reverse DNS or domain name and service identification from an IP and a port.
Here the service will be identified as one of the common services like *http, https* etc.
The functino getnameinfo takes IP and port as input and identifies the domain name and service that is running on that port.
For example 127.0.0.1:80 would give *localhost* and *http*(provided a http server like apache is running).

```
getnameinfo(&sa, sizeof sa, host, sizeof host, service, sizeof service, 0);
```
The hostname and service are returned by the function in host and service parameter respectively.

> Input: IP and port.
> Output: The hostname and service.

Lab2.2b
=======
Goal is to find out the mac address of an interface. Here we use *struct ifreq ifr;* The ifreq struct is used as parameter to ioctl function as request struct. The structure of ifreq is given below. The ioctl function completes the struct for us when we need the data about an interface.
```
struct ifreq {
               char ifr_name[IFNAMSIZ]; /* Interface name */
               union {
                   struct sockaddr ifr_addr;
                   struct sockaddr ifr_dstaddr;
                   struct sockaddr ifr_broadaddr;
                   struct sockaddr ifr_netmask;
                   struct sockaddr ifr_hwaddr;    /* Hardware address */
                   short           ifr_flags;
                   int             ifr_ifindex;
                   int             ifr_metric;
                   int             ifr_mtu;
                   struct ifmap    ifr_map;
                   char            ifr_slave[IFNAMSIZ];
                   char            ifr_newname[IFNAMSIZ];
                   char           *ifr_data;
               };
           };
``` 
We assign the input interface to the `ifr.ifr_name` using the strncpy function.
```strncpy(ifr.ifr_name , iface , IFNAMSIZ-1);```
We pass this `struct ifr` to ioctl fucntion with the flag **SIOCGIFHWADDR** which completes the struct and which contains the mac address.
```
ioctl(fd, SIOCGIFHWADDR, &ifr);
```
We access the hardware address of the interface using `ifr_hwaddr` member of the `struct ifreq`.
```
mac = (unsigned char *)ifr.ifr_hwaddr.sa_data;
```

>Input: The interface name.
>Output: The mac address.

Lab2.3
======
Here our goal is to find all the interfaces available on a machine. To store this I used `getifaddrs()` function. 
The `getifaddrs()` function creates a linked list of structures describing the network interfaces of the local system, and stores the address of the first item of the list in *ifap.  The list consists of ifaddrs structures, defined as follows:
```
           struct ifaddrs {
               struct ifaddrs  *ifa_next;    /* Next item in list */
               char            *ifa_name;    /* Name of interface */
               unsigned int     ifa_flags;   /* Flags from SIOCGIFFLAGS */
               struct sockaddr *ifa_addr;    /* Address of interface */
               struct sockaddr *ifa_netmask; /* Netmask of interface */
               union {
                   struct sockaddr *ifu_broadaddr;  /* Broadcast address of interface */
                   struct sockaddr *ifu_dstaddr;    /* Point-to-point destination address */
               } ifa_ifu;
```
The `struct ifaddrs  *ifa_next;` stores the address of next struct in the linked list. We need to travel through this linked list and print the names of IPv4 and IPv6 interfaces.
```
for(ifa = ifaddr, n=0; ifa!=NULL; ifa=ifa->ifa_next, n++){
		if(ifa->ifa_addr == NULL) continue;
		family = ifa->ifa_addr->sa_family;
		if(family == AF_INET) 
			printf("AF_INET : %s\n", ifa->ifa_name);
		else if(family == AF_INET6) 
			printf("AF_INET6: %s\n", ifa->ifa_name);
	}
```
This above code checks if the family of the interface is AF_INET or AF_INET6 and prints their names.

Lab2.4a
=======
We read the routing table from the file, `/proc/net/route`. The code is self explanatory.

Lab2.4b
=======
We need to on the IP forwarding of the machine and in make the proxy server as the first hop or gateway in the client systems
that act as clients to the router(our proxy system)
Both the steps are explained here:
```
sudo sysctl net.ipv4.ip_forward=1;
```
This enable IP forwarding of the machine and it will forward all the packet it recieves to the correct machine, in affect 
acting as router.
```
route add -net 10.34.0.0 netmask 255.255.0.0 gw $routerIp
```
This ensures that a gateway is added to client.

Lab2.5
======
**Ping**
This program contains two main functions `ping` and `listener`. These two functions perform the function of pinging the host and listening for the messages respectively.
The `struct packet` is the structure that represents the packet that is to be sent. It contains an ICMP header and data. here we are keeping the data as all zeros. This can be made to present timestamp to calculate the RTT. ie; Round trip time, but that is not done here.
The packet header is filled according to ICMP echo header.
```
pckt.hdr.type = ICMP_ECHO;
pckt.hdr.un.echo.id = pid;
pckt.msg[i] = 0;
pckt.hdr.un.echo.sequence = cnt++;
pckt.hdr.checksum = checksum(&pckt, sizeof(pckt));
```
Here the function `checksum` calculates the checksum of the header and the data that is an array of zero.

The program creates a child that listens for the reply messages while the parent process continously pings the host.
**Listener**
```
void listener(){
	for(;;)
		bytes = recvfrom(sd, buf, sizeof(buf), 0, (struct sockaddr*)&addr, &len);
}
```
**Ping**
```
void ping(){
	for(;;){
		// create header and data
		if ( sendto(sd, &pckt, sizeof(pckt), 0, (struct sockaddr*)addr, sizeof(*addr)) <= 0 )
			perror("sendto");
	}
}
```
