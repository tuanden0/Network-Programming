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
		int i=0,j=0,a=0,b=0,c=0,d=0,g=0,h=0,k=0,ch;
		char e[10],f[10],content[1024];
		FILE *file;
		bzero(&buffer, sizeof(buffer));
		n=read(newsock, buffer,sizeof(buffer));
		printf("Client: %s", buffer);
		if(n==0){
			printf("Client disconnected.\n");
			break;
		}
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
		matrix(d,h);
		file=fopen("temp", "r");
		if(file){
			printf("Sending file to Client....\n");
			while((c=getc(file))!=EOF){
				content[i]=c;
				i++;
			}
			close(file);
			strcpy(buffer,content);
			write(newsock, buffer, sizeof(buffer));
			printf("Done!\n");
		} else {
			strcpy(buffer,"Can't create the matrix\n");
			write(newsock, buffer, sizeof(buffer));
		}
		
	}
	close(newsock);
	return 0;
}

void matrix(int r, int c){
	int i=0, j=0;
	int a[r][c];
	FILE *fp;
	srand (time(NULL));
	printf("Client's matrix: \n");
	fp=fopen("temp", "w");
	if(fp){
		for(i=0;i<r;i++){
			for(j=0;j<c;j++){
				a[i][j]=rand()%100;
				printf("%d\t", a[i][j]);
				fprintf(fp,"%d\t", a[i][j]);
			}
			printf("\n");
			fprintf(fp,"\n");
		}
		fclose(fp);
	}
}
