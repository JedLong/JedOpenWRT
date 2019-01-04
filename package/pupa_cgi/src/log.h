#ifndef _LOG_H  
#define _LOG_H  
  
#include <stdarg.h>  
#include <syslog.h>  
  
#define MAX_LOG_LEN 1024  
#define LOG_FILE "/var/pupacgi.log"

enum _log_level{
	JED_LOG_EMERG,
	JED_LOG_ALERT,
	JED_LOG_CRIT,
	JED_LOG_ERR,
	JED_LOG_WARNING,
	JED_LOG_NOTICE,
	JED_LOG_INFO,
	JED_LOG_DEBU
};

void log_message(const int level, const char *fmt, ...);

/* 添加了打印语句所在的文件、行号、函数信息 */  
#define JED_LOG(level, fmt, argc...) log_message(level, "[%s, %s(): %d]" fmt, __FILE__, __FUNCTION__,  __LINE__, ##argc)   

//#define DEBUG_X86

#ifdef DEBUG_X86
	#define JED_DEBUG(fmt, argc...) printf("[%s():%d]" fmt "\n", __func__, __LINE__, ##argc)
	#define JED_ERROR(fmt, argc...) printf("[%s():%d]" fmt "\n", __func__, __LINE__, ##argc)
#else
	#define JED_DEBUG(fmt, argc...) JED_LOG(JED_LOG_DEBU,fmt, ##argc)
	#define JED_ERROR(fmt, argc...) JED_LOG(JED_LOG_ERR,fmt, ##argc)
#endif

/*
#define WRITE_LOG(FORMAT, ...){                     \  
    do{                             \  
        FILE* fp    = fopen(LOG_FILE, "a");         \  
        struct tm* pt;                      \  
        time_t time_now;                    \  
        struct timeval tv;                  \  
        gettimeofday(&tv, NULL);                \  
        time(&time_now);                    \  
        pt  = localtime(&(tv.tv_sec));          \  
        fprintf(fp, "%04d-%02d-%02d %02d:%02d:%02d.%03u "FORMAT"\n", \  
            pt->tm_year+1900,                \  
            pt->tm_mon+1,                    \  
            pt->tm_mday,                 \  
            pt->tm_hour,                 \  
            pt->tm_min,                  \  
            pt->tm_sec,                  \  
            (u32)(tv.tv_usec)/1000,             \  
            ##__VA_ARGS__);                 \  
        fclose(fp);                     \  
    }while(0);                          \  
} 
#endif
*/

#endif 

