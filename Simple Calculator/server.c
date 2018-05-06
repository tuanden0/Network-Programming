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
		int i=0,j=0,k=0,l=0,n=0,flag=0,c=0,d=0,e=0;
		char a[10],b[10];
		bzero(&buffer, sizeof(buffer));
		n=read(newsock, buffer,sizeof(buffer));
		printf("Client: %s", buffer);
		if(n==0){
			printf("Client disconnected.\n");
			break;
		}
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
		c=atoi(a);
		for(k=0;k<l;k++){
			b[k]=buffer[n+1];
			n++;
		}
		d=atoi(b);
		if(flag==0){
			bzero(&buffer, sizeof(buffer));
			e=c+d;
			sprintf(buffer,"%d",e);
			write(newsock, buffer, sizeof(buffer));
		} else if(flag==1){
			bzero(&buffer, sizeof(buffer));
			e=c-d;
			sprintf(buffer,"%d",e);
			write(newsock, buffer, sizeof(buffer));
		} else if(flag==2){
			bzero(&buffer, sizeof(buffer));
			e=c*d;
			sprintf(buffer,"%d",e);
			write(newsock, buffer, sizeof(buffer));
		} else{
			bzero(&buffer, sizeof(buffer));
			float s;
			s=(float)c/d;
			sprintf(buffer,"%.2f",s);
			write(newsock, buffer, sizeof(buffer));
		}
	}
	close(newsock);
	return 0;
}
