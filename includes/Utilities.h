#ifndef UTILITIES_H
#define UTILITIES_H

#include <stddef.h>
#define ERROR(x) write(2, x, DoxStrlen(x));
typedef struct{
	char	*string;
	size_t	stringLength;
	size_t	bufferLength;
	char	*(*getString)(void);
	size_t	(*getLength)(void);
	void	(*append)(const void *,const size_t);
	void	(*destroy)(void);
} smart_string;

void		EXPORTTHIS(void *);
smart_string	*GETTHIS(void);
smart_string	*MakeNewSmartString(void);
void		SmartStringAppend(const void *,const size_t);
size_t		SmartStringGetLength(void);
char		*SmartStringGetString(void);
void		SmartStringDestroy(void);
size_t		DoxStrlen(const char *str);
size_t		GetMessageSize(const void*, int *, size_t);
unsigned long	GetTime(void);

#endif
