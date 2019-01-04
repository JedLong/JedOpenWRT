#include "cgi_motor_fan.h"
//#include "opt.h"

s_motorFan_t gMotorFan = { 
	.optdevice_info = {
		.device_info = {25,"motor_fan","on","connected"},
		.sta_number = "1234",
		.gateway_sta ="123456",
		.linked = {
			.count_devices = 2, 
			.devices[0] = {24,PRO_SUPPORT_DISPLAYS, "on", "connected" },
			.devices[1] = {23,PRO_SUPPORT_TEMP_SENSOR, "on", "connected" }
		}
	},
	.state = "off"  //[off, low, high, unknown]
};
		
s_motorFan_t *pMotorFan = &gMotorFan;

int  print_device_motor_fan_val(cJSON* response,s_motorFan_t *mtf)
{
	int i = 0;
	cJSON *devicesObj = response;
	
	cJSON_AddNumberToObject(devicesObj, "device_id", mtf->optdevice_info.device_info.id);
	cJSON_AddStringToObject(devicesObj, "device_type", mtf->optdevice_info.device_info.device_type); 
	cJSON_AddStringToObject(devicesObj, "power_status", mtf->optdevice_info.device_info.power_status);
	cJSON_AddStringToObject(devicesObj, "usb_module_status", mtf->optdevice_info.device_info.usb_module_status);

	cJSON_AddStringToObject(devicesObj, "sta_number", mtf->optdevice_info.sta_number);
	cJSON_AddStringToObject(devicesObj, "gateway_sta", mtf->optdevice_info.gateway_sta);

	cJSON *linkedDeviceArray = cJSON_CreateArray();
	cJSON *device = NULL;
	for(i = 0; i < mtf->optdevice_info.linked.count_devices; i ++){
		//JED_DEBUG("linked.devices[%d].id: %d.", i, tts->optdevice_info.linked.devices[i].id);
		device 	= cJSON_CreateObject();
		cJSON_AddNumberToObject(device, "device_id",  mtf->optdevice_info.linked.devices[i].id);
		cJSON_AddItemToArray(linkedDeviceArray, device);	
	}
	
	cJSON_AddItemToObject(devicesObj, "linked_devices",linkedDeviceArray);
//	char *buf = json_object_to_buf(devicesObj);
    cJSON_AddStringToObject(devicesObj, "state", mtf->state);
	
	return 0;
}


int cgi_get_device_motor_fan(void *sever, s_connection_t *con)
{
	int res = 0; 

	if(!IS_FUNC_GET(con)){
		return ILLEGALFUNCTION;
	}
	
	res = print_device_motor_fan_val(con->response, pMotorFan);

	return res;
}

int cgi_set_device_motor_fan_state(void *sever, s_connection_t *con)
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

s_cgi_protocol_t pro_device_motor_fan[] = {
	{"allinfo", cgi_get_device_motor_fan},
	{"state", cgi_set_device_motor_fan_state},
	{NULL, NULL}
};

