#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
void error_handling(char *message);
void Busy_waiting();


int main(int argc,char* argv[])
{
	int sock;
	struct sockaddr_in serv_addr;
	char message[500];
	int str_len;
	int read_len;


	if(argc!=3)
	{
		printf("Usage :%s <ip> <port>\n",argv[0]);
		exit(1);
	}
	sock=socket(PF_INET,SOCK_STREAM,0);
	if(sock == -1)
		error_handling("socket() error ");
	
	memset(&serv_addr,0,sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
	serv_addr.sin_port=htons(atoi(argv[2]));

	if(connect(sock,(struct sockaddr*)&serv_addr, sizeof(serv_addr))==-1)
		error_handling("connect() error ");
	
	Busy_waiting();
	
	read_len=read(sock,message,sizeof(message));
	if(read_len==-1)
		error_handling("read() error");	

	printf("Message form server : %s\n",message);
	close(sock);
	return 0;	
}

void error_handling(char *message)
{
	fputs(message,stderr);
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

