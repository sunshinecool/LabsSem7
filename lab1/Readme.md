Lab1.1
======
For forking 2 childs, a for loop is used and in both the childs another for loop is used to create 2 grandchildren for each child.
```
for(i=0; i<2; i++){
	pid = vfork();
	// If parent continue;
	// If child: Fork twice again
	    for(i=0; i<2; i++){
		    pid = vfork();
		    // If child continue;
		    // If grandchild print and exit.
		  }
}
```
This ensures that each child is forked twice and two grandchildren are created for each child.

Lab1.2
======
In this example 2 threads are created for the sender and reciever respectively. Two function `sender_function` and `receiver_function` are executed on these threads. 

Initially a function `initialize` is called which creates a set of numbers which represent that the packet which has a number in this is treated as lost and will not be received by the receiver.
```
void initialize(){
    for(int i=0;i<PROBABILITY_COUNT;++i)  // Count is a random number.
    {
        probability[i]=rand()%(total_packets_on_receiver_side);
    }	
}	
```

In the `sender_function`  we send the packets if it is not in the lost list.
```
void sender_function(){
	if(!isLost(sender_count)){
		sender_count++;
	}
}
```

Also, in the receiver function, the function waits for a fixed amount of time and then checks if the packet was sent and it will increment the receiver count.
```
void receiver_function(){
	if(sender[recieve_number]==1) 
		receive_packet++;
}
```


Lab1.3
======
The main uses two helper functions `string dectohex(long int decimalNumber)` and `int hextodec(string hexNumber)` which convert decimal to hex and hex to decimal as their name suggest.

If we add all the 2 byte sections of the header, we must get **FFFF** as the sum of all the 2 bytes. But if the sum is not FFFF, the header is not valid.
```
for(int i=0; i<IPHeader.length(); i+=4){
		string temp = IPHeader.substr(i,4);
		sum += hextodec(temp);
	}
```
This caculates the sum of the header in chunks of 2 bytes. 
```
while(sumhex.length()>4){
		string temp = sumhex.substr(sumhex.length()-4, 4);
		string strcarry = sumhex.substr(0, sumhex.length()-4);
		sum = hextodec(strcarry) + hextodec(temp);
		sumhex = dectohex(sum);
	}
```
This part of the code adds the carry till it the sum is of 2 bytes.


Lab1.4
======
Here we need to fragment and reassemble the packets based on the MTU that is given as input.
**Fragmentation module**
The function 
```
string* fragment(string ip,int MTU)
``` 
takes the packet as an input and fragments it into packets of size MTU. This function changes the header of the file and then breaks the data of the complete packet into parts and adds the header and the data to create a new packet. First the header is broken down into parts so as to modify it.
```
string length = ip.substr(4,4);
string restHeader = ip.substr(16,16);
string identification = ip.substr(8,4);
```
We now calculate the number of fragments by dividing the total length of the data with the MTU.
```
noOfFragments = (hextodec(length)-20)/(MTU));
```
Now based on the fragment number, an offset is created and this offset is added in the fragmentaion flag field of the header.

`string frag_flag =  bitset<13>(offset/8).to_string();` 

Finally the data, the fragmentation flag, length and the remaining header are joined to form the final packet.
```
string final_fragment = ip.substr(0,4) + fraglength + identification + final_flag + restHeader;
```
The `fragment` function returns an array of strings representing each of the packet.

**Reassembly**
The function `void reassemble(string s[],int n,int MTU)` reassebles the packets that are passed to it as arguments. First the offset is calculated for each of the incoming packets assuming that they come from the same original packet. Then the packets are sorted based on their offset. Then the data of each segment is added to form the final packet.


Lab1.5
======
Client
------
The client creates a socket using `socket` function and connects to the server using `connect` function. The client then waits for the timestamp and blocks in `recv` function.
Server
------
The server creates a socket using `socket` function and binds to the IP and port using `bind` function. Once the client is connected by the `accept` function, the server creates a timestamp message using `sprintf` and `time_t`.
```
sprintf(tmsg, "%.4i-%.2i-%.2i %.2i:%.2i:%.2i %s\n", 
	      		tm->tm_year + 1900,
	      		tm->tm_mon + 1,
	      		tm->tm_mday,
	     		tm->tm_hour,
	      		tm->tm_min,
	      		tm->tm_sec,
	      		tm->tm_zone);
```
The serer then send this string using `send` function.

>Input: Both server and client take port as the only parameter.

>Output: Client prints the timestamp sent from the server.

Lab1.6
======
Client Chat application
-----------------------
The client creates a socket and connect to the server using the port number of the server. The client is given two options 


..* To create a new chatroom.
..* To join an already created chat room.

If the client chooses to join a chat room the client and server use a protocol to communicate and tell the server what the client wants during the chatroom joining stage.

**Protocol used:**
..* #a - Send the names of the chat rooms!
..* #b - Take chat room as input and send conformation as y/n.
..* #c - Send messages to chat room!
For example, if the client send a message starting with #a, the server parses this message and responds with the list of chat rooms that are available.

Once the client is connected and added to a chat room, it can send and recieve messages.

The backbone of this client and also the server application is the use of select funtion with the FD_SET, and FD_ISSET functions macros for **I/O multiplexing**.
```
FD_ZERO(&clfds);
FD_SET(0, &clfds);  // add stdin to FD_SET
FD_SET(sfd, &clfds);   // add socket to FD_SET
```
In the client side, the stdin and the socket are added to the FD_SET and these two files are multiplexed.
```
int r = select(sfd+1, &clfds, NULL, NULL, NULL);
if(FD_ISSET(0, &clfds)){
  // read input and send msg
}
if(FD_ISSET(sfd, &clfds)){
  // receive msg 
}
```

Server chat application
-----------------------
In server side, the main task is to maintain many connections at the same time, again `select` function is used to multiplex
many sockets. The server maintains an array of descriptors for each chatroom and send the message to all the clients in the 
chatroom when it receives from a client in the chatroom.
The server and client follow the protocol described. ie;
When the server recieves the messages based on the protocol, it performs a particular task.
The function `handleMessage` parses the message. 

Lab1.7
======
The bank RPC uses 2 functions that are used to create and update the bank account.
We have a `bankDetails` struct that contains the account number, name, age, address and phone number.
```
struct bankDetails {
	int account_number;
	char name[20];
	int age;
	char address[40];
	int phone_number;
};
```
The functions that update and open the account details
```
void BANKPROC_ENTRY(bankDetails) = 1;
void BANKPROC_UPDATE(bankDetails) = 2;
```

A account is created using the `bankproc_enty` function and the updated using the `bankproc_update` function.
The account details are stored in a text files. The implementation is straight forward.
