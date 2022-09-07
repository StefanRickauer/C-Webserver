#include <string.h>
#include "http_status_codes.h"
#include "http_request.h"
#include "mcval.h"


int check_version_support(char *supported_protocol, char *requested_protocol)
{
	int result = strncmp(supported_protocol, requested_protocol, strlen(supported_protocol));

	if(result != 0) 
		return HTTP_VERS_N_SUP;

	return SUCCESS;
}

int extract_req_params(char *request, char *method, char *target, char *version)
{

	char temp[BUF_SIZE];
	char *sub_string;

	strcpy(temp, request);
	
	sub_string = strtok(temp, " ");
	
	if(sub_string == NULL)
		return BAD_REQUEST;
	
	strcpy(method, sub_string);

	sub_string = strtok(NULL, " ");

	if(sub_string == NULL)
		return BAD_REQUEST;

	strcpy(target, sub_string);

	sub_string = strtok(NULL, "\n");

	if(sub_string == NULL)
		return BAD_REQUEST; 	

	strcpy(version, sub_string);

	return SUCCESS;
}
