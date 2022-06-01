#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <ctype.h>

#define MAX_BUFF_SIZE 1024
#define DEFAULT_PORT 9999

#define PrintLog(format, ...)   \
	fprintf(stderr, format, ##__VA_ARGS__)

#define PrintHelp() \
	PrintLog("Usage: ./SimpleApp [OPTIONS]\n"); \
	PrintLog("Application runs as server by default if -i is not specified\n"); \
	PrintLog("-i: Run as client, requires IP address for connection\n"); \
	PrintLog("-p: Port setting\n");

void BeRunAsServer(unsigned long port);
void BeRunAsClient(char * ip, unsigned long port);