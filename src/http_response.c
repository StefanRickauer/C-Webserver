#include <stdio.h>
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

void create_header_fields(char *data, int length)
{
	char date[TOTAL_DATE_LEN]; 
	get_gmt_date_string(date);
	char s_name[] = "Server: webserv\n";
	char rel_loc[] = "Location: /\n";
	char conn[] = "Connection: close\n";
	char content_len[] = "Content-Length: ";	// str-len body (if number is less than actual str it will be cut off)
	char string_len[BUF_SIZE];
	char content_type[] = "Content-Type: text/html; charset=iso-8859-1\n\n";

	strcpy(data, date);
	strcat(data, s_name);
	strcat(data, rel_loc);
	strcat(data, conn);
	
	if(length > 0)
	{
		sprintf(string_len, "%d", length);	// convert int to string

		strcat(data, content_len);
		strcat(data, string_len);
		strcat(data, "\n");
	}

	strcat(data, content_type);
}

void create_header(char *protocol, int status_code, char *header, int content_length)
{
	char content[BUF_SIZE], status_line[BUF_SIZE], header_fields[BUF_SIZE];

	create_status_line(protocol, status_code, status_line);
	create_header_fields(header_fields, content_length);

	strcpy(content, status_line);
	strcat(content, header_fields);

	strcpy(header, content);
}	

void send_header_only(int client, char *protocol, int status_code, char *header, char *response)
{
	create_header(protocol, status_code, header, HEADER_ONLY);
        strncpy(response, header, strlen(header));

        write(client, response, BUF_SIZE);
}
