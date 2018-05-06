#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]){
	/* TCP */
	/* Variables */
	int sock, newsock;
	struct sockaddr_in server;
	char buffer[1024];
	int n;
	/* Socket */
	sock=socket(AF_INET,SOCK_STREAM,0);
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=INADDR_ANY;
	server.sin_port=htons(5000);		
	/* Bind */
	bind(sock,(struct sockaddr*)&server,sizeof(server));
	/* Listen */
	listen(sock,5);
	bzero(&server,sizeof(server));
	/* Accept */
	newsock=accept(sock,(struct sockaddr *)0,0);
	while(1){
		bzero(&buffer, sizeof(buffer));
		n=read(newsock, buffer,sizeof(buffer));
		printf("Client: %s", buffer);
		if(n==0){
			printf("Client disconnected.\n");
			break;
		}
		write(newsock, buffer, sizeof(buffer));
	}
	close(newsock);
	return 0;
}
