#ifndef __CGI_TEMP_SENSOR_HEAD__
#define __CGI_TEMP_SENSOR_HEAD__

#include "common.h"
#include "protocol.h"

typedef struct _temperatureSensor{
	s_optDeviceInfo_t optdevice_info;
	int tempperature;
	char units[1];		//[c,f]
}s_temperatureSensor_t;

extern s_cgi_protocol_t pro_temp_sensor[];

int cgi_get_temp_sensor_stat(void *sever, s_connection_t *con);


#endif