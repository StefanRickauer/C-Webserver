#include <limits.h>
#include <stdio.h>
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

int create_body(char *body, char *location, char *file)
{
	char path[PATH_MAX];
	strcpy(path, location);
	strcat(path, "/");
	strcat(path, file);

	FILE *requested_file = fopen(path, "r");

	while(!feof(requested_file))
	{
		int bytes_read = fread(body, sizeof(unsigned char), BUF_SIZE, requested_file);

		if(bytes_read < 1)
			return INTERNAL_ERROR;
	}

	return SUCCESS;
}
