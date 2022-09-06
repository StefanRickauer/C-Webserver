#include <stdio.h>
#include <stdlib.h>
#include "sys_err.c.inc"
#include "error_handler.h"

void notify(int err)
{
	fprintf(stderr, "[ ERROR ]   %s: %s\n",
			(err > 0 && err <= ERR_TOTAL) ? err_name[err] : "?UNSPECIFIED?",
			(err > 0 && err <= ERR_TOTAL) ? err_name[err] : "?UNSPECIFIED?");
}

void terminate(int err)
{
	fprintf(stderr, "[ ERROR ]   %s: %s\n", 
			(err > 0 && err <= ERR_TOTAL) ? err_name[err] : "?UNSPECIFIED?",
			(err > 0 && err <= ERR_TOTAL) ? err_msg[err]  : "?UNSPECIFIED?");
	fflush(stderr);
	exit(EXIT_FAILURE);
}
