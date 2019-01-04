#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	//char *query_string = "cgif=devices&opt=info&function=get";
//	char *index = NULL, *index1 = NULL;
//	char *str = (char *)malloc((int)strlen(query_string)+1);
//	int strLen = (int)strlen(query_string);


	//memcpy(str, query_string, (int)strlen(query_string)+1);
	char endFlag = 0;
	char parm[10], val[30];
	char *str = "cgif=devices&opt=info&function=get";
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
			endFlag  = 1;
		}

		setenv(parm, val, 1);
		printf("%s\n", getenv(parm));

		if(endFlag){
			break;
		}
	}
	

	return 0;
}
