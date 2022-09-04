#include <string.h>
#include "http_request.h"
#include "mcval.h"

#include <stdio.h>

// return 0 on success, 1 failure getting method, 2 failure getting target, 3 failure getting version
int extract_req_params(char *request, char *method, char *target, char *version)
{

	char temp[BUF_SIZE];
	char *sub_string;

	strcpy(temp, request);
	
	sub_string = strtok(temp, " ");
	
	if(sub_string == NULL)
	{
		printf("TEST 1\n");
		return 1;
	}
	
	strcpy(method, sub_string);

	sub_string = strtok(NULL, " ");

	if(sub_string == NULL)
	{
		printf("TEST 2\n");
		return 2;
	} 	
	strcpy(target, sub_string);

	sub_string = strtok(NULL, "\n");

	if(sub_string == NULL)
	{
		printf("TEST 3\n");
		return 3;
	} 	

	strcpy(version, sub_string);

	return 0;
}
