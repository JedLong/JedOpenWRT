#ifndef __CGI_DEVICES_HEAD__
#define __CGI_DEVICES_HEAD__

#include "common.h"
#include "protocol.h"

extern s_cgi_protocol_t pro_devices_list[];

int cgi_get_all_devices_stat(void *sever, s_connection_t *con);


#endif