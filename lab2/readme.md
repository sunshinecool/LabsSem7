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

> In the code *only* setting and getting of TCP buffers is done, but it can be done for UDP buffers also by using the rules above.


Lab2.2a
======
In this question ***getnameinfo*** funtion is used to do reverse DNS or domain name and service identification from an IP and a port.
Here the service will be identified as one of the common services like *http, https* etc.
The functino getnameinfo takes IP and port as input and identifies the domain name and service that is running on that port.
For example 127.0.0.1:80 would give *localhost* and *http*(provided a http server like apache is running).

> In the code, IP and port are taken as inputs.

Lab2.2b
=======
Goal is to find out the mac address of an interface. 
