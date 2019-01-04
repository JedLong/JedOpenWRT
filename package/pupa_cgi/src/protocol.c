#include "protocol.h"
#include "cgi_devices.h"
#include "cgi_displays.h"
#include "cgi_motor_fan.h"
#include "cgi_temp_sensor.h"

int responce_json(cJSON* response, s_returnStatus_t *rt)
{
	cJSON_AddStringToObject(response, "message", rt->message);
	cJSON_AddNumberToObject(response, "status_code", rt->status_code); 
	return 0;
}

s_cgi_protocol_t *find_pro_handler2(s_cgi_protocol_t *pro,const char *pro_opt)
{
    int i = 0;
	
    if(pro_opt == NULL){
        return NULL;
    }
	
    while(1){
        if(pro[i].name == NULL)
            return NULL;
        if(strcmp(pro[i].name, pro_opt) == 0){
			JED_DEBUG("Found protocol: %s.\n", pro[i].name);
            return &pro[i];
        }
        i++;
    }
	
    return NULL;
}

s_cgi_protocol_t *find_pro_handler(const char* cgif, const char *pro_opt)
{
	int mlen =  0;
    s_cgi_protocol_t * t = NULL;
	
    if(cgif == NULL || pro_opt == NULL){
        return NULL;
    }

    if( IS_DEVICES(cgif) && ( t = find_pro_handler2(pro_devices_list,pro_opt) ) != NULL){
    }else if( IS_DISPLAY(cgif) && (t = find_pro_handler2(pro_device_displays,pro_opt)) != NULL){
    }else if( IS_MOTOR_MOTOR_FAN(cgif) && (t = find_pro_handler2(pro_device_motor_fan,pro_opt)) != NULL){
    }else if( IS_TEMP_SENSOR(cgif) && (t = find_pro_handler2(pro_temp_sensor,pro_opt)) != NULL){
    }
	
    return t;
}

