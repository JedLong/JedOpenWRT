
#include "main.h"
#include "protocol.h"

char *get_env_value(char *prefix, char *name)
{
	char env[512];

	snprintf(env, sizeof(env), "%s%s",
		prefix ? prefix : "", name);
	return getenv(env);
}

static int create_head(s_connection_t *con)
{
	int len = 0;

	if (con->http_head)
		return 0;

	con->http_head = malloc(NC_HTTP_HEAD_MAX);
	if (!con->http_head) {
		JED_ERROR("Malloc head fail, %s\n", con->request);
		return -1;
	}
	
	len += snprintf(con->http_head + len,
		NC_HTTP_HEAD_MAX - len,
		"%s 200 OK\r\n"
		"Server: %s\r\n"
		"Connection: close\r\n"
		"Content-Type: %s; charset=utf-8\r\n",
		con->http_ver, NC_VER, con->http_ctype ? 
		con->http_ctype : "application/json");
	//if (con->gzip) {
	//	len += snprintf(con->http_head + len,
	//		NC_HTTP_HEAD_MAX - len,
	//		"Content-Encoding: gzip\r\n");
	//}
	
	if (con->http_body_len > 0) {
		len += snprintf(con->http_head + len,
			NC_HTTP_HEAD_MAX - len,
			"Content-Length: %d\r\n", con->http_body_len);
	}
	
	len += snprintf(con->http_head + len,
		NC_HTTP_HEAD_MAX - len,
		"\r\n");
	
	if (len >= NC_HTTP_HEAD_MAX) {
		JED_ERROR("http head too large\n");
		free(con->http_head);
		con->http_head = NULL;
		return -1;
	}
	
	con->http_head_len = len;
	return 0;
}

static int create_body(s_connection_t *con)
{
	int len;
	char *json, *ptr;

	if (con->http_body)
		return 0;

	json = cJSON_PrintUnformatted(con->response);
	if (!json)
		return -1;
	
	/*if (con->gzip) {
		ptr = malloc(8192*2);
		if (!ptr)
			return -1;
		len = deflate_file_to_buffer_gzip(ptr, 8192*2, json, strlen(json), 0);
		if (len < 0)
			return -1;
	} else {*/
		ptr = json;
		len = strlen(json);
	//}

	con->http_body = ptr;
	con->http_body_len = len;
	return 0;
}

static int send_reply(s_connection_t *con)
{
	if (write(con->sock, con->http_head,
			con->http_head_len) < 0) {
		JED_ERROR("send head fail, %s\n", con->request);
		return -1;
	}
	if (write(con->sock, con->http_body,
			con->http_body_len) < 0) {
		JED_ERROR("send body fail, %s\n", con->request);
		return -1;
	}
	return 0;
}

static void send_err(s_connection_t *con)
{
	char buf[2048];

	snprintf(buf, sizeof(buf), 
		"HTTP/1.1 200 OK\r\n"
		"Server: NC 1.0.0\r\n"
		"Connection: close\r\n"
		"Content-Type: application/json; charset=utf-8\r\n"
		"Content-Length: %d\r\n\r\n"
		"%s",
		(int)strlen("{\"error\": 1000}"), "{\"error\": 1000}");
	write(con->sock, buf,(int)strlen(buf));
}


int net_environment_process(s_connection_t *con)
{
	int res = 0;
	char *buf = NULL, *opt = NULL, *cgif = NULL, *function = NULL;

	s_cgi_protocol_t *cgi_fun = NULL;
	//cJSON *obj = NULL;
	
	memset(con, 0, sizeof(con));
	do{
		function = env_key_value("function");
		if(function == NULL){
			JED_ERROR("Run env_key_value(\"function\").");
			res = PRO_BASE_ARG_ERR; 
			break;
		}
		if (strcmp(function, "get") == 0) {
			con->function = cget;
		} else if (strcmp(function, "set") == 0) {
			con->function = cset;
		}
	
		cgif = env_key_value("cgif");
		if(cgif == NULL){
			JED_ERROR("Run env_key_value(\"cgif\").");
			res = PRO_BASE_ARG_ERR; 
			break;
	    }
		
		opt = env_key_value("opt");
		if(opt == NULL){
			JED_ERROR("Run env_key_value(\"opt\").");
			res = PRO_BASE_ARG_ERR; 
			break; 
	    }
			
		function = env_key_value("function");
		if (function == NULL) {
			JED_ERROR("Run env_key_value(\"function\").");
			res = PRO_BASE_ARG_ERR; 
			break;  
		}
		
		con->response = cJSON_CreateObject();
		cgi_fun = find_pro_handler(cgif, opt);
		if (cgi_fun == NULL) {
			JED_ERROR("Run find_pro_handler(), res = %d.", res);
			res = PRO_BASE_ARG_ERR; 
			break; 
		}

		JED_DEBUG("Going to hanle function.\n");
		res = cgi_fun->handler(NULL,con);
		if(res != 0){
			JED_ERROR("Run handler, res = %d.", res);
			break;
		}

		buf = json_object_to_buf(con->response);
		JED_DEBUG("buf: %s", buf);
		//printf("Will print buf data:");
		printf("%s",buf);  //Response json format data to web client.
	}while(0);
		
	if(res){
		cJSON_AddNumberToObject(con->response, "errno", res);
		cJSON_AddStringToObject(con->response, "opt", opt);
		cJSON_AddStringToObject(con->response, "cgif", cgif);
		buf = json_object_to_buf(con->response);
		printf("%s",buf);
	}
	
	cJSON_Delete(con->response);
	SAFETYFREE(buf);
	return res;
}

void url_parm_to_env(void)
{
	
	char endFlag = 0;
	char parm[10], val[30];
	char *str = getenv("QUERY_STRING") ;
	char *index = NULL, *index1 = NULL;
	int strLen = (int)strlen(str);

	index = str;
	while( NULL != (index1 = strchr( index, '=' ) )){
	   memset(parm, 0, 10); memset(val, 0, 30);
	   strncpy(parm, index == str ? index : index + 1, index1 - (index == str ? index : index + 1));

	   index = strchr(index1 + 1, '&');
	   if(index != NULL){
			   strncpy(val, index1 + 1, index - index1 - 1);
	   }else{
			   strncpy(val, index1 + 1, str + strLen - index1 - 1);
			   endFlag	= 1;
	   }

	   setenv( parm, val, 1 );
	   //printf("%s\n", getenv(parm));
	   if(endFlag){
			   break;
	   }
	}
}

int main(int argc, const char * argv [ ])
{
	char *requestString = NULL;
	int res = 0;
	s_connection_t con;

	requestString = getenv("REQUEST_METHOD");
	
	JED_DEBUG("method: %s.", requestString);
	JED_DEBUG("env data : %s.", getenv("QUERY_STRING") );
	
	url_parm_to_env();
	if(! strncmp(requestString, "GET", strlen("GET"))){
		res = net_environment_process(&con);
	}
	
	if (res){
		JED_ERROR("Error, res = %d.", res);
		return res;
	}
	
	//opt(print_devices_json_val);
	
	return 0;
}
