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
	int sock, n, cli, count=0;
	struct sockaddr_in server, client;
	char buffer[1024], u[1024], p[1024];
	char user[10]="root";
	char pass[10]="123456";
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
		int a_len=0, b_len=0;
		bzero(buffer, sizeof(buffer));
		recvfrom(sock,buffer,sizeof(buffer),0,(struct sockaddr *)&client,&cli);
		printf("Client user: %s",buffer);
		a_len=strlen(buffer)-1; //remove '/n' 
		buffer[a_len]='\0';	//when using fgets
		strcpy(u,buffer);
		bzero(buffer, sizeof(buffer));
		recvfrom(sock,buffer,sizeof(buffer),0,(struct sockaddr *)&client,&cli);
		printf("Client password: %s",buffer);
		b_len=strlen(buffer)-1; //remove '/n' 
		buffer[b_len]='\0'; //when using fgets
		strcpy(p,buffer);
		bzero(buffer, sizeof(buffer));
		if(strcmp(user,u)==0 && strcmp(pass,p)==0){
			strcpy(buffer,"Congrats, <root>!\n");
			sendto(sock,buffer,sizeof(buffer),0,(struct sockaddr *)&client,cli);
			break; //or do something here
		} else {
			strcpy(buffer,"You’ve input wrong username/password\n");
			sendto(sock,buffer,sizeof(buffer),0,(struct sockaddr *)&client,cli);
			count++;
			if(count>3){
				bzero(buffer, sizeof(buffer));
				strcpy(buffer,"You’ve input wrong username/password more than 3 times, Server will close this connect.\n");
				sendto(sock,buffer,sizeof(buffer),0,(struct sockaddr *)&client,cli);
				break;
			}
		}
	}
	close(sock);
	return 0;
}
