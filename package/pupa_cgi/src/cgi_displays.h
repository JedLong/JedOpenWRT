#ifndef __CGI_DEVICE_DISPLAY_HEAD__
#define __CGI_DEVICE_DISPLAY_HEAD__

#include "common.h"
#include "protocol.h"

typedef struct _displays{
	s_optDeviceInfo_t optdevice_info;
	unsigned int content;
}s_displays_t;

extern s_cgi_protocol_t pro_device_displays[];

int cgi_get_device_displays(void *sever, s_connection_t *con);


#endif

