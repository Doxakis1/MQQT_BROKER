#ifndef UTILITIES_H
#define UTILITIES_H

#include <stddef.h>
#define ERROR(x) write(2, x, DoxStrlen(x));
typedef struct{
	char	*string;
	size_t	stringLength;
	size_t	bufferLength;
	size_t	(*getLength)(void);
	void	(*append)(const void *,const size_t);
	void	(*destroy)(void);
} smart_string;

void		EXPORTTHIS(void *);
smart_string	*GETHIS(void);
smart_string	*MakeNewSmartString(void);
void		SmartStringAppend(const void *,const size_t);
size_t		SmartStringGetLength(void);
void		SmartStringDestroy(void);
size_t		DoxStrlen(const char *str);
size_t		GetMessageSize(const void*, int *, size_t);
unsigned long	GetTime(void);

#endif
