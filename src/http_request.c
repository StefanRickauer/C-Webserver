#include <string.h>
#include "http_status_codes.h"
#include "http_request.h"
#include "mcval.h"

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

int check_version_support(char *supported_protocol, char *requested_protocol)
{
	int result = strncmp(supported_protocol, requested_protocol, strlen(supported_protocol));

	if(result != 0) 
		return HTTP_VERS_N_SUP;

	return SUCCESS;
}

int check_method_support(char *method)
{
	if(strncmp(method, "HEAD", strlen(method)) == 0)
		return NOT_IMPLEMENTED;
	
	else if (strncmp(method, "GET", strlen(method)) == 0)
		return SUCCESS;
	
	else if (strncmp(method, "POST", strlen(method)) == 0)
		return NOT_IMPLEMENTED;
	
	else if (strncmp(method, "PUT", strlen(method)) == 0)
		return NOT_IMPLEMENTED;
	
	else if (strncmp(method, "DELETE", strlen(method)) == 0)
                return NOT_IMPLEMENTED;
	
	else if (strncmp(method, "CONNECT", strlen(method)) == 0)
                return NOT_IMPLEMENTED;
	
	else if (strncmp(method, "OPTIONS", strlen(method)) == 0)
                return NOT_IMPLEMENTED;
	
	else if (strncmp(method, "TRACE", strlen(method)) == 0)
                return NOT_IMPLEMENTED;
	
	else if (strncmp(method, "PATCH", strlen(method)) == 0)
                return NOT_IMPLEMENTED;

	else 
		return BAD_REQUEST;

	return SUCCESS;
}
