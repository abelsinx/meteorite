#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 8080

int main(int argc, char const *argv[]){
	
	int sockfd, new_sock;     //the socket file descriptor
	int opt = 1;
	struct sockaddr_in address;
	char buffer[1024] = {0};
	int bufflen = sizeof(buffer);
	ssize_t valread;
	int addrlen = sizeof(address);	
	//creating the socket
	//AF_INET says its IP
	//SOCK_STREAM says it is TCP
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		perror("error creating the socket");
		exit(1);
	}
	
	//making the socket addr and por reuseable.
	if((setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, 
					sizeof(opt))) < 0){
		perror("SetSock");
		exit(2);
	}
	
	address.sin_family = AF_INET;
	address.sin_port = htons(PORT);
	address.sin_addr.s_addr = INADDR_ANY;
	
	//attaching(binding) socket with port and address.
	if((bind(sockfd, (struct sockaddr *) &address, 
					(socklen_t) addrlen)) < 0){
		perror("Binding problems");
		exit(3);
	}

	//Listening
	//while(0 < 1){
		printf("\nGOT HERE1");
		if((listen(sockfd,3)) < 0){
			perror("Listen problems");
			exit(4);
		}
		
		//accepting the connection and making anew socket 
		//where the data will go through
		printf("\nGOT HERE2");
		if((new_sock = accept(sockfd, (struct sockaddr *) &address, 
						(socklen_t *) &addrlen)) < 0){
			perror("Accepting connection");
			exit(5);
		}
		
		printf("\nGOT HERE3");
		for (int i=0; i<3; i++){
			dup2(i, new_sock);
		}
		//if((valread = recv(new_sock, buffer, 1024, 0)) < 0){
		//	perror("data unable to be printed\n");
		//	exit(6);
		//}
		//else{
			//printf("\n%d\n", valread);
		//	printf("%s\n", buffer);
		//	memset(buffer, '\0', sizeof(buffer)); //cleaning the buffer

		//}
	//}

	return 0;
}
