#include <string.h>

#include "file_utils.h"
#include "http_status_codes.h"
#include "mcval.h"

int is_subdirectory(char *directory, char *sub_directory)
{
	if(strncmp(directory, sub_directory, strlen(directory)) == 0)
		return SUCCESS;
	
	return BAD_REQUEST;
}
