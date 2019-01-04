
#ifndef __MAIN_HEAD__
#define __MAIN_HEAD__

#include "common.h"
#include "cJSON.h"

#define NC_ENV_COMMON          "NWC_"
#define NC_ENV_PRIVATE         "NWP_"
#define NC_ENV_IP              "ip"
#define NC_ENV_SOCK            "sock"
#define NC_ENV_HTTP_VER        "http_ver"
#define NC_ENV_HTTP_ENCODING   "http_encoding"
#define NC_ENV_FILE_NAME       "file_name"

#define NC_HTTP_HEAD_MAX   2048
#define NC_VER   "NW_CGI 1.0"

//#define env_key_value(name) \
//	get_env_value(NC_ENV_PRIVATE, name)

#define env_key_value(name) \
	get_env_value(NULL, name)
	
//#define env_com_value(name) \
//	get_env_value(NC_ENV_COMMON, name)

#define env_com_value(name) \
	get_env_value(NULL, name)
	
#define env_sys_value(name) \
	get_env_value(NULL, name)
	
extern char *get_env_value(char *prefix, char *name);

#endif