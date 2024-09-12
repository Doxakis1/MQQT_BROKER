#ifndef UTILITIES_H
#define UTILITIES_H

#include <stddef.h>
#define ERROR(x) write(2, x, DoxStrlen(x));
#define SMART_STRING_SIZE sizeof(smart_string)
typedef char * smartString;

typedef struct {
	size_t	bufferSize;
	size_t	stringLength;
	char	string[];
}	smart_string;

smartString	MakeNewSmartString(void);
void		SmartStringAppend(smartString *, const void *, const size_t);
void		SmartStringDestroy(smartString *);
size_t		DoxStrlen(const char *);
size_t		GetMessageSize(const void*, int *, size_t);
unsigned long	GetTime(void);

#endif
