#include "MQTT_header.h"
#include <unistd.h>

int main(void)
{
	return write(1, "Hello World!\n", 13), 42;
}
