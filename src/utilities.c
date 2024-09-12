#include "Utilities.h"
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>
//TODO: remove stdio
#include <stdio.h>

size_t	DoxStrlen(const char *str)
{
	size_t len = 0;
	if (!str)
		return len;
	while (str[len++])
		;
	return len;
}

size_t	GetMessageSize(const void *vbyteStart, int *vbyteSize, size_t maxBytes)
{
	size_t	message_size = 0;
	size_t	currentByteIndex = 0;
	size_t	value = 0;
	int	shift = 7; 
	const unsigned char *bytes = (unsigned char *)vbyteStart;
	if (!vbyteStart)
		return message_size;
	while(currentByteIndex < maxBytes)
	{
		value = (size_t)(bytes[currentByteIndex]);
		message_size = (value & 127) | (message_size << shift);
		if ((value >> 7) == 1)
			break ;
		currentByteIndex++;
	}
	*vbyteSize = currentByteIndex;
	return message_size;
}

unsigned long	GetTime(void)
{
	long			time;
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	time = (current_time.tv_sec) * 1000
		+ (current_time.tv_usec / 1000);
	return (time);
}

smartString MakeNewSmartString(void){
	smart_string *newString;
	newString = (smart_string *)malloc(sizeof(smart_string) + 1);
	if (newString == NULL)
		return NULL;
	newString->bufferSize = 1;
	newString->stringLength = 0;
	newString->string[0] = '\0';
	return newString->string;
}

void	SmartStringAppend(smartString *str, const void *str2, const size_t len)
{
	size_t i = 0;
	smart_string *ptr = (smart_string *)(*str - SMART_STRING_SIZE);
	while (ptr->bufferSize < (ptr->stringLength + len + 1))
	{	
		ptr = (smart_string *)realloc(ptr, SMART_STRING_SIZE + ptr->bufferSize * 2);
		if (ptr == NULL)
			exit(1);
		ptr->bufferSize *= 2;
		ptr->bufferSize++;
	}
	while (i < len)
	{
		ptr->string[ptr->stringLength + i] = ((char *)str2)[i];
		i++;
	}
	ptr->stringLength += len;
	ptr->string[ptr->stringLength] = '\0';
	*str = ptr->string;
	
}

void SmartStringDestroy(smartString *str)
{
	smart_string *ptr = (smart_string *)(*str - SMART_STRING_SIZE);
	free(ptr);
	*str = NULL;
}

