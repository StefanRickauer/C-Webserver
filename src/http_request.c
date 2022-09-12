#include <errno.h>
#include <libgen.h>
#include <limits.h>
#include <string.h>
#include <unistd.h>

#include "error_handler.h"
#include "http_status_codes.h"
#include "http_request.h"
#include "mcval.h"

int process_url(char *full_url, char *path, char *params)
{
	
	char copy[BUF_SIZE];
	char *url_path, *url_params;

	strcpy(copy, full_url);

	url_path = strtok(copy, "?");
	
	if(url_path == NULL)
	{
		notify(errno);
		return INTERNAL_ERROR;
	}

	url_params = strtok(NULL, "\0");

	if(url_params == NULL)			// no parameters submitted (found)
	{
		strcpy(path, url_path);
		return SUCCESS;
	}

	strcpy(path, url_path);
	strcpy(params, url_params);
	return SUCCESS;
}

int extract_req_params(char *request, char *method, char *path, char *params, char *version, char *webroot)
{

	char temp[BUF_SIZE], cwd[PATH_MAX], url_path[BUF_SIZE], url_params[BUF_SIZE], copy_sub_string[BUF_SIZE];
	char *sub_string;
	int status;

	strcpy(temp, request);
	
	sub_string = strtok(temp, " ");
	
	if(sub_string == NULL)
		return BAD_REQUEST;
	
	strcpy(method, sub_string);

	sub_string = strtok(NULL, " ");

	if(sub_string == NULL)
		return BAD_REQUEST;

	strcpy(copy_sub_string, sub_string);
	
	if(strcmp(copy_sub_string, "/") == 0)			// default page requested
	{
		strcpy(copy_sub_string, DEFAULT_PAGE);		// defined in mcval.h
	}
						
	sub_string = strtok(NULL, "\n");
	
	if(sub_string == NULL)
		return BAD_REQUEST; 	

	strcpy(version, sub_string);

	if( (strncmp(method, "GET", strlen("GET")) == 0) ||
	    (strncmp(method, "HEAD", strlen("HEAD")) == 0))
	{
		status = process_url(copy_sub_string, url_path, url_params);
		
		if(status != SUCCESS)
			return status;

		if(webroot[0] == '\0')
		{
			if(getcwd(cwd, sizeof(cwd)) == NULL)
			{
				notify(errno);
				return INTERNAL_ERROR;
			}

			strcpy(path, cwd);

			strcat(path, url_path);
			
			strcpy(params, url_params);
		}

		else 
		{
			strcpy(path, webroot);

			strcat(path, url_path);

			strcpy(params, url_params);
		}
	}
	
	else 
	{
		return NOT_IMPLEMENTED;
	}

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
		return SUCCESS;
	
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

int chop_reqested_location(char *full_path, char *directory, char *filename)
{
	char cwd[PATH_MAX];
	char *dir, *base, *cpy;
	int status;

	cpy = strdup(full_path);

	if(getcwd(cwd, PATH_MAX) == NULL)
	{
		notify(errno);
                return INTERNAL_ERROR;
	}

	if(chdir(full_path) == -1)
	{
		if(errno == ENOTDIR)			// Full path contains file!
		{
			dir = dirname(full_path);	// Get directory
			base = basename(cpy);		// Get file
		}

		else 
		{
			notify(errno);
                	status = errno_to_status(errno);
                	return status;
		}
	}

	if(chdir(cwd) == -1)
        {
                notify(errno);
                status = errno_to_status(errno);
                return status;
        }

	strcpy(directory, dir);
	strcpy(filename, base);

	return SUCCESS;
}
