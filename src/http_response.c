#include "http_response.h"
#include "gmt_date.h"

/* All Error Codes
   ===============

Informal Responses

100 	Continue 	
101 	Switching Protocols 	
102 	Processing 	
103 	Early Hints 

Successful Responses	

200 	OK 	
201 	Created 	
202 	Accepted 	
203 	Non-Authoritative Information 	
204 	No Content 	
205 	Reset Content 	
206 	Partial Content 	
207 	Multi-Status 	
208 	Already Reported 		
226 	IM Used 	

Redirection Messages

300 	Multiple Choices 	
301 	Moved Permanently 	
302 	Found 	
303 	See Other 	
304 	Not Modified 	
305 	Use Proxy 		
307 	Temporary Redirect 	
308 	Permanent Redirect 	

Client Error Responses

400 	Bad Request 	
401 	Unauthorized 	
402 	Payment Required 	
403 	Forbidden 	
404 	Not Found 	
405 	Method Not Allowed 	
406 	Not Acceptable 	
407 	Proxy Authentication Required 	
408 	Request Timeout 	
409 	Conflict 	
410 	Gone 	
411 	Length Required 	
412 	Precondition Failed 	
413 	Content Too Large 	
414 	URI Too Long 	
415 	Unsupported Media Type 	
416 	Range Not Satisfiable 	
417 	Expectation Failed 	
421 	Misdirected Request 	
422 	Unprocessable Content 	
423 	Locked 	
424 	Failed Dependency 	
425 	Too Early 	
426 	Upgrade Required 	
427 	Unassigned 	
428 	Precondition Required 	
429 	Too Many Requests 	
430 	Unassigned 	
431 	Request Header Fields Too Large 		
451 	Unavailable For Legal Reasons 	

Server Error Responses

500 	Internal Server Error 	
501 	Not Implemented 	
502 	Bad Gateway 	
503 	Service Unavailable 	
504 	Gateway Timeout 	
505 	HTTP Version Not Supported 	
506 	Variant Also Negotiates 	
507 	Insufficient Storage 	
508 	Loop Detected 	


511 	Network Authentication Required 	
512-599 	Unassigned

*/


void get_status_line(char *protocol, char *status, char *msg)
{
	strcpy(msg, protocol);
	strcat(msg, " ");
	strcat(msg, status);
	strcat(msg, "\n");
}

void get_header_fields(char *data)
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
