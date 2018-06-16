#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>

int matrix(int r, int c);
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
		int i=0,j=0,a=0,b=0,c=0,d=0,g=0,h=0,k=0,sum=0;
		char e[10],f[10];
		bzero(buffer, sizeof(buffer));
		recvfrom(sock,buffer,sizeof(buffer),0,(struct sockaddr *)&client,&cli);
		printf("Client: %s",buffer);
		while(buffer[a]!='\0'){
			if(buffer[a]==' '){
				b=a;
			}
			a++;
		}
		for(c=0;c<=b;c++){
			e[c]=buffer[c];
		}
		d=atoi(e);
		for(g=0;g<a-1;g++){
			f[g]=buffer[b+1];
			b++;
		}
		h=atoi(f);
		bzero(buffer, sizeof(buffer));
		k=matrix(d,h);
		sprintf(buffer,"Sum of first row is %d", k);
		sendto(sock,buffer,sizeof(buffer),0,(struct sockaddr *)&client,cli);
	}
	close(sock);
	return 0;
}

int matrix(int r, int c){
	int i=0, j=0, sum=0;
	int a[r][c];
	srand (time(NULL));
	printf("Client's matrix: \n");
	for(i=0;i<r;i++){
		for(j=0;j<c;j++){
			a[i][j]=rand()%100;
			printf("%d\t", a[i][j]);
		}
		printf("\n");
	}
	for(i=0;i<r;i++){
		for(j=0;j<c;j++){
			sum=sum+a[i][j];
		}
		break;
	}
	printf("Sum of first row is %d\n", sum);
	return sum;
}
