
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


int  print_devices_display_json_val(cJSON* response)
{

	cJSON *devicesObj = response;
	
	cJSON_AddNumberToObject(devicesObj, "device_id", 24);
	cJSON_AddStringToObject(devicesObj, "device_type", "disply");//"temp_sensor"
	cJSON_AddStringToObject(devicesObj, "power_status", "on");
	cJSON_AddStringToObject(devicesObj, "usb_module_status", "connected");

	cJSON_AddStringToObject(devicesObj, "sta_number", "1234");
	cJSON_AddStringToObject(devicesObj, "gateway_sta", "123456");


	cJSON *linkedDeviceArray = cJSON_CreateArray();
	cJSON *device = cJSON_CreateObject();
	cJSON_AddNumberToObject(device, "device_id", 23);
	cJSON_AddItemToArray(linkedDeviceArray, device);
	
	device = cJSON_CreateObject();
	cJSON_AddNumberToObject(device, "device_id", 25);
	cJSON_AddItemToArray(linkedDeviceArray, device);

	cJSON_AddItemToObject(devicesObj, "linked_devices",linkedDeviceArray);
//	char *buf = json_object_to_buf(devicesObj);

	return 0;
}


int  print_device_temp_sensor_json_val(cJSON* response)
{

	cJSON *devicesObj = response;
	
	cJSON_AddNumberToObject(devicesObj, "device_id", 23);
	cJSON_AddStringToObject(devicesObj, "device_type", "temp_sensor"); 
	cJSON_AddStringToObject(devicesObj, "power_status", "on");
	cJSON_AddStringToObject(devicesObj, "usb_module_status", "connected");

	cJSON_AddStringToObject(devicesObj, "sta_number", "1234");
	cJSON_AddStringToObject(devicesObj, "gateway_sta", "123456");


	cJSON *linkedDeviceArray = cJSON_CreateArray();
	cJSON *device = cJSON_CreateObject();
	cJSON_AddNumberToObject(device, "device_id", 24);
	cJSON_AddItemToArray(linkedDeviceArray, device);	
	
	cJSON_AddItemToObject(devicesObj, "linked_devices",linkedDeviceArray);
//	char *buf = json_object_to_buf(devicesObj);

	return 0;
}

int print_device_motor_fan_json_val(cJSON* response)
{

	cJSON *devicesObj = response;
	
	cJSON_AddNumberToObject(devicesObj, "device_id", 25);
	cJSON_AddStringToObject(devicesObj, "device_type", "motor_fan");
	cJSON_AddStringToObject(devicesObj, "power_status", "on");
	cJSON_AddStringToObject(devicesObj, "usb_module_status", "connected");

	cJSON_AddStringToObject(devicesObj, "sta_number", "1234");
	cJSON_AddStringToObject(devicesObj, "gateway_sta", "123456");


	cJSON *linkedDeviceArray = cJSON_CreateArray();
	cJSON *device = cJSON_CreateObject();
	cJSON_AddNumberToObject(device, "device_id", 24);
	cJSON_AddItemToArray(linkedDeviceArray, device);	
	
	cJSON_AddItemToObject(devicesObj, "linked_devices",linkedDeviceArray);
//	char *buf = json_object_to_buf(devicesObj);

	return 0;
}

/*
int opt(function *pcgi)
{
	char *method = NULL,*getFlag = "GET";
	char *data = NULL;
	int slen = 0;
	
	method = getenv("REQUEST_METHOD");
	data = getenv("QUERY_STRING");

	//JED_DEBUG("method: %s.", method);
	//JED_DEBUG("env data : %s.", data );
	
	if (method == NULL){
		JED_ERROR("getenv!");
		return -1;
	}

	slen = strlen(method);

	if (slen < strlen(getFlag)){
		JED_ERROR("getenv method length!");
		return -1;
	}
	
	if (strncmp(method, getFlag, strlen(getFlag)))	{
		JED_ERROR("Not the GET method!");
		return -1;	
	}
 
	printf("%s\r\n\r\n","Content-Type:text/html");
	data = pcgi();
	printf("%s\n", data);
	JED_DEBUG("Data: %s", data);

	SAFETYFREE(data);
	
	return 0;
}
*/

