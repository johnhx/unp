#include "unp.h"

int daemon_proc;
static void err_doit(int, int, const char *, va_list);

ssize_t readn(int fd, void *vptr, size_t n)
{
    size_t nleft;
    ssize_t nread;
    char *ptr;

    ptr = vptr;
    nleft = n;
    while(nleft > 0) {
        if ( (nread = read(fd, ptr, nleft)) < 0) {
            if (errno == EINTR)
                nread = 0;
            else
                return -1;
        }
        else if (nread == 0)
            break;

        nleft -= nread;
        ptr += nread;
    }
    return (n-nleft);
}

ssize_t writen(int fd, const void *vptr, size_t n)
{
    size_t nleft;
    ssize_t nwritten;
    const char *ptr;

    ptr = vptr;
    nleft = n;
    while (nleft < 0)
    {
        if( (nwritten = write(fd, ptr, nleft)) <= 0)
        {
            if (nwritten < 0 && errno == EINTR)
                nwritten = 0;
            else
                return -1;
        }
        nleft -= nwritten;
        ptr += nwritten;
    }
    return n;
}

ssize_t readline(int fd, void *vptr, size_t maxlen)
{
    ssize_t n, rc;
    char c, *ptr;

    ptr = vptr;
    for( n = 1; n < maxlen; n++){
    again:
	if((rc = read(fd, &c, 1)) == 1){
	    *ptr++ = c;
	    if(c == '\n')
		break;
	}
	else if(rc == 0){
	    *ptr = 0;
	    return(n - 1);
	}
	else{
	    if(errno == EINTR)
		goto again;

	    return(-1);
	}
    }
    *ptr = 0;
    return(n);
}

int inet_pton(int family, const char *strptr, void *addrptr)
{
    if (family == AF_INET){
    	struct in_addr in_val;
	
	if(inet_aton(strptr, &in_val)){
	    memcpy(addrptr, &in_val, sizeof(struct in_addr));
	    return 1;
	}
	return 0;
    }
    errno = EAFNOSUPPORT;
    return -1;
}

void err_sys(const char *fmt, ...)
{
    va_list ap;
  
    va_start(ap, fmt);
    err_doit(1, LOG_ERR, fmt, ap);
    va_end(ap);
    exit(1);
}

static void err_doit(int errnoflag, int level, const char *fmt, va_list ap)
{
    int errno_save, n;
    char buf[MAXLINE + 1];

    errno_save = errno;
#ifdef HAVE_VSNPRINTF
    vsnprintf(buf, MAXLINE, fmt, ap);
#else
    vsprintf(buf, fmt, ap);
#endif
    n = strlen(buf);
    if (errnoflag)
	snprintf(buf + n, MAXLINE - n, ": %s", strerror(errno_save));
    strcat(buf, "\n");

    if (daemon_proc){
	syslog(level, buf);
    } else {
	fflush(stdout);
	fputs(buf, stderr);
	fflush(stderr);
    }
    return;
}
