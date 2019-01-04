#include "common.h"

char *device_type[] ={
	"temp_sensor",
	"display",
	"motor_fan"
};

char *device_power_status[] = {
	"on",
	"off"
};

char *usb_module_status[] = {
	"connected",
	"isconnected"
};

void buffer_init(buffer_t *buf){
	buf->ptr = NULL;
	buf->size = 0;
	buf->used = 0;
}

int buffer_prepare(buffer_t *req,int size)
{
	if (req->used > BUFFER_PR_SIZE_MAX*3) {
		JED_DEBUG("used is to long,req->used = %d",req->used);
		return -1;
	}
	if (req->size == 0) {
		req->ptr = malloc(size);
		if (req->ptr == NULL) {
			JED_ERROR("malloc error,req->ptr = NULL");
			return -1;
		}
		req->used = 0;
		req->size = size;
	} else if(req->size - req->used < size) {
		req->size += size;
		req->ptr = realloc(req->ptr,req->size);
		if (req->ptr == NULL) {
			JED_ERROR("req->ptr = NULL");
			return -1;
		}
	}
	return 0;
}

void buffer_free(buffer_t *buf){
	if(buf){
		buf->size = 0;
		buf->used = 0;
		free(buf->ptr);
		buf->ptr = NULL;
	}
}
#if 0
int exec_cmd(const char * fmt,...)
{
	int pid;
	int flag = 0;
	int wpid = 0;
	int waittime = 0;
	int timeout = 600;
	int statbuf;
	char tmp[1024] = {0};
	char cmdbuf[1024] = {0,};
	
	va_list ap;
	va_start(ap, fmt);
	vsprintf(cmdbuf, fmt, ap);
	va_end(ap);
#endif
void buffer_add(buffer_t * buf,const char * fmt,...){
	int len;
	if(!buf || !fmt){
		return;
	}
	//printf("buffer_add\n");
	char cmdbuf[10240];
	va_list ap;
	va_start(ap, fmt);
	vsprintf(cmdbuf, fmt, ap);
	va_end(ap);
	len = strlen(cmdbuf);
	//printf("buf->used=%d\n",buf->used);
	//printf("buffer_add cmdbuf=%s\n",cmdbuf);
	if(!buffer_prepare(buf,len+1)){
	    strcpy(&buf->ptr[buf->used],cmdbuf);
	    buf->used += len;
    }
	//printf("buf->used=%d\n",buf->used);
}

char * json_object_to_buf(cJSON *jsonObj)
{
	char *buf = NULL;

	buf = cJSON_Print(jsonObj);
	//buf = cJSON_PrintUnformatted(jsonObj);
	
	return buf;
}





