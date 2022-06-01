#include <SimpleApp.h>

int main(int argc, char *argv[])
{
	unsigned long port;
	char *port_c = NULL;
	char *ip = NULL;
	int optc;

	while((optc = getopt(argc, argv, "p:i:")) != -1)
	switch(optc)
		{
		case 'p':
			port_c = optarg;
			break;
		case 'i':
			ip = optarg;
			break;
		case '?':
			if (optopt == 'p' || optopt == 'i') {
				PrintLog("Option -%c requires an argument.\n", optopt);
				PrintHelp();
			} else if (isprint(optopt)) {
				PrintLog("Unknown option `-%c'.\n", optopt);
				PrintHelp();
			} else {
				PrintLog("Unknown option character `\\x%x'.\n", optopt);
				PrintHelp();
			}
			return 1;
	
		default:
		abort();
	}

	if(!port_c) {
		port = DEFAULT_PORT;
		PrintLog("Port is not specified, using default %ld\n", port);
	} else {
		port = strtol(port_c, NULL, 10);
	}

	if(ip) {
		BeRunAsClient(ip, port);
	} else {
		BeRunAsServer(port);
	}
}