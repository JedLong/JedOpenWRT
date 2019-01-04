#include "cgi_temp_sensor.h"
//#include "opt.h"

s_temperatureSensor_t tempSensor = { 
	.optdevice_info = {
		.device_info = {23,"temp_sensor","on","connected"},
		.sta_number = "1234",
		.gateway_sta ="123456",
		.linked = {
			.count_devices = 2, 
			.devices[0] = {24,PRO_SUPPORT_DISPLAYS, "on", "connected" },
			.devices[1] = {25,PRO_SUPPORT_MOTOR_FAN, "on", "connected" }
		}
	},
	.tempperature = 28,
	.units = "c"
};

s_temperatureSensor_t *pTempSensor = &tempSensor;

int  print_device_temp_sensor_val(cJSON* response,s_temperatureSensor_t *tts)
{
	int i = 0;
	cJSON *devicesObj = response;
	
	cJSON_AddNumberToObject(devicesObj, "device_id", tts->optdevice_info.device_info.id);
	cJSON_AddStringToObject(devicesObj, "device_type", tts->optdevice_info.device_info.device_type); 
	cJSON_AddStringToObject(devicesObj, "power_status", tts->optdevice_info.device_info.power_status);
	cJSON_AddStringToObject(devicesObj, "usb_module_status", tts->optdevice_info.device_info.usb_module_status);

	cJSON_AddStringToObject(devicesObj, "sta_number", tts->optdevice_info.sta_number);
	cJSON_AddStringToObject(devicesObj, "gateway_sta", tts->optdevice_info.gateway_sta);

	cJSON *linkedDeviceArray = cJSON_CreateArray();

	cJSON *device = NULL;
	for(i = 0; i < tts->optdevice_info.linked.count_devices; i ++){
		//JED_DEBUG("linked.devices[%d].id: %d.", i, tts->optdevice_info.linked.devices[i].id);
		device 	= cJSON_CreateObject();
		cJSON_AddNumberToObject(device, "device_id",  tts->optdevice_info.linked.devices[i].id);
		cJSON_AddItemToArray(linkedDeviceArray, device);	
	}
	
	cJSON_AddItemToObject(devicesObj, "linked_devices",linkedDeviceArray);
//	char *buf = json_object_to_buf(devicesObj);
    cJSON_AddNumberToObject(devicesObj, "tempperature", tts->tempperature);
	cJSON_AddStringToObject(devicesObj, "units", tts->units);
	
	return 0;
}


int cgi_get_temp_sensor_stat(void *sever, s_connection_t *con)
{
	int res = 0;

	if(!IS_FUNC_GET(con)){
		return ILLEGALFUNCTION;
	}
	
	res = print_device_temp_sensor_val(con->response, pTempSensor);

	return res;
}

int cgi_set_device_temp_sensor_temperature(void *sever, s_connection_t *con)
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

s_cgi_protocol_t pro_temp_sensor[] = {
	{"allinfo", cgi_get_temp_sensor_stat},
	{"temperature",cgi_set_device_temp_sensor_temperature},
	{NULL, NULL}
};

