#include "cgi_displays.h"
#include "opt.h"

s_displays_t gDisplay = { 
	.optdevice_info = {
		.device_info = {24,"displayer","on","connected"},
		.sta_number = "1234",
		.gateway_sta ="123456",
		.linked = {
			.count_devices = 2, 
			.devices[0] = {23,PRO_SUPPORT_TEMP_SENSOR, "on", "connected" },
			.devices[1] = {25,PRO_SUPPORT_MOTOR_FAN, "on", "connected" }
		}
	},
	.content = 2456
};
		
s_displays_t *pDisplay = &gDisplay;

int  print_device_displayer_val(cJSON* response,s_displays_t *dsp)
{
	int i = 0;
	cJSON *devicesObj = response;
	
	cJSON_AddNumberToObject(devicesObj, "device_id", dsp->optdevice_info.device_info.id);
	cJSON_AddStringToObject(devicesObj, "device_type", dsp->optdevice_info.device_info.device_type); 
	cJSON_AddStringToObject(devicesObj, "power_status", dsp->optdevice_info.device_info.power_status);
	cJSON_AddStringToObject(devicesObj, "usb_module_status", dsp->optdevice_info.device_info.usb_module_status);

	cJSON_AddStringToObject(devicesObj, "sta_number", dsp->optdevice_info.sta_number);
	cJSON_AddStringToObject(devicesObj, "gateway_sta", dsp->optdevice_info.gateway_sta);

	cJSON *linkedDeviceArray = cJSON_CreateArray();
	cJSON *device = NULL;
	for( i = 0; i < dsp->optdevice_info.linked.count_devices; i ++){
		//JED_DEBUG("linked.devices[%d].id: %d.", i, tts->optdevice_info.linked.devices[i].id);
		device 	= cJSON_CreateObject();
		cJSON_AddNumberToObject(device, "device_id",  dsp->optdevice_info.linked.devices[i].id);
		cJSON_AddItemToArray(linkedDeviceArray, device);	
	}
	
	cJSON_AddItemToObject(devicesObj, "linked_devices",linkedDeviceArray);
//	char *buf = json_object_to_buf(devicesObj);
    cJSON_AddNumberToObject(devicesObj, "content", dsp->content);
	
	return 0;
}

int cgi_get_device_displays(void *sever, s_connection_t *con)
{
	int res = 0; 
	
	if(!IS_FUNC_GET(con)){
		return ILLEGALFUNCTION;
	}
	
	res = print_device_displayer_val(con->response, pDisplay);

	return res;
}

int cgi_set_device_displays_contect(void *sever, s_connection_t *con)
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

s_cgi_protocol_t pro_device_displays[] = {
	{"allinfo", cgi_get_device_displays},
	{"display", cgi_set_device_displays_contect},
	{NULL, NULL}
};

