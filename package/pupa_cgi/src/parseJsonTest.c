#include <stdio.h>
#include <stdlib.h>

#include "cJSON.H"
#include "common.h"

int main(int argc, const char * argv [ ])
{
	char *data = "{\"love\":[\"LOL\",\"Go shopping\"]}";

	cJSON * json = cJSON_Parse(data);
	char *json_data = cJSON_Print(json);
	
	printf("data: %s\n", json_data);
	
	SAFETYFREE(json_data);
	cJSON_Delete(json);

	return 0;
}
