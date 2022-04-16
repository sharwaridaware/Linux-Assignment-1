#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<stdlib.h>
#include<string.h>
#include<netinet/in.h>

void handleClient(int connfd)
{
	int n;
	char buf[200];
	n = read(connfd,buf,200);
	buf[n] = '\0';
	printf("data rec'd from client = %s\n",buf);
	printf("requested handled by server %d\n",getpid());
	write(connfd,"Good bye",8);
	exit(0);
}

main()
{
	int sockfd,retval,n;
	
	socklen_t clilen;
	struct sockaddr_in cliaddr,servaddr;
	char buf[10000];
	sockfd = socket(AF_INET,SOCK_DGRAM,0);
	if(sockfd < 0)
	{
		perror("sock:");
		exit(1);
	}

	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port=htons(8000);

	retval=bind(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
	if(retval<0)
	{
		perror("bind:");
		exit(2);
	}

	while(1)
	{
		printf("before execution\n");
		n = recvfrom(sockfd,buf,10000,0,(struct sockaddr *)&cliaddr,&clilen);
		printf("rec'd %d bytes\n",n);
		buf[n] = '\0';
		printf("msg from client = %s\n",buf);
	}
	close(sockfd);
	

}
