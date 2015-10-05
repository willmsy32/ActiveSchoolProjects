//Andrew Willms
//9-22-2015
//CSE 489 Project 1
/*
Project Guidelines:

Your process (your program when it is running in memory) will take 2 command line parameters. The
first parameter indicates whether your program instance should run as a server or a client. The second
parameter corresponds to the port on which your process will listen for incoming connections (e.g., if
your program is called prog1, then you can run it like this: ./prog1 s 4322, where the “s” indicates that
it is the server and 4322 is the port. Suppose you want to run it as a client then you should run it
as ./prog1 c 4322 where the “c” parameter indicates that the process is a client and 4322 is the listening
port).

NOTE: Server should always be run on timberlake and no other host involved in file transfer should be
run on timberlake. Use other CSE student servers to run hosts involved in file transfer.

NOTE: Use TCP Sockets only for your implementation. You should use only the select() API for
handling multiple socket connections. Please don’t use multi-threading or fork-exec.

Servers to be used:
Timberlake ( only to run server. Don't do any file exchange on timberlake).
Following servers can be used for file-exchange:
Euston (euston.cse.buffalo.edu)
Embankment(embankment.cse.buffalo.edu)
Underground (underground.cse.buffalo.edu)
Highgate (highgate.cse.buffalo.edu)

NOTE: You should use only the servers listed above. Don’t use any other department servers. Also,
create your own directory in /local/Fall_2015/ on all the hosts except Timberlake where you can use
your home directory. Use only this directory to store/run your programs. Also, make sure you have set
appropriate permissions to your folder so that it cannot be accessed by any other students.

NOTE: Please don't use any other directory/CSE servers to run your code.
*/


#define _GNU_SOURCE     // To get defnitions of NI_MAXSERV and NI_MAXHOST
#include <arpa/inet.h>
#include <linux/if_link.h>
#include <ifaddrs.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

void initializeProcess(int argc, char *argv[]);
char *substringOf(int i,int j,char *ch);
void *get_in_addr(struct sockaddr *sa);
char *localIP();
void handleDisplayRequest();


/* DEFINITIONS AND GLOBALS ========================================================================


*/
//Define the boolean data type
typedef int bool;
#define true 1
#define false 0

//Define the standard input file descriptor number
#define std_in 0 

//Define the port for the process to listen on
int listenPort = -1;

//Define whether the process will act as a server or as a client
bool isServer = false;

//Used to check the return values for functions and return their error messages
int returnValue = 0;




/* PRIMARY FUNCTIONS ==============================================================================

*/
int main(int argc, char *argv[]){
	initializeProcess(argc,argv);
	handleDisplayRequest();
	
    return 0;
}

/*Initializes the process
- Sets the process as either a server or client
- Sets the process' listening port

*/
void initializeProcess(int argc, char *argv[]){
	if( argc != 3){
		printf("This program requires two command line arguments to initialize!\n");
		printf("You must specify whether the process is a server or a client using 'c' and 's' as your first parameter\n");
		printf("You must specify what port the process should listen on as you second parameter\n");
	}
	else{
		//If this client has been designated as a server
		if(strcmp(argv[1],"s")==0){
			printf("This process has been designated as a server\n");
			isServer = true;
		//If this client has been designated as a client
		}else if (strcmp(argv[1],"c")==0){
			printf("This process has been designated as a client\n");
			isServer = false;
		//If it cannot be determined if the process is a client or a server
		}else{
			printf("Invalid designation of process role- Please specify if process is a server or client with first parameter\n");
			exit(-1);
		}
		
		//Grab the second parameter as a integer
		listenPort = atoi(argv[2]);
		if(listenPort==-1){
			printf("Invalid designation of process port- Please specify a port for the process to listen on\n");
			exit(-1);
		}
		printf("Process will listen in on port %d\n",listenPort);
	}
}

/* HELP
1. HELP: Display information about the available user command options.
*/
void handleHelpRequest(){
	printf("Function unimplemented!\n");
}

/* DISPLAY
2. DISPLAY: Display your (the students) full name, your UBIT name and UB email address, the IP
address of this process, and the port on which this process is listening for incoming connections.
NOTE: The IP should not be your “Lo” address (127.0.0.1). It should be the actual IP of the host.
*/
void handleDisplayRequest(){
	printf("Andrew S. Willms (aswillms)\naswillms@buffalo.edu\nLocal Process IP:   <%s>\nLocal Process Port: %d\n",localIP(),listenPort);
}

/* REGISTER
4. REGISTER <server IP> <port no>: This command is used by the client to register itself with the
server and to get the IP and listening port numbers of all other peers currently registered with the
server. The first task of every host is to register itself with the server by sending the server a TCP
message containing its listening port number. The server should maintain a list of the IP address and
the listening ports of all the registered clients. Let’s call this list as “Server-IP-List”. Whenever a
new host registers or a registered host exits, the server should update its Server-IP-List appropriately
and then send this updated list to all the registered clients. Hosts should always listen to such updates
from the server and update their own local copy of the available peers. Any such update which is
received by the host should be displayed by the client. The REGISTER command takes 2 arguments.
The first argument is the IP address of the server and the second argument is the listening port of the
server. If the host closes the TCP connection with the server for any reason then that host should be
removed from the “Server-IP-List” and the server should promptly inform all the remaining hosts.

NOTE: The REGISTER command works only on the client and not on the server. Registered clients
should always maintain a live TCP connection with the server.
*/
void handleRegisterRequest(){
	printf("Function unimplemented!\n");
}

