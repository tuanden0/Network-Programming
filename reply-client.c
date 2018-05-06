#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

int main(int argc, char *argv[]){
	/* TCP */
	/* Variables */
	int sock;
	struct sockaddr_in server;
	struct hostent *hp;
	char buffer[1024];
	/* Socket */
	sock=socket(AF_INET,SOCK_STREAM,0);
	server.sin_family=AF_INET;
	server.sin_port=htons(5000);
	hp=gethostbyname(argv[1]);
	memcpy(&server.sin_addr, hp->h_addr, hp->h_length);
	/* Connect */
	connect(sock,(struct sockaddr *)&server,sizeof(server));
	while(1){
		
		printf("Your message: ");
		bzero(&buffer, sizeof(buffer));
		fgets(buffer,sizeof(buffer),stdin);
		write(sock,buffer,sizeof(buffer));
		bzero(&buffer, sizeof(buffer));
		read(sock,buffer,sizeof(buffer));
		printf("Server: %s", buffer);
	}
	close(sock);
	return 0;
}
