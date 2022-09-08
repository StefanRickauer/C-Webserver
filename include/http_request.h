#ifndef _HTTP_REQUEST_H
#define _HTTP_REQUEST_H

int extract_req_params(char *, char *, char *, char *);
int check_version_support(char *, char *);
int check_method_support(char *);

#endif
