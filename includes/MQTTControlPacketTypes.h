#ifndef MQTT_CONTROL_PACKET_TYPES
#define MQTT_CONTROL_PACKET_TYPES

// The mqtt fixed header is the first byte recieved via mqtt protocol 
// The upper half of the 8 bits is used to denote the packet type and the lower bits are flags

//Packet types
#define HEADER_RESERVED 0 << 4
#define HEADER_CONNECT 1 << 4
#define HEADER_CONNACK 2 << 4
#define HEADER_PUBLISH 3 << 4
#define HEADER_PUBACK 4 << 4
#define HEADER_PUBREC 5 << 4
#define HEADER_PUBREL 6 << 4
#define HEADER_PUBCOMP 7 << 4
#define HEADER_SUBSCRIBE 8 << 4
#define HEADER_SUBACK 9 << 4
#define	UNSUBSCRIBE 10 << 4
#define	UNSUBACK 11 << 4
#define	PINGREQ 12 << 4
#define	PINGRESP 13 << 4
#define HEADER_DISCONNECT 14 << 4
#define HEADER_AUTH 15 << 4

//Packet flags
// Majority of the packet types do not have assosiated flags and there fore the lower half is zeroed and reserved

#define HEADER_PUBREC_FLAG 1 << 1
#define HEADER_SUBSCRIBE_FLAG 1 << 1
#define HEADER_UNSUBSCRIBE_FLAG 1 << 1
#define HEADER_PUBLISH_DUP 1 << 3
#define HEADER_PUBLISH_QOS_MAX_DELIVERY_NOT_ONCE 3 << 1
#define HEADER_PUBLISH_QOS_MIN_DELIVERY_ONCE 1 << 1
#define HEADER_PUBLISH_QOS_MAX_DELIVERY_ONCE 1 << 2

#endif