/* CONNECT
4. CONNECT <destination> <port no>: This command is used to establish a connection between two
registered clients. The command establishes a new TCP connection to the specified <destination> at
the specified <port no>. The <destination> can either be an IP address or a hostname. (e.g., CONNECT
timberlake.cse.buffalo.edu 3456 or CONNECT 192.168.45.55 3456). The specified IP address should
be a valid IP address and listed in the Server-IP-List sent to the host by the server. Any attempt to
connect to an invalid IP or an IP address not listed by the server in its Server-IP- List should be rejected
and suitable error message displayed. Success or failure in connections between two peers should be
indicated by both the peers using suitable messages. Self-connections and duplicate connections should
be flagged with suitable error messages. Every client can maintain up-to 3 connections with its peers.
Any request for more than 3 connections should be rejected.
*/
void handleConnectRequest(){
	printf("Function unimplemented!\n");
}

/* LIST
5. LIST: Display a numbered list of all the connections this process is part of. This numbered list
will include connections initiated by this process and connections initiated by other processes. The
output should display the hostname, IP address and the listening port of all the peers the process is
connected to. Also, this should include the server details.
id: Hostname IP address Port No.

1: timberlake.cse.buffalo.edu 192.168.21.20 4545
2: highgate.cse.buffalo.edu 192.168.21.21 5454
3: underground.cse.buffalo.edu 192.168.21.22 5000
4: embankment.cse.buffalo.edu 192.168.21.22 5005
5: euston.cse.buffalo.edu 192.168.21.22 5125

NOTE: The connection id 1 should always be your server running on timberlake.cse.buffalo.edu.
The remaining connections should be the peers whom you have connected to.
*/
void handleListRequest(){
	printf("Function unimplemented!\n");
}

/* TERMINATE
6. TERMINATE <connection id> This command will terminate the connection listed under the
specified number when LIST is used to display all connections. E.g., TERMINATE 2. In this
example, the connection with highgate should end. An error message is displayed if a valid
connection does not exist as number 2. If a remote machine terminates one of your connections,
you should also display a message.
*/
void handleTerminateRequest(){
	printf("Function unimplemented!\n");
}

/* QUIT
7. QUIT Close all connections and terminate this process. When a host exits, the server unregisters the
host and sends the updated “Server-IP-List” to all the clients. Other hosts on receiving the updated list
from the server should display the updated list
*/
void handleQuitRequest(){
	printf("Function unimplemented!\n");
}

/* SEND
8. SEND <connection id. > <message>: (Eg., send 3 Oh! This project is a piece of cake). This will
send the message to the host on the connection that is designated by the number 3 when LIST
command is used. The message to be sent can be up-to 100 characters long, including blank spaces.
On successfully executing the command, the sender should display “Message sent to <connection
id>” on the screen. On receiving any message from the peer, the receiver should display the received
message along with the sender information.

E.g., if a process running on embankment.cse.buffalo.edu sends a message to a process running on
euston.cse.buffalo.edu then the output on euston on receiving a message should display as shown:

Message received from embankment.cse.buffalo.edu
Sender’s IP: < IP of the sender>
Sender’s Port: <The port no. of the sender>
Message “<received message>”

NOTE: SEND command on a server should display an error message. Any attempt to send the
server any messages should be flagged as an erroneous input and suitable error message should be
displayed.
*/
void handleSendRequest(){
	printf("Function unimplemented!\n");
}



/* SECONDARY FUNCTIONS ============================================================================

*/
// Determines the local IP address of the current process
char *localIP(){
	struct ifaddrs *ifaddr, *ifa;
	int family, s, n;
	char host[NI_MAXHOST];
	char *myIP = malloc (sizeof(char)*NI_MAXHOST);

	if (getifaddrs(&ifaddr) == -1) {
		perror("getifaddrs");
		exit(EXIT_FAILURE);
	}
	
	/* Walk through linked list, maintaining head pointer so we can free list later */
	for (ifa = ifaddr, n = 0; ifa != NULL; ifa = ifa->ifa_next, n++) {
		if (ifa->ifa_addr == NULL){
			continue;
		}

		family = ifa->ifa_addr->sa_family;
		
		if (family == AF_INET) {
			s = getnameinfo(ifa->ifa_addr,(family == AF_INET) ? sizeof(struct sockaddr_in) :sizeof(struct sockaddr_in6),host, NI_MAXHOST,NULL, 0, NI_NUMERICHOST);
			if (s != 0) {
				printf("getnameinfo() failed: %s\n", gai_strerror(s));
				exit(EXIT_FAILURE);
			}
			if(strcmp("127.0.0.1",host)!=0){
				//printf("My address is <%s>\n",host);
				strcpy(myIP,host);
			}
		}
	}
	freeifaddrs(ifaddr);
	
	return myIP;
}

// Grab the substring from character i to character j of the string *ch
char *substringOf(int i,int j,char *ch){
    int n,k=0;
    char *ch1;
    ch1=(char*)malloc((j-i+1)*1);
    n=j-i+1;

    while(k<n)
    {
        ch1[k]=ch[i];
        i++;k++;
    }

    return (char *)ch1;
}

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa){
	if (sa->sa_family == AF_INET) {
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}

	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}




/* References =====================================================================================
http://man7.org/linux/man-pages/man3/getifaddrs.3.html
https://stackoverflow.com/questions/16443780/how-to-return-a-char-array-from-a-function-in-c
http://beej.us/guide/bgnet/output/html/singlepage/bgnet.html#select





*/
