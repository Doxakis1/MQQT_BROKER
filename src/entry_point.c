#include "MQTT_header.h"
#include <unistd.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/socket.h>
#include <netinet/in.h>

//TODO: remove stdio
#include <stdio.h>

int main(int ac, char **av)
{
	struct sockaddr_in	serveraddr;
	const struct sockaddr	*serveraddr_ptr = (const struct sockaddr*)&serveraddr;
	socklen_t		len;
	int			serverfd;
	
	if (ac != 2)
		return ERROR("Invalid ammount of arguements!\n\tPlease use by: mqqt_broker <port>\n");
	serverfd = socket(AF_INET, SOCK_STREAM | SOCK_CLOEXEC, 0);
    	if (serverfd == -1)
		return ERROR("Failed to initialize server socket!\n");
   	bzero(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
    	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    	serveraddr.sin_port = htons(atoi(av[1]));
	len  = sizeof(serveraddr);
	if (bind(serverfd, serveraddr_ptr, len) < 0)
		return ERROR("Failed to bind on serverfd!\n");
	if (listen(serverfd, BACKLOG_MAX) < 0)
		return ERROR("Failed to listen on serverfd!\n");
	return 1;
}
