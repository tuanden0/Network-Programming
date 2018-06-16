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
		int i=0,j=0,k=0,l=0,n=0,flag=0;
		float e=0, s=0, c=0, d=0;
		char a[10],b[10];
		bzero(&server, sizeof(server));
		recvfrom(sock,buffer,sizeof(buffer),0,(struct sockaddr *)&client,&cli);
		printf("Client: %s",buffer);
		while(buffer[i]!='\0'){
			if(buffer[i]=='+' || buffer[i]=='-' || buffer[i]=='*' || buffer[i]=='/'){
				n=i;
				if(buffer[i]=='+'){
					flag=0;
				} else if(buffer[i]=='-'){
					flag=1;
				} else if(buffer[i]=='*'){
					flag=2;
				} else {
					flag=3;
				}
			}
			l=i-1;
			i++;
		}
		for(j=0;j<=n;j++){
			a[j]=buffer[j];
		}
		c=atof(a);
		for(k=0;k<l;k++){
			b[k]=buffer[n+1];
			n++;
		}
		d=atof(b);
		if(flag==0){
			bzero(&buffer, sizeof(buffer));
			e=c+d;
			sprintf(buffer,"%.2f",e);
			sendto(sock,buffer,sizeof(buffer),0,(struct sockaddr *)&client,cli);
		} else if(flag==1){
			bzero(&buffer, sizeof(buffer));
			e=c-d;
			sprintf(buffer,"%.2f",e);
			sendto(sock,buffer,sizeof(buffer),0,(struct sockaddr *)&client,cli);
		} else if(flag==2){
			bzero(&buffer, sizeof(buffer));
			e=c*d;
			sprintf(buffer,"%.2f",e);
			sendto(sock,buffer,sizeof(buffer),0,(struct sockaddr *)&client,cli);
		} else{
			bzero(&buffer, sizeof(buffer));
			s=c/d;
			sprintf(buffer,"%.2f",s);
			sendto(sock,buffer,sizeof(buffer),0,(struct sockaddr *)&client,cli);
		}
	}
	close(sock);
	return 0;
}
