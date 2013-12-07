#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include "base64.h"

#define ERR_EXIT(m) \
	do{\
		perror (m);\
		exit(EXIT_FAILURE);\
	}while(0)
void do_service(int sockfd,char* message);

int main(int argc,char* argv[])
{
	
	int sockfd,ret;

	char body[] = "From:sky<sky@qq.com>\r\nTo:sky<sky@qq.com>\r\nSubject:hello\r\n\r\nHello World,Hello Email.\r\n.\r\n";
	if((sockfd = socket(AF_INET,SOCK_STREAM,0))<0)
		ERR_EXIT("socket error.");

	struct sockaddr_in servaddr;
	memset(&servaddr,0,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(25);
	servaddr.sin_addr.s_addr = inet_addr("12.34.56.78");
	
	if(connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr)) < 0)
		ERR_EXIT("connect error");

	do_service(sockfd,"HELO mail.qq.com\r\n");

	do_service(sockfd,"auth login\r\n");

	do_service(sockfd,"c3RldaVuLnpoYW4=\r\n");

	do_service(sockfd,"YWfWafd4kWloxMjM=\r\n");
	
	do_service(sockfd,"mail from:<sky@qq.com>\r\n");

	do_service(sockfd,"rcpt to:<sky@qq.com>\r\n");

	do_service(sockfd,"data\r\n");

	do_service(sockfd,body);

	close(sockfd);

	return 0;
}

void do_service(int sockfd,char* message)
{
	int ret;
	char recvBuf[200] = {0};
	char sendBuf[] = {0};

	memset(sendBuf,0,sizeof(sendBuf));
	strcpy(sendBuf,message);
	ret = write(sockfd,sendBuf,strlen(sendBuf));
	if(ret == -1)
		ERR_EXIT("write error.");

	memset(recvBuf,0,sizeof(recvBuf));
	ret = read(sockfd,recvBuf,sizeof(recvBuf));
	if(ret == -1)
		ERR_EXIT("read error.");
	fprintf(stderr,"%s",recvBuf);

}
