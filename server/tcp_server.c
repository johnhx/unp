#include "unp.h"

void str_echo(int sockfd)
{
    ssize_t n;
    char    buf[MAXLINE];

again:
    while( (n = read(sockfd, buf, MAXLINE)) > 0 )
    {
        writen(sockfd, buf, n);
    }

    if (n < 0 && errno == EINTR)
        goto again;
    else if (n < 0)
        err_sys("str_echo: read error");
}

int main(int argc, char *argv[])
{
    int listenfd, connfd;
    pid_t childpid;
    socklen_t clilen;
    struct sockaddr_in servaddr, cliaddr;
    int sin_size;
    char buf[BUFSIZ];
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);

    if((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 )
    {
        perror("socket");
        return 1;
    }

    if(bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("bind");
        return 1;
    }

    listen(listenfd, 5);
    for( ; ; ){
	clilen = sizeof(cliaddr);
	if((connfd = accept(listenfd, (struct sockaddr*)&cliaddr, &clilen)) < 0){
	    perror("accept");
	    return 1;
	}

	if((childpid = fork()) == 0){
	    close(listenfd);
	    str_echo(connfd);
	    exit(0);
	}
	close(connfd);
    }
}
