#ifndef MQTT_CONTROL_PACKET_TYPES_HEADER_MACROS
#define MQTT_CONTROL_PACKET_TYPES_HEADER_MACROS
#include "Utilities.h"
// The mqtt fixed header is the first byte recieved via mqtt protocol 
// The upper half of the 8 bits is used to denote the packet type and the lower bits are flags

//Packet types
#define HEADER_RESERVED		0 << 4
#define HEADER_CONNECT		1 << 4
#define HEADER_CONNACK		2 << 4
#define HEADER_PUBLISH		3 << 4
#define HEADER_PUBACK		4 << 4
#define HEADER_PUBREC		5 << 4
#define HEADER_PUBREL		6 << 4
#define HEADER_PUBCOMP		7 << 4
#define HEADER_SUBSCRIBE	8 << 4
#define HEADER_SUBACK		9 << 4
#define	UNSUBSCRIBE		10 << 4
#define	UNSUBACK		11 << 4
#define	PINGREQ			12 << 4
#define	PINGRESP		13 << 4
#define HEADER_DISCONNECT	14 << 4
#define HEADER_AUTH		15 << 4

//Packet flags
// Majority of the packet types do not have assosiated flags and there fore the lower half is zeroed and reserved
#define HEADER_PUBREC_FLAG				1 << 1
#define HEADER_SUBSCRIBE_FLAG				1 << 1
#define HEADER_UNSUBSCRIBE_FLAG				1 << 1
#define HEADER_PUBLISH_DUP				1 << 3
#define HEADER_PUBLISH_QOS_MAX_DELIVERY_NOT_ONCE	3 << 1
#define HEADER_PUBLISH_QOS_MIN_DELIVERY_ONCE		1 << 1
#define HEADER_PUBLISH_QOS_MAX_DELIVERY_ONCE		1 << 2

//Reason Codes
//A one byte usinged value that indicates he result of an operation codes less than		0x80 are success codes
//while codes above		0x80 indicate error
//Bellow are the definitions of the Reason Codes followed by the packets that support/use them
#define RC_SUCCESS					0x0 //CONNACK,PUBACK. PUBREC, PUBREL, PUBCOMP, UNSUBACK, AUTh
#define RC_NORMAL_DISCONNECT				0x0 //DISCONNECT
#define RC_GRANTED_ZERO_QOS				0x0 //SUBACK
#define RC_GRANTED_ONE_QOS				0x1 //SUBACK
#define RC_GRANTED_TWO_QOS				0x2 //SUBACK
#define RC_DISCONNECT_WITH_WILL_MESSAGE			0x4 //DISCONNECT
#define RC_NO_MATCHING_SUBSCRIBERS			0x10 //PUBACK, PUBREL
#define RC_NO_SUBCRIPTION_EXISTED			0x11 //UNSUBACK
#define RC_CONTINUE_AUTHENTICATION			0x18 //AUTH
#define RC_REQUEST_AUTHENTICATION			0x19 //AUTH
#define RC_UNSPECIFIED_ERROR				0x80 //CONNACK, PUBACK, PUBREC, SUBACK, UNSUBACK, DISCONNECT
#define RC_MALFORMED_PACKET				0x81 //CONNACK, DISCONNECT
#define RC_PROTOCOL_ERROR				0x82 //CONNACK, DISCONNECT
#define RC_IMPLEMENTATION_SPECIFIC_ERROR		0x83 //CONNACK, PUBACK, PUBREC, SUBACK, UNNSUBACK, DISCONNECT
#define RC_UNSUPPORTED_PROTOCOL_VERSION			0x84 //CONNACK
#define RC_CLIENT_IDENTFIER_INVALID			0x85 //CONNACK
#define RC_BAD_CREDENTIALS				0x86 //CONNACK
#define RC_NOT_AUTHORIZED				0x87 //CONNACK, PUBACK, PUBREC, SUBACK, UNSUBACK, DISCONNECT
#define RC_SERVER_UNAVAIBLE				0x88 //CONNACK
#define RC_SERVER_BUSY					0x89 //CONNACK, DISCONNECT
#define RC_BANNED					0x8A //CONNACK
#define RC_SERVER_SHUTTING_DOWN				0x8b //dISCONNECT
#define RC_BAD_AUTHENTICATION_METHOD			0x8C //CONNACK, DISCONNECT
#define RC_KEEP_ALIVE_TIMEOUT				0x8D //DISCONNECT
#define RC_SESSION_TAKE_OVER				0x8e //DISCONNECT
#define RC_TOPIC_FILTER_INVALID				0x8F //SUBACK, UNSUBACK, DISCONNECT
#define RC_TOPIC_NAME_INVALID				0x90 //CONNACK, PUBACK, PUBREC, DISCONNECT
#define RC_PACKET_IDENTIFIER_IN_USE			0x91 //PUBACK, PUBREC, SUBACK, UNSUBACK
#define RC_PACKET_IDENTIFIER_NOT_FOUND			0x92 //PUBREL, PUBCOMP
#define RC_RECEIVE_MAXIMUM_EXCEEDED			0x93 //DISCONNECT
#define RC_TOPIC_ALIAS_INVALID				0x94 //DISCONNECT
#define RC_PACKET_TOO_LARGE				0x95 //CONNACK, DISCONNECT
#define RC_MESSAGE_RATE_TOO_HIGH			0x96 //DISCONNECT
#define RC_QUOTA_EXCEEDED				0x97 //CONNACK, PUBREC, SUBACK, DISCONNECT
#define RC_ADMINISTRATIVE_ACTION			0x98 //DISCONNECT
#define RC_PAYLOAD_FORMAT_INVALID			0x99 //CONNACK, PUBACK, PUBREC, DISCONNECT
#define RC_RETAIN_NOT_SUPPORTED				0x9A //CONNACK, DISCONNECT
#define RC_QOS_UNSUPPORTED				0x9B //CONNACK, DISCONNECT
#define RC_USER_OTHER_SERVER				0x9C //CONNACK, DISCONNECT
#define RC_SERVER_MOVED					0x9D //CONNACK, DISCONNECT
#define RC_SHARED_SUBSCRIPTIONS_NOT			0x9E //SUBACK, DISCONNECT
#define RC_CONNECTION_RATE_EXCEEDED			0x9F //CONNACK, DISCONNECT
#define RC_MAXIMUM_CONNECT_TIME				0xA0 //DISCONNECT
#define RC_SUBSCRIPTION_IDENTIFIER_NOT_SUPPORTED	0xA1 //SUBACK, DISCONNECT#define RC_WILDCARD_SUBSCRIPTION_NOT_SUPPORTED		0xA2 //SUBACK, DISCONNECT
#define RC_WILDCARD_SUBSCRIPTION_NOT_SUPPORTED		0xA2 //SUBACK, DISCONNECT

typedef unsigned char	HeaderByte;
typedef	unsigned char	HeaderType;
typedef	unsigned char	HeaderFlags;
typedef int		SocketFileDescriptor;

typedef struct {
	HeaderType		type;
	HeaderFlags		flags;
	SocketFileDescriptor	senderFd;
	char			*headerStart;
	char			*vHeaderStart;
	char			*payloadStart;
	size_t			packetLength;
}	mqtt_packet;

mqtt_packet ValidatePacket(SocketFileDescriptor fd);

#endif
