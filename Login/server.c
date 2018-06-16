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
	int sock, newsock, count=0;
	struct sockaddr_in server;
	char buffer[1024], u[1024], p[1024];
	char user[10]="root";
	char pass[10]="123456";
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
		int a_len=0, b_len=0;
		bzero(&buffer, sizeof(buffer));
		n=read(newsock, buffer,sizeof(buffer));
		printf("Client user: %s", buffer);
		if(n==0){
			printf("Client disconnected.\n");
			break;
		}
		a_len=strlen(buffer)-1; //remove '\n' 
		buffer[a_len]='\0'; //when using fgets
		strcpy(u,buffer);
		bzero(&server, sizeof(server));
		read(newsock, buffer,sizeof(buffer));
		printf("Client password: %s",buffer);
		b_len=strlen(buffer)-1; //remove '/n' 
		buffer[b_len]='\0'; //when using fgets
		strcpy(p,buffer);
		bzero(&server, sizeof(server));
		if(strcmp(user,u)==0 && strcmp(pass,p)==0){
			strcpy(buffer,"Congrats, <root>!\n");
			write(newsock, buffer, sizeof(buffer));
			break;
		} else {
			strcpy(buffer,"You’ve input wrong username/password\n");
			write(newsock, buffer, sizeof(buffer));
			count++;
			if(count>3){
				bzero(&server, sizeof(server));
				strcpy(buffer,"You’ve input wrong username/password more than 3 times, Server will close this connect.\n");
				write(newsock, buffer, sizeof(buffer));
				break;
			}
		}
	}
	close(newsock);
	return 0;
}
