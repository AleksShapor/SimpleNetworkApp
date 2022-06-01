#include <SimpleApp.h>

void MessegeSenderClient(int sockfd)
{
	char buff[MAX_BUFF_SIZE];
	int n;
	bzero(buff, MAX_BUFF_SIZE);
	printf("Enter the string : ");
	n = 0;
	while ((buff[n++] = getchar()) != '\n')
		;
	write(sockfd, buff, sizeof(buff));
	bzero(buff, sizeof(buff));
	read(sockfd, buff, sizeof(buff));
	PrintLog("Server response : %s\n", buff);
}

void BeRunAsClient(char * ip, unsigned long port) {
	int sockfd, err;
	struct sockaddr_in servaddr;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		PrintLog("Socket creation failed...\n");
		exit(0);
	} else {
		PrintLog("Socket successfully created...\n");
	}

	bzero(&servaddr, sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr(ip);
	servaddr.sin_port = htons(port);

	err = connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

	if (err != 0) {
	   PrintLog("Connection with the server failed...\n");
		exit(0);
	} else {
		PrintLog("Connected to the server...\n");
	}

	MessegeSenderClient(sockfd);
	close(sockfd);
}