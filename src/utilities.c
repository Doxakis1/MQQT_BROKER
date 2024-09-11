#include "Utilities.h"
#include <sys/time.h>
#include <stdlib.h>

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

void EXPORTTHIS(void *this) {
	register void *ptr asm("r15");
	ptr  = this;
	(void)ptr;
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

smart_string *makeNewSmartString(void)
{
	smart_string    *returnString = (smart_string *)malloc(sizeof(smart_string));
	return returnString ? *returnString = (smart_string){NULL, 0, 0,&SmartStringGetLength, &SmartStringAppend , NULL} , returnString : returnString;
}

size_t SmartStringGetLength(void)
{
	int *this;
	EXPORTTHIS(this);
}

void SmartStringAppend(void *data, size_t length)
{
	
}
