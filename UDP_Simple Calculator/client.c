#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

int main(int argc, char *argv[]){
	/* UDP */
	/* Variables */
	int sock, cli, n;
	struct sockaddr_in server, client;
	struct hostent *hp;
	char buffer[1024];
	/* Socket */
	sock=socket(AF_INET,SOCK_DGRAM,0);
	server.sin_family=AF_INET;
	server.sin_port=htons(5000);
	hp=gethostbyname(argv[1]);
	memcpy(&server.sin_addr, hp->h_addr, hp->h_length);
	cli=sizeof(struct sockaddr_in);
	/* Do somwthing */
	while(1){
		bzero(buffer, sizeof(buffer));
		printf("Your operation: ");
		fgets(buffer,sizeof(buffer),stdin);
		sendto(sock,buffer,sizeof(buffer),0,(struct sockaddr *)&server,cli);
		bzero(buffer, sizeof(buffer));
		recvfrom(sock,buffer,sizeof(buffer),0,(struct sockaddr *)&client,&cli);
		printf("Server: %s\n", buffer);
	}
	close(sock);
	return 0;
}
