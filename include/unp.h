#ifndef __unp_h
#define __unp_h

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>	// va_list...
#include <syslog.h>	// LOG_ERR
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

#define MAXLINE 4096
#define SERV_PORT 9877

#define SA struct sockaddr

#endif

