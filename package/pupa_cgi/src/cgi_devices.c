#include "cgi_devices.h"
#include "opt.h"


int print_devices_json_val(cJSON* response)
{
	cJSON *rootArray = cJSON_CreateArray();
	
	cJSON *devicesObj = cJSON_CreateObject();
	cJSON_AddNumberToObject(devicesObj, "device_id", 23);
	cJSON_AddStringToObject(devicesObj, "device_type", "temp_sensor");
	cJSON_AddStringToObject(devicesObj, "power_status", "on");
	cJSON_AddStringToObject(devicesObj, "usb_module_status", "connected");
	cJSON_AddItemToArray(rootArray, devicesObj);
	
	devicesObj = cJSON_CreateObject();
	cJSON_AddNumberToObject(devicesObj, "device_id", 24);
	cJSON_AddStringToObject(devicesObj, "device_type", "disply");
	cJSON_AddStringToObject(devicesObj, "power_status", "off");
	cJSON_AddStringToObject(devicesObj, "usb_module_status", "connected");
	cJSON_AddItemToArray(rootArray, devicesObj);

	devicesObj = cJSON_CreateObject();
	cJSON_AddNumberToObject(devicesObj, "device_id", 25);
	cJSON_AddStringToObject(devicesObj, "device_type", "motor_fan");
	cJSON_AddStringToObject(devicesObj, "power_status", "off");
	cJSON_AddStringToObject(devicesObj, "usb_module_status", "disconnected");
	cJSON_AddItemToArray(rootArray, devicesObj);

	cJSON_AddItemToObject(response, "devices", rootArray);
	//char *buf = json_object_to_buf(response);
	
	//cJSON_Delete(rootArray);
	
	return 0;
}

int cgi_get_all_devices_stat(void *sever, s_connection_t *con)
{
	int res = 0;

	if(!IS_FUNC_GET(con)){
		return ILLEGALFUNCTION;
	}
	
	res = print_devices_json_val(con->response);

	return res;
}

int cgi_link_two_devices(void *sever, s_connection_t *con)
{
	int res = 0; 
	s_returnStatus_t rts;
	
	if(!IS_FUNC_SET(con)){
		return ILLEGALFUNCTION;
	}

	memset(&rts,0, sizeof(rts));

	strncpy(rts.message, "Success", strlen("Success"));
	rts.status_code = SUCCESS;
	res = responce_json(con->response, &rts);

	return res;	
}

s_cgi_protocol_t pro_devices_list[] = {
	{"list", cgi_get_all_devices_stat},
	{"linkage", cgi_link_two_devices},
	{NULL, NULL}
};

