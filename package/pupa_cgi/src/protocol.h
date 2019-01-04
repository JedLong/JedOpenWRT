#ifndef __PROTOCOL_HEAD__
#define __PROTOCOL_HEAD__

#include "common.h"

/*register devices.*/
#define PRO_SUPPORT_DEVICES   			"devices"
#define PRO_SUPPORT_DISPLAYS  			"displayer"
#define PRO_SUPPORT_MOTOR_FAN			"motor_fan"
#define PRO_SUPPORT_TEMP_SENSOR 		"temp_sensor"

#define IS_DEVICE(fn,adev) 				(!strncmp(fn, adev,MIXSTR(strlen(fn), strlen(adev))))
#define IS_DEVICES(fn)					IS_DEVICE(fn, PRO_SUPPORT_DEVICES)
#define IS_DISPLAY(fn)					IS_DEVICE(fn, PRO_SUPPORT_DISPLAYS)
#define IS_MOTOR_MOTOR_FAN(fn)			IS_DEVICE(fn, PRO_SUPPORT_MOTOR_FAN)
#define IS_TEMP_SENSOR(fn)				IS_DEVICE(fn, PRO_SUPPORT_TEMP_SENSOR)

typedef struct _cgi_protocol_t{
        const char *name;                 /* function name*/
        //int (*handler)(server_t*, s_connection_t *, buffer_t *); /*function handler*/
		int (*handler)(void*, s_connection_t *); /*function handler*/
}s_cgi_protocol_t, *cgi_protocol_tp;

s_cgi_protocol_t *find_pro_handler(const char *cgif, const char *pro_opt);
char *test_string(char *dhd);
int responce_json(cJSON* response, s_returnStatus_t *rt);


#endif

