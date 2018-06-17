#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void matrix(int r, int c);
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
		int key=0,i=0;
		char text[1024];
		bzero(&buffer, sizeof(buffer));
		n=read(newsock, buffer,sizeof(buffer));
		printf("Client text: %s", buffer);
		if(n==0){
			printf("Client disconnected.\n");
			break;
		}
		strcpy(text,buffer);
		bzero(&buffer, sizeof(buffer));
		read(newsock, buffer,sizeof(buffer));
		printf("Client key: %s", buffer);
		key=atoi(buffer);
		for(i=0;i<strlen(text)-1;i++){
			if(islower(text[i])){
            			text[i]=(text[i]+key-97)%26+97;
			} else {
				text[i]=(text[i]+key-65)%26+65;
			}
    		}
		printf("Encrypted: %s", text);
		write(newsock, text, sizeof(text));
		bzero(&text, sizeof(text));
	}
	close(newsock);
	return 0;
}

