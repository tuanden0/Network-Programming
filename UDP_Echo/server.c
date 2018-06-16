#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]){
	/* UDP */
	/* Variables */
	int sock, n, cli;
	struct sockaddr_in server, client;
	char buffer[1024];
	/* Socket */
	sock=socket(AF_INET,SOCK_DGRAM,0);
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=INADDR_ANY;
	server.sin_port=htons(5000);
	/* Bind */
	bind(sock,(struct sockaddr *)&server,sizeof(server));
	cli=sizeof(struct sockaddr_in);
	bzero(&server,sizeof(server));
	/* Do something */
	while(1){
		recvfrom(sock,buffer,sizeof(buffer),0,(struct sockaddr *)&client,&cli);
		printf("Client: %s",buffer);
		sendto(sock,buffer,sizeof(buffer),0,(struct sockaddr *)&client,cli);
	}

	close(sock);
	return 0;
}
