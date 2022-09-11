#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "boolean.h"
#include "error_handler.h"
#include "http_response.h"
#include "http_request.h"
#include "http_status_codes.h"
#include "mcval.h"
#include "server_logic.h"


int handle_client(int client, char *webroot, bool verbose) // no user input => (webroot[0] == '\0')
{
	char *body = "<h1>Hello World!</h1>";

	char request[BUF_SIZE], req_method[BUF_SIZE], req_location[BUF_SIZE]; 
	char req_params[BUF_SIZE], req_proto[BUF_SIZE];
	char response[BUF_SIZE], header[BUF_SIZE];
	int bytes_read, status;	
		
	memset(request, '\0', BUF_SIZE);	
	memset(response, '\0', BUF_SIZE);

	while((bytes_read = read(client, request, BUF_SIZE-1)) > 0)
	{
		if(verbose)	
			fprintf(stdout, "Client request:\n%s\n", request);
			
		if(request[bytes_read - 1] == '\n')
		{
			break;
		}
			
	}
	
	if(bytes_read < 0)
	{
		notify(errno);
		
		create_header(PROTOCOL, BAD_REQUEST, header);	
		strncpy(response, header, strlen(header));

		write(client, response, BUF_SIZE);

		return FAILURE;
	}
	
	// Process request here
	status = extract_req_params(request, req_method, req_location, req_params, req_proto, webroot);
	
	if(status != SUCCESS)	// error detected
	{
		create_header(PROTOCOL, status, header);
		strncpy(response, header, strlen(header));

		write(client, response, BUF_SIZE);

		return FAILURE;
	}

	printf("[TEST] Method: %s\tLocation: %s\tProtocol: %s\n"
			"Parameters: %s\n", req_method, req_location, req_proto, (req_params == NULL) ? "" : req_params);
	
	
	// protocol supported?
	status = check_version_support(PROTOCOL, req_proto);

	if(status != SUCCESS)
	{
		create_header(PROTOCOL, status, header);
		strncpy(response, header, strlen(header));

		write(client, response, BUF_SIZE);
		
		return FAILURE;
	}

	// method supported?			
	status = check_method_support(req_method);

	if(status != SUCCESS)
	{
		create_header(PROTOCOL, status, header);
		strncpy(response, header, strlen(header));

		write(client, response, BUF_SIZE);

		return FAILURE;
	}

	// requested location => valid?  prevent directory traversal
	// 		      => readable?
	
	create_header(PROTOCOL, OK, header);
	
	strncpy(response, header, strlen(header));
	strncat(response, body, strlen(body));
	
	write(client, response, BUF_SIZE);
      	
	return SUCCESS;
}
