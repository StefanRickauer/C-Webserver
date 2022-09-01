#include <arpa/inet.h>
#include <getopt.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/wait.h>

#define BACKLOG 500		// max. number of pending connections
#define PORT 10000
#define BUF_SIZE 400

/*
 * To Do:
 * 	Add function that creates header data
 * 	Add header-file that contains function mentioned above
 * 	Add status codes to header-file (status codes see: RFC-7231)
 * 	Process requests 
 * 	Handle errors
 * 	Add log function?
 *
 * Test the server:
 * 	nc localhost <port>
 * 	localhost:<port> (Browser)
 *
 * Header examples:
 * 	curl -I <url>
*/


static const struct option long_options[] = 
{
	{ "port",	required_argument, 	0, 'p' },
	{ "help", 	no_argument,		0, 'h' },
	{ 0, 0, 0, 0 }
};

char *help_msg = "Usage: ./webserv [ -p port_number ]\n"
	     "\t\tCommand summary:\n"
	     "\t\t\t-h\t\tShow this text\n"
	     "\t\t\t-p port\t\tSpecify port number for remote connections\n"
	     "\n\t\tCommand summary (long):\n"
	     "\t\t\t--help\t\tShow this text\n"
	     "\t\t\t--port port\tSpecify port number for remote connections\n";

// When sending only html-code like: <h1>Test</h1> the browser does not render the code.
// Adding a header solves the problem. *test_msg got renderd correctly!

char *test_msg = "HTTP/1.1 200 OK\nDate: Thu, 01 Sep 2022 16:54:46 GMT\nServer: webserv\nLocation: /\n"
		 "Connection: close\nContent-Type: text/html; charset=iso-8859-1\n\n<h1>Hello World!</h1>";

int handle_client(int client);

int main(int argc, char **argv)
{
	int port = -1;	// to check if user specified port, if not port == -1
	
	while(1)
	{
		int option_index = 0;
		int c = getopt_long(argc, argv, "p:h", long_options, &option_index);

		if(c == -1)
			break;

		switch(c) 
		{
			case 'p':
				port = strtol(optarg, NULL, 10);
				// possible errors: EINVAL ERANGE (see: man strtol)
				// valid port number range: 0 - 65536 (add check)
				// handle errors
				break;
			case 'h':
				printf("%s", help_msg);
				exit(EXIT_SUCCESS);
				break;
			case '?':
				if(optopt == 'p')	fprintf(stderr, "-p: Missing argument.\n"); 
				break;
		}
	}
	
	int serverFd, clientFd;
	int status;
	struct sockaddr_in6 serv_addr, cli_addr;
	socklen_t addr_len;
	char cli_addr_str[INET6_ADDRSTRLEN];
	pid_t pid;

	
	serverFd = socket(AF_INET6, SOCK_STREAM, 0);
	
	if(serverFd == -1)
	{
		// Handle socket error and terminate
	}

	memset(&serv_addr, 0, sizeof(struct sockaddr_in6));
	serv_addr.sin6_family = AF_INET6;
	serv_addr.sin6_addr = in6addr_any;
       	serv_addr.sin6_port = htons( (port == -1) ? PORT : port);	

	status = bind(serverFd, (struct sockaddr*) &serv_addr, sizeof(struct sockaddr_in6));
	if(status == -1)
	{
		// Handle bind error, close socket and terminate
		close(serverFd);
	}
 
	status = listen(serverFd, BACKLOG);
	if(status == -1)
	{
		// Handle listen error, close socket and terminate
		close(serverFd);
	}

	printf("Server started on port: %d\n", (port == -1) ? PORT : port);
	
	while(1)
	{
		addr_len = sizeof(struct sockaddr_in6);
		clientFd = accept(serverFd, (struct sockaddr*) &cli_addr, &addr_len);

		if(clientFd == -1)
		{
			// Handle accept error, close socket and terminate
			close(serverFd);
		}

		if(inet_ntop(AF_INET6, &cli_addr.sin6_addr, cli_addr_str,
					INET6_ADDRSTRLEN) == NULL)
		{
			// Could not convert client address to string
			printf("Accepted new connection.\n");
		} else {
		
			printf("Accepted new connection from: %s:%d\n", 
					cli_addr_str, ntohs(cli_addr.sin6_port));
		}
			
		pid = fork();
		if(pid == -1) 
		{
			// Add err msg
			exit(EXIT_FAILURE);
		}
		
		else if (pid == 0) 
		{
			close(serverFd);
			handle_client(clientFd);
			close(clientFd);
			printf("Connection closed.\n");
			return 0;
		}

		else 
		{
			close(clientFd);
		}	
	}

	exit(EXIT_SUCCESS);
}


// return codes: -1 fail, 1 success
int handle_client(int client) 
{
	char request[BUF_SIZE], response[BUF_SIZE];
	int bytes_read;	
		
	memset(request, '\0', BUF_SIZE);	
		
	while((bytes_read = read(client, request, BUF_SIZE-1)) > 0)
	{
			
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
