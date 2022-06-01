#include <SimpleApp.h>

static const char server_response[] = "I received message, thank you!\n";
static const ssize_t server_response_size = sizeof(server_response);

void Daemonize(void) {
	switch (fork()) {
	case 0:
		break;
	case -1:
		PrintLog("Error forking!\n");
		exit(0);
		break;
	default:
		_exit(0);
	}

	if (setsid() < 	0) {
		PrintLog("Error daemonizing!");
		exit(0);
	}
}

void MessengeSender(int connfd) {
	if (send(connfd, server_response, server_response_size, 0) < 0) {
		PrintLog("Failing sending response!");
	}
}

void MessengeHandler(int connfd) {
	char * buff = malloc(MAX_BUFF_SIZE);

	bzero(buff, MAX_BUFF_SIZE);
	read(connfd, buff, MAX_BUFF_SIZE);
	PrintLog("Server received: %s\n", buff);
	free(buff);

	MessengeSender(connfd);
}

void BeRunAsServer(unsigned long port) {
	int sockfd, connfd, err;
	struct sockaddr_in servaddr, cli;
	socklen_t len;

	Daemonize();

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		PrintLog("Socket creation failed...\n");
		exit(0);
	} else {
		PrintLog("Socket successfully created...\n");
	}

	bzero(&servaddr, sizeof(servaddr));
	
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(port);

	err = bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
	if (err != 0) {
		PrintLog("Socket bind failed...\n");
		exit(0);
	} else {
		PrintLog("Socket successfully binded...\n");
	}

	for(;;) {
		err = listen(sockfd, 1);
		if (err != 0) {
			PrintLog("Listen failed...\n");
			exit(0);
		} else {
			PrintLog("Server listening on %ld...\n", port);
		}

		len = sizeof(cli);

		connfd = accept(sockfd, (struct sockaddr *)&cli, &len);
		if (connfd < 0) {
			PrintLog("Server accept failed...\n");
			exit(0);
		} else {
			PrintLog("Server accept the client...\n");
		}

		MessengeHandler(connfd);

		close(connfd);
	}

	close(sockfd);
}