#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "boolean.h"
#include "server_logic.h"

// return codes: -1 fail, 1 success
int handle_client(int client, bool verbose) 
{
	char *test_msg = "HTTP/1.1 200 OK\nDate: Thu, 01 Sep 2022 16:54:46 GMT\nServer: webserv\nLocation: /\n"
		 "Connection: close\nContent-Length: 21\nContent-Type: text/html; charset=iso-8859-1\n\n<h1>Hello World!</h1>";

	char request[BUF_SIZE], response[BUF_SIZE];
	int bytes_read;	
		
	memset(request, '\0', BUF_SIZE);	
		
	while((bytes_read = read(client, request, BUF_SIZE-1)) > 0)
	{
		if(verbose)	
			fprintf(stdout, "Received: %s\n", request);
			
		if(request[bytes_read - 1] == '\n')
		{
			break;
		}
			
	}
	if(bytes_read < 0)
		return -1;
	
	memset(response, '\0', BUF_SIZE);

	 
	//sleep(10);	<= successfully tested parallel processing
	
	//snprintf(response, BUF_SIZE, "HTTP/1.1 200 OK");
	
	strncpy(response, test_msg, strlen(test_msg));
	write(client, response, BUF_SIZE);
      	
	return 1;
}
