#ifndef __CGI_DEVICE_MOTOR_FAN_HEAD__
#define __CGI_DEVICE_MOTOR_FAN_HEAD__

#include "common.h"
#include "protocol.h"

typedef struct _motor_fan{
	s_optDeviceInfo_t optdevice_info;
	char state[STRING_LEN];
}s_motorFan_t;

extern s_cgi_protocol_t pro_device_motor_fan[];

int cgi_get_device_motor_fan(void *sever, s_connection_t *con);


#endif

