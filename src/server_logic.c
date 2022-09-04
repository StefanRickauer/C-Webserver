#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "boolean.h"
#include "http_response.h"
#include "http_request.h"
#include "mcval.h"
#include "server_logic.h"

// return codes: -1 fail, 1 success
int handle_client(int client, bool verbose) 
{
	char *body = "<h1>Hello World!</h1>";

	char request[BUF_SIZE], req_method[BUF_SIZE], req_location[BUF_SIZE], req_proto[BUF_SIZE]; 
	char response[BUF_SIZE], header[BUF_SIZE], status_line[BUF_SIZE], header_fields[BUF_SIZE];
	int bytes_read, status;	
		
	memset(request, '\0', BUF_SIZE);	
		
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
		return -1;
	
	// Process request here
	status = extract_req_params(request, req_method, req_location, req_proto);
	
	if(status == 0)		// everything is fine
	{
		printf("[TEST] Method: %s\tLocation: %s\tProtocol: %s\n", req_method, req_location, req_proto);
	}

	// <===================== Proceed here check method (get, post, head etc.) load html file

	memset(response, '\0', BUF_SIZE);
	
	create_status_line(PROTOCOL, "200 OK", status_line);
	create_header_fields(header_fields);
	
	strcpy(header, status_line);
	strcat(header, header_fields);

	strncpy(response, header, strlen(header));
	strncat(response, body, strlen(body));
	
	write(client, response, BUF_SIZE);
      	
	return 1;
}
