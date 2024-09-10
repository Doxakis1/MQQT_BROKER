#ifndef MQTT_HEADER_H
#define MQTT_HEADER_H

#include "MQTTControlPacketTypesHeaderMacros.h"
#include "Utilities.h"
#define SIZE_T_MAX sizeof(size_t)

#define ERROR(x) write(2, x, dox_strlen(x));
#define BACKLOG_MAX 42
#endif
