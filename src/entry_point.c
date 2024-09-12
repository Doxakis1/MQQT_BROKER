#include "MQTT_header.h"
#include <unistd.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>

//TODO: remove stdio
#include <stdio.h>

int	initializeConnections(Connection *connections)
{
	for (int i = 0; i < MAX_CONNECTIONS; i++)
	{
		connections[i] = (Connection){0};
		connections[i].fd = i;
		if (pthread_mutex_init(&connections[i].connectionLock, NULL) != 0)
			return 1;
		connections[i].setTimeOut = DEFAULT_TIME_OUT;
	}
	return 0;
}



int main(int ac, char **av)
{
	ERROR("WTF before\n")
	smart_string *string1 = MakeNewSmartString();
	smart_string *string2 = MakeNewSmartString();
	//smart_string *string2 = MakeNewSmartString();
	EXPORTTHIS(string1);
	char *str = "FIRST world!";
	char *str2 = "SECOND world!\n";
	printf("string1 lentgth: %ld, string: %s\n", string1->getLength(), string1->getString());
	string1->append(str,DoxStrlen(str)); 
	printf("string1 lentgth: %ld, string: %s\n", string1->getLength(), string1->getString());
	EXPORTTHIS(string2);
	string2->append(str,DoxStrlen(str)); 
	string2->append(str2,DoxStrlen(str)); 
	EXPORTTHIS(string1);
	string1->append(str2,DoxStrlen(str)); 
	printf("string1 lentgth: %ld, string: %s\n", string1->getLength(), string1->getString());
	string1->destroy();
	EXPORTTHIS(string2);
	printf("string2 lentgth: %ld, string: %s\n", string2->getLength(), string2->getString());
	string2->destroy();
	exit(1);	
	struct sockaddr_in	serveraddr;
	const struct sockaddr	*serveraddr_ptr = (const struct sockaddr*)&serveraddr;
	struct sockaddr		clientSockaddr;
	socklen_t		len;
	int			serverfd;
	int			newClient;
	Connection		connections[MAX_CONNECTIONS];
	fd_set			inSet, outSet, copySet;
 	struct timeval		selectTimeOut;
//	char			inBuffer[BUFFER_SIZE];
	int			selectResult;

	if (ac != 2)
		return ERROR("Invalid ammount of arguements!\n\tPlease use by: mqqt_broker <port>\n");
	if (initializeConnections(connections))
		return ERROR("Failed to initialize connections!\n");
	//TODO: Handle signals
	FD_ZERO(&inSet);
	FD_ZERO(&outSet);
	FD_ZERO(&copySet);
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
	FD_SET(serverfd,&copySet);
	while(1)
	{
		selectTimeOut.tv_sec = 5; //select timeout to 5 secconds TODO:consider using a 
		selectTimeOut.tv_usec = 0;
		inSet = copySet;
		outSet = copySet;
		selectResult = select(MAX_CONNECTIONS, &inSet, &outSet, NULL, &selectTimeOut);
		if (selectResult == -1){
			ERROR("Selevt failed!\n");
		}else if (selectResult == 0){
			ERROR("Select timed out!\n");
		}else
		{
			for(int i = 0; i < MAX_CONNECTIONS; i++)
			{
				if (FD_ISSET(i, &inSet))
				{
					if ( i == serverfd){
						len = sizeof(struct sockaddr);
						newClient = accept(serverfd, &clientSockaddr, &len);
						if (newClient < 0){
							ERROR("Failed to accept new connection!\n");
						}else if (newClient == MAX_CONNECTIONS){
						//TODO: add logic to send to user the code that server is a max capacity as per MQTT protocol
						close(newClient);
						}else{
						//TODO: initialize new connection
						}
					}else{
						//TODO:add getting the message code here
						ERROR("We got a new message!\n");
					}
				}
			}
			
		}
		//Here will be added to code and logic to send msgs to clients
	} 
	return 1;
}


int testFunction(void)
{
	exit(1);
}
