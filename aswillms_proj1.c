//Andrew Willms
//9-22-2015
//CSE 489 Project 1

/*
References:
http://man7.org/linux/man-pages/man3/getifaddrs.3.html
https://stackoverflow.com/questions/16443780/how-to-return-a-char-array-from-a-function-in-c
http://beej.us/guide/bgnet/output/html/singlepage/bgnet.html#select





*/


#define _GNU_SOURCE     /* To get defns of NI_MAXSERV and NI_MAXHOST */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <ifaddrs.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <linux/if_link.h>


char *substringOf(int i,int j,char *ch);
char *localIP();
void handleDisplayRequest();

int main(int argc, char *argv[])
{
    int i=0,j=2;
    char str[]="String";
    char *test;

    test=substringOf(i,j,str);
    printf("%s\n",test);

	handleDisplayRequest();
    return 0;
}

// Grab the substring from character i to character j of the string *ch
char *substringOf(int i,int j,char *ch)
{
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
// Prints out required information for DISPLAY instruction
void handleDisplayRequest(){
	printf("Andrew S. Willms (aswillms)\naswillms@buffalo.edu\nLocal Process IP:   <%s>\nLocal Process Port: %d\n",localIP(),0);
}