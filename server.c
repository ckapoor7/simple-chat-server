#include "chat-server.h"

//Get the (IPv4) socket address
void *get_in_addr(struct sockaddr *sa){
  return &(((struct sockaddr_in*)sa)->sin_addr); //cast into a pointer
}

int main(int argc, char *argv[]){
  int sockfd, new_fd; //File descriptors for the connecting and listening sockets
  struct addrinfo hints, *servinfo, *p;
  struct sockaddr_storage their_addr; //Connector's address
  socklen_t sin_size; //Length of the address
  struct sigaction sa; //Examine and change signal action
  int yes = 1;
  char s[INET6_ADDRSTRLEN]; //Length of IPv6 address
  int rv;

  //Standard stuff follows...
  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_INET; //Specifically IPv4
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  if ((rv = getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0){
    fprintf(stderr, "getaddrinfo : %s\n", gai_strerror(rv));
    return 1;
  }

  //Iterate through, and bind to the first available port
  for (p = servinfo; p!=NULL; p = p->ai_next){
    if ((sockfd = socket(p->ai_family, p->ai_socktype,
			 p->ai_protocol)) == -1) {
      perror("server: socket");
      continue;
    }
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes,
		   sizeof(int)) == -1) {
      perror("setsockopt");
      exit(1);
    }
    if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
      close(sockfd);
      perror("server: bind");
      continue;
    }
    break;
  }

  freeaddrinfo(servinfo); //Free the pointer

  //A bunch of error checks
  if (p == NULL) {
    fprintf(stderr, "server: failed to bind\n");
    exit(1);
 }
  /*
  if (listen(sockfd, BACKLOG) == -1) {
    perror("listen");
    exit(1);
  }
  
  sa.sa_handler = sigchld_handler; // yield all dead processes
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = SA_RESTART;
  
  if (sigaction(SIGCHLD, &sa, NULL) == -1) {
    perror("sigaction");
    exit(1);
    }*/

  printf("server: waiting for connections...\n");
  

  return 0;
}
