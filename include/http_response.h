#ifndef _HTTP_RESPONSE
#define _HTTP_RESPONSE

void create_status_line(char *, int, char *);
void create_header_fields(char *, int);
void create_header(char *, int, char *, int);
void send_header_only(int , char *, int , char *, char *);

#endif
