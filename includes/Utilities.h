#ifndef UTILITIES_H
#define UTILITIES_H

#include <stddef.h>

typedef struct{
	char	*string;
	size_t	stringLength;
	size_t	bufferLenght;
	size_t	(*getLength)(void);
	void	(*append)(void *, size_t);
	void	(*destroy)(void);
} smart_string;

void		EXPORTTHIS(void *);
smart_string	*MakeNewSmartString(void);
void		SmartStringAppend(void *, size_t);
size_t		SmartStringGetLength(void);
size_t		DoxStrlen(const char *str);
size_t		GetMessageSize(const void*, int *, size_t);
unsigned long	GetTime(void);

#endif
