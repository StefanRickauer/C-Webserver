#include <arpa/inet.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>


#define BACKLOG 500		// max. number of pending connections
#define PORT 10000
#define BUF_SIZE 100

// Connect to server using netcat: nc 127.0.0.1 10000

int main(int argc, char **argv)
{

	// Add command line parser so user can define custom port number

	int socketFd, clientFd=-1;
	int status, n;
	struct sockaddr_in6 serv_addr, cli_addr;
	socklen_t addr_len;
	char cli_addr_str[INET6_ADDRSTRLEN];
	char req[BUF_SIZE], res[BUF_SIZE];

	// create
	socketFd = socket(AF_INET6, SOCK_STREAM, 0);
	
	if(socketFd == -1)
	{
		// Handle socket error and terminate
	}

	memset(&serv_addr, 0, sizeof(struct sockaddr_in6));
	serv_addr.sin6_family = AF_INET6;
	serv_addr.sin6_addr = in6addr_any;
       	serv_addr.sin6_port = htons(PORT);	

	// bind
	status = bind(socketFd, (struct sockaddr*) &serv_addr, sizeof(struct sockaddr_in6));
	if(status == -1)
	{
		// Handle bind error, close socket and terminate
		close(socketFd);
	}

	// listen 
	status = listen(socketFd, BACKLOG);
	if(status == -1)
	{
		// Handle listen error, close socket and terminate
		close(socketFd);
	}

	// accept
	while(1)
	{
		addr_len = sizeof(struct sockaddr_in6);
		clientFd = accept(socketFd, (struct sockaddr*) &cli_addr, &addr_len);

		if(clientFd == -1)
		{
			// Handle accept error, close socket and terminate
			close(socketFd);
		}

		if(inet_ntop(AF_INET6, &cli_addr.sin6_addr, cli_addr_str
					, INET6_ADDRSTRLEN) == NULL)
		{
			// Could not convert client address to string
			// terminate
			close(socketFd);
		} 
		printf("Accepted new connection from: %s:%d ... \n", 
				cli_addr_str, ntohs(cli_addr.sin6_port));
			
		memset(req, '\0', BUF_SIZE);	
		
		while((n = read(clientFd, req, BUF_SIZE-1)) > 0)
		{
			
			fprintf(stdout, "Received: %s\n", req);
			
			if(req[n-1] == '\n')
			{
				break;
			}
			
		}
		if(n < 0)
			return -1;
			
                if(status == -1)
       		{
                	// handle error
             		close(clientFd);
             		continue;
      		}

		memset(res, '\0', BUF_SIZE);

		snprintf(res, BUF_SIZE, "HTTP/1.0 200 0K");
		write(clientFd, res, BUF_SIZE);
		close(clientFd);
        	printf("Connection closed.\n");

			
	}

	return 0;
}
