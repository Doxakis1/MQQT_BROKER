#ifndef MQTT_HEADER_H
#define MQTT_HEADER_H

#include "MQTTControlPacketTypesHeaderMacros.h"
#include "Utilities.h"
#include <stdbool.h>
#include <pthread.h>
#define SIZE_T_MAX sizeof(size_t)
#define MAX_CONNECTIONS 1025
#define BUFFER_SIZE 1024
#define ERROR(x) write(2, x, dox_strlen(x));
#define BACKLOG_MAX 1024 //maximum connection queue 
#define DEFAULT_TIME_OUT (unsigned long)100000 //100 seconds

typedef unsigned long time_in_ms;
typedef	pthread_mutex_t connection_lock;

typedef struct{
	int		fd;
	bool		inUse;
	void		*data;
	size_t		dataLen;
	time_in_ms	timeOfLastIncompleteMsg;
	time_in_ms	timeOfLastMsg;
	time_in_ms	setTimeOut;
	connection_lock	connectionLock;	
} Connection;

#endif
