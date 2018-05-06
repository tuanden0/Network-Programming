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
		int i=0,j=0,k=0,l=0,m=0,n=0,o=1,p=0,r=1,q=0;
		char s[10],a[10],b[10],c[10],d[]="It is a right triangle!",e[]="It is not a right triangle";
		bzero(&buffer, sizeof(buffer));
		n=read(newsock, buffer,sizeof(buffer));
		printf("Client: %s", buffer);
		if(n==0){
			printf("Client disconnected.\n");
			break;
		}
		while(buffer[i]!='\0'){
			if(buffer[i]==' '){
				s[j]=i;
				j++;
			}
			k=i-1;
			i++;
		}
		for(l=0;l<=s[0];l++){
			a[l]=buffer[l];
		}
		m=atoi(a);
		for(n=0;n<=s[1];n++){
			b[n]=buffer[s[0]+o];
			o++;
		}
		p=atoi(b);
		for(q=0;q<k;q++){
			c[q]=buffer[s[1]+r];
			r++;
		}
		q=atoi(c);
		if(m*m==(p*p+q*q) || p*p==(m*m+q*q) || q*q==(p*p+m*m)){
			write(newsock, d,sizeof(d));
		} else {
			write(newsock, e,sizeof(e));
		}
	}
	close(newsock);
	return 0;
}
