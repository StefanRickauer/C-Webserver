#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "boolean.h"
#include "http_response.h"
#include "server_logic.h"

// return codes: -1 fail, 1 success
int handle_client(int client, bool verbose) 
{
	char *body = "<h1>Hello World!</h1>";

	char request[BUF_SIZE], response[BUF_SIZE], header[BUF_SIZE], status_line[BUF_SIZE], header_fields[BUF_SIZE];
	int bytes_read;	
		
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
	
	memset(response, '\0', BUF_SIZE);
	
	get_status_line(PROTOCOL, "200 OK", status_line);
	get_header_fields(header_fields);
	
	strcpy(header, status_line);
	strcat(header, header_fields);

	strncpy(response, header, strlen(header));
	strncat(response, body, strlen(body));
	
	write(client, response, BUF_SIZE);
      	
	return 1;
}
