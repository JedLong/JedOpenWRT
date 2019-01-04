
#ifndef __COMMON_HEAD__
#define __COMMON_HEAD__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "log.h"
#include "cJSON.h"

/*Status Code.*/
#define SUCCESS 				200
#define BADREQUEST				400
#define UNAUTHORIZED			401
#define	FORBIDDEN				403
#define NOTFOUND				404
#define INTERNALSERVERERROR		500
#define ILLEGALFUNCTION			600

/*Error Code*/
/*base errno -18000*/
#define PRO_BASE_ARG_ERR			-18000
#define PRO_BASE_MALLOC_ERR			-18001
#define PRO_BASE_IDENTITY_ERR		-18002
#define PRO_BASE_UPFILE_ERR     	-18003
#define PRO_BASE_NOTFOUND			-18004
#define PRO_BASE_NOTROOT			-18005
#define PRO_BASE_NOTSUPPORT			-18006
#define PRO_BASE_SYSTEM_ERR			-18007

#define STRING_LEN 			(50)
#define MAX_LINKED_NUM		(100)

#define SAFETYFREE(m) do{ \
	if (m != NULL){ \
		free(m); \
		m = NULL; \
	} \
}while(0)

#ifndef MIXSTR
#define MIXSTR(a,b)  ( a > b ? b : a )
#endif

typedef struct _returnStatus{
	char message[STRING_LEN];
	int status_code;
}s_returnStatus_t;

typedef s_returnStatus_t s_returnSuccess_t;  

typedef struct _returnFailed{
	s_returnStatus_t rstatus;
	int cause_code;
}s_returnFailed_t;

/*
typedef enum _deviceType{
	temp_sensor, 
	display, 
	motor_fan
}e_deviceType_t;

typedef struct _stringDeviceType{
	e_deviceType_t ti;
	char *string_type;
}s_stringDeviceType_t;
extern char *device_type[];

typedef enum _powerStatus{
	on, 
	off
}e_powerStatus_t;
	
extern char *device_power_status[];

typedef enum _usbModuleStatus{
	connected,
	disconnected
}e_usbModuleStatus_t;

extern char *usb_module_status[];
*/

typedef struct _deviceInfo{
	int id;							 //23
	char device_type[STRING_LEN];      //deviceName
	char power_status[STRING_LEN];
	char usb_module_status[STRING_LEN];
}s_device_info_t;

typedef struct _linkedDevices{
	int count_devices;
	s_device_info_t devices[MAX_LINKED_NUM];
}s_linkedDvice_t;

typedef struct _optDeviceInfo{
	s_device_info_t device_info;
	char sta_number[STRING_LEN];         //
	char gateway_sta[STRING_LEN];
	s_linkedDvice_t linked;
}s_optDeviceInfo_t;


typedef enum _function{
	cget = 1,
	cset
}e_func_t;

typedef struct connection{
	e_func_t function;
	char state;    
	char *ip_from;
	cJSON* response; 
	int sock;
	char *request;
	char *encoding; // Accept-Encoding
	char *http_ver; // HTTP/1.1
	char *http_ctype; // default: application/json
	char *http_head;
	char *http_body;
	int http_head_len;
	int http_body_len;
}s_connection_t;

#define IS_FUNC_SET(cont) ( cont->function == cset)
#define IS_FUNC_GET(cont) ( cont->function == cget)

#define BUFFER_PR_SIZE 4096
#define BUFFER_PR_SIZE_MAX 8192

typedef struct buffer{
	char *ptr;
	int used;
	int size;
}buffer_t;
void buffer_init(buffer_t *buf);

int buffer_prepare(buffer_t *req,int size);
void buffer_free(buffer_t *buf);
void buffer_add(buffer_t * buf,const char * fmt,...);

char * json_object_to_buf(cJSON *jsonObj);

#endif

	
