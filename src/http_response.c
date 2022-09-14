#include <string.h>
#include <unistd.h>

#include "gmt_date.h"
#include "http_response.h"
#include "http_status_codes.h"
#include "mcval.h"

void create_status_line(char *protocol, int status_code, char *msg)
{
	char status[BUF_SIZE];
	get_status_message(status_code, status);

	strcpy(msg, protocol);
	strcat(msg, " ");
	strcat(msg, status);
	strcat(msg, "\n");
}

void create_header_fields(char *data)
{
	char date[TOTAL_DATE_LEN]; 
	get_gmt_date_string(date);
	char s_name[] = "Server: webserv\n";
	char rel_loc[] = "Location: /\n";
	char conn[] = "Connection: close\n";
	char content_len[] = "Content-Length: 21\n";	// str-len body (if number is less than actual str it will be cut off)
	char content_type[] = "Content-Type: text/html; charset=iso-8859-1\n\n";

	strcpy(data, date);
	strcat(data, s_name);
	strcat(data, rel_loc);
	strcat(data, conn);
	strcat(data, content_len);
	strcat(data, content_type);
}

void create_header(char *protocol, int status_code, char *header)
{
	char content[BUF_SIZE], status_line[BUF_SIZE], header_fields[BUF_SIZE];

	create_status_line(protocol, status_code, status_line);
	create_header_fields(header_fields);

	strcpy(content, status_line);
	strcat(content, header_fields);

	strcpy(header, content);
}	

void send_header_only(int client, char *protocol, int status_code, char *header, char *response)
{
	create_header(protocol, status_code, header);
        strncpy(response, header, strlen(header));

        write(client, response, BUF_SIZE);
}
