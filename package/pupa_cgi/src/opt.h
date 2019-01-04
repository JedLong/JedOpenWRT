#ifndef __OPT_HEAD__
#define __OPT_HEAD__

#include "common.h"
#include "cJSON.h"

typedef char *(function)(cJSON* response);

int print_devices_json_val(cJSON* response);
int print_devices_display_json_val(cJSON* response);
int print_device_temp_sensor_json_val(cJSON* response);
int print_device_motor_fan_json_val(cJSON* response);

char * json_object_to_buf(cJSON *jsonObj);
extern int opt(function *pcgi);

#endif

