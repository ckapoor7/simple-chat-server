#ifndef CHAT_SERVER
#define CHAT_SERVER

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define UNAMEMAX 50 //max length of an username
#define PORT "3490" //port which the user connects to
#define MAXDATASIZE 1000000 //max number of bytes that we can get at once (1MB)

#endif
