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

smart_string	*GETTHIS(void)
{
	smart_string *ptr;
	__asm__ __volatile__ (
    	"movq %%r15, %0"
    	: "=r"(ptr)
    	:
    	:
	);
	return ptr;
}

void EXPORTTHIS(void *this) {
	__asm__ __volatile__ (
    	"movq %0, %%r15"
    	:
    	: "r" (this)
    	: 
	);
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

void SmartStringDestroy()
{
	smart_string *this = GETTHIS();
	free(this->string);
	free(this);
}

smart_string *MakeNewSmartString(void)
{
	smart_string    *returnString = (smart_string *)malloc(sizeof(smart_string));
	if (returnString == NULL)
		return returnString;
	returnString->string = NULL;
	returnString->stringLength = 0;
	returnString->bufferLength = 0;
	returnString->getString = &SmartStringGetString;
	returnString->getLength = &SmartStringGetLength;
	returnString->append = &SmartStringAppend;
	returnString->destroy = &SmartStringDestroy;
	return returnString;
}

char *SmartStringGetString(void)
{
	smart_string *this = GETTHIS();
	return this->string;
}

size_t SmartStringGetLength(void)
{
	smart_string *this = GETTHIS();
	return this->stringLength;
}

void SmartStringAppend(const void *data, const size_t length)
{
	smart_string *this = GETTHIS();
	const char *newData = (const char *)data;
	size_t i = 0;
	while (this->bufferLength < (this->stringLength + length))
	{
		if (this->bufferLength == 0)
			this->bufferLength = 2;
		this->string  = realloc(this->string, this->bufferLength * 2);
		if(this->string == NULL){
			(void)ERROR("Failed to realloc in SmartStringAppend\n")
			exit(1);
		}
		this->bufferLength *= 2;	
	}
	while (i < length)
	{
		this->string[this->stringLength + i] = newData[i];
		i++;
	}
	this->stringLength += length - 1;
	this->string[this->stringLength] = '\0';
}
