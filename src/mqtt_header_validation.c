#include "MQTT_header.h"
#include "MQTTControlPackTypesHeaderMacros.h"
#include "utilities.h"
#include <unistd.h>


mqtt_packet ValidatePacket(SocketFileDescriptor fd)
{
	mqtt_packet newPacket = {.senderFd = fd;};
	HeaderByte header;
	return newPacket;
}
