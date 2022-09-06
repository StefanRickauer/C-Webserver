#include <string.h>
#include "http_status_codes.h"

void get_status_message(int code, char *msg)
{
	switch(code)
	{
		case CONTINUE:
			strcpy(msg, "100 Continue");
			break;
		case SWITCHING:
			strcpy(msg, "101 Switching Protocols");
			break;
		case PROCESSING:
			strcpy(msg, "102 Processing");
                        break;
		case EARLY_HINTS:
			strcpy(msg, "103 Early Hints");
                        break;
		case OK:
			strcpy(msg, "200 OK");
                        break;
		case CREATED:
			strcpy(msg, "201 Created");
                        break;
		case ACCEPTED:
			strcpy(msg, "202 Accepted");
                        break;
		case NON_AUTH_INFO:
			strcpy(msg, "203 Non-Authoritative Information");
                        break;
		case NO_CONTENT:
			strcpy(msg, "204 No Content");
                        break;
		case RESET_CONTENT:
			strcpy(msg, "205 Reset Content");
                        break;
		case PARTIAL_CONTENT:
			strcpy(msg, "206 Partial Content");
                        break;
		case MULTI_STATUS:
			strcpy(msg, "207 Multi-Status");
                        break;
		case AL_REP:
			strcpy(msg, "208 Already Reported");
                        break;
		case IM_USED:
			strcpy(msg, "226 IM Used");
                        break;
		case MUL_CHOICES:
			strcpy(msg, "300 Multiple Choices");
                        break;
		case MOVED_PERM:
			strcpy(msg, "301 Moved Permanently");
                        break;
		case FOUND:
			strcpy(msg, "302 Found");
                        break;
		case SEE_OTHER:
			strcpy(msg, "303 See Other");
                        break;
		case NOT_MODIFIED:
			strcpy(msg, "304 Not Modified");
                        break;
		case USE_PROXY:
			strcpy(msg, "305 Use Proxy");
                        break;
		case TEMP_REDIR:
			strcpy(msg, "307 Temporary Redirect");
                        break;
		case PERM_REDIR:
			strcpy(msg, "308 Permanent Redirect");
                        break;
		case BAD_REQUEST:
			strcpy(msg, "400 Bad Request");
                        break;
		case UNAUTHORIZED:
			strcpy(msg, "401 Unauthorized");
                        break;
		case PAYMENT_REQ:
			strcpy(msg, "402 Payment Required");
                        break;
		case FORBIDDEN:
			strcpy(msg, "403 Forbidden");
                        break;
		case NOT_FOUND:
			strcpy(msg, "404 Not Found");
                        break;
		case MET_NOT_ALLOWED:
			strcpy(msg, "405 Method Not Allowed");
                        break;
		case NOT_ACCEPTABLE:
			strcpy(msg, "406 Not Acceptable");
                        break;
		case PROX_AUTH_REQ:
			strcpy(msg, "407 Proxy Authentication Required");
                        break;
		case REQUEST_TIMEOUT:
			strcpy(msg, "408 Request Timeout");
                        break;
		case CONFLICT:
			strcpy(msg, "409 Conflict");
                        break;
		case GONE:
			strcpy(msg, "410 Gone");
                        break;
		case LENGTH_REQUIRED:
			strcpy(msg, "411 Length Required");
                        break;
		case PRECON_FAILED:
			strcpy(msg, "412 Precondition Failed");
                        break;
		case CON_TOO_LARGE:
			strcpy(msg, "413 Content Too Large");
                        break;
		case URI_TOO_LONG:
			strcpy(msg, "414 URI Too Long");
                        break;
		case UNSUPP_MED_TYPE:
			strcpy(msg, "415 Unsupported Media Type");
                        break;
		case RAN_NOT_SATIS:
			strcpy(msg, "416 Range Not Satisfiable");
                        break;
		case EXPEC_FAILED:
			strcpy(msg, "417 Expectation Failed");
                        break;
		case MISDIR_REQ:
			strcpy(msg, "421 Misdirected Request");
                        break;
		case UNPROCSS_CONT:
			strcpy(msg, "422 Unprocessable Content");
                        break;
		case LOCKED:
			strcpy(msg, "423 Locked");
                        break;
		case FAILED_DEPEN:
			strcpy(msg, "424 Failed Dependency");
                        break;
		case TOO_EARLY:
			strcpy(msg, "425 Too Early");
                        break;
		case UPGRADE_REQ:
			strcpy(msg, "426 Upgrade Required");
                        break;
		case PRECON_REQ:
			strcpy(msg, "428 Precondition Required");
                        break;
		case TOO_MANY_REQ:
			strcpy(msg, "429 Too Many Requests");
                        break;
		case REQ_HDR_TOO_LAR:
			strcpy(msg, "431 Request Header Fields Too Large");
                        break;
		case UNAV_FOR_LEG_P:
			strcpy(msg, "451 Unavailable For Legal Reasons");
                        break;
		case INTERNAL_ERROR:
			strcpy(msg, "500 Internal Server Error");
                        break;
		case NOT_IMPLEMENTED:
			strcpy(msg, "501 Not Implemented");
                        break;
		case BAD_GATEWAY:
			strcpy(msg, "502 Bad Gateway");
                        break;
		case SERV_UNAVAIL:
			strcpy(msg, "503 Service Unavailable");
                        break;
		case GATEWAY_TIMEOUT:
			strcpy(msg, "504 Gateway Timeout");
                        break;
		case HTTP_VERS_N_SUP:
			strcpy(msg, "505 HTTP Version Not Supported");
                        break;
		case VAR_ALSO_NEG:
			strcpy(msg, "506 Variant Also Negotiates");
                        break;
		case INSUFFICIENT_ST:
			strcpy(msg, "507 Insufficient Storage");
                        break;
		case LOOP_DETECTED:
			strcpy(msg, "508 Loop Detected");
                        break;
		case NET_AUTH_REQ:
			strcpy(msg, "511 Network Authentication Required");
                        break;
		default:
			strcpy(msg, "500 Internal Server Error");
			break;
	}
}
