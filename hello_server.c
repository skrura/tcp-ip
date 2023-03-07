#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
void error_handling(char *message);
void Busy_waiting();

int main(int argc, char *argv[])
{
	int serv_sock;
	int clnt_sock;
	struct sockaddr_in serv_addr;
	struct sockaddr_in clnt_addr;
	socklen_t clnt_addr_size;

	char message[]="Hello tpc/ip!";
	char message_1[]="one";
	char message_2[]="two";
	char message_3[]="three";
	char message_4[]="four";
	char message_5[]="five";	

	if(argc!=2)
	{
	printf("Usage : %s <port>\n", argv[0]);
	exit(1);
	}
	serv_sock=socket(PF_INET,SOCK_STREAM,0);//found socket
	if(serv_sock == -1)		//error detection
		error_handling("socket() error");
	
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_addr.sin_port=htons(atoi(argv[1]));

	if(bind(serv_sock,(struct sockaddr*) &serv_addr, sizeof(serv_addr))==-1)
		error_handling("bing() error"); 	//distribution ip andport
	
	if(listen(serv_sock,5)==-1)	//Transition to accepttable connectionstate
		error_handling("listen() error");
	 
	clnt_addr_size = sizeof(clnt_addr);
	clnt_sock=accept(serv_sock,(struct sockaddr*)&clnt_addr,&clnt_addr_size);
	if(clnt_sock==-1)         //Accpet connection request
		error_handling("accept() error");
	
	int i=0;
	for(i=0;i<sizeof(message);i++)
	{
		write(clnt_sock,&message[i],1);
		printf("%c",message[i]);
	}
	printf("%d\n",i); 
	close(clnt_sock);
	close(serv_sock);
	return 0;
}

void error_handling(char *message)
{

	fputs(message, stderr);
	fputc('\n',stderr);
	exit(1);
}

void Busy_waiting()
{
	int i;
	for(i=0;i<3000;i++)
	{
		printf("wait time %d\n",i);
	}
}
