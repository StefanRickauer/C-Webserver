#include <string.h>

#include "boolean.h"
#include "file_utils.h"

bool is_subdirectory(char *directory, char *sub_directory)
{
	if(strncmp(directory, sub_directory, strlen(directory)) == 0)
		return true;
	
	return false;
}
