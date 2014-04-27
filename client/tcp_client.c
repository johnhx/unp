#include "unp.h"

void str_cli(FILE *fp, int sockfd);

int main(int argc, char **argv)
{
    int sockfd;
    struct sockaddr_in servaddr;

    if(argc != 2){
	// err_quit("usage tcp_client <IPaddress>");
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

    if(connect(sockfd, (SA *)&servaddr, sizeof(servaddr)) < 0){
    	perror("connect");
	return 1;
    }

    str_cli(stdin, sockfd);

    exit(0);    
}

void str_cli(FILE *fp, int sockfd)
{
    char sendline[MAXLINE], recvline[MAXLINE];
    while(fgets(sendline, MAXLINE, fp) != NULL){
    	writen(sockfd, sendline, strlen(sendline));
	if(readline(sockfd, recvline, MAXLINE) == 0){
	    // err_quit("str_cli: server terminated prematurely");
	}

	fputs(recvline, stdout);
    }
}
