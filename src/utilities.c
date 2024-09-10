#include "Utilities.h"
#include <sys/time.h>

size_t	dox_strlen(const char *str)
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

unsigned long	getTime(void)
{
	long			time;
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	time = (current_time.tv_sec) * 1000
		+ (current_time.tv_usec / 1000);
	return (time);
}

