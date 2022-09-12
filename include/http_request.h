#ifndef _HTTP_REQUEST_H
#define _HTTP_REQUEST_H

int process_url(char *, char *, char *);
int extract_req_params(char *, char *, char *, char *, char *, char *);
int check_version_support(char *, char *);
int check_method_support(char *);
int chop_reqested_location(char *, char *, char *);

#endif
