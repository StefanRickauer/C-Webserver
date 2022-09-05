#ifndef _HTTP_ERROR_CODES_H
#define _HTTP_ERROR_CODES_H

// Informal Responses

#define CONTINUE 	100
#define SWITCHING 	101
#define PROCESSING	102
#define EARLY_HINTS	103

// Successful Responses
#define OK 		200
#define CREATED		201
#define ACCEPTED	202
#define NON_AUTH_INFO	203
#define NO_CONTENT	204
#define RESET_CONTENT	205
#define PARTIAL_CONTENT 206
#define MULTI_STATUS	207
#define AL_REP		208
#define IM_USED		226

// Redirection Messages
#define MUL_CHOICES 	300
#define MOVED_PERM	301
#define FOUND		302
#define SEE_OTHER	303
#define NOT_MODIFIED	304
#define USE_PROXY	305
#define TEMP_REDIR	307
#define PERM_REDIR	308

// Client Error Responses
#define BAD_REQUEST	400
#define UNAUTHORIZED	401
#define PAYMENT_REQ	402
#define FORBIDDEN	403
#define NOT_FOUND	404
#define MET_NOT_ALLOWED 405
#define NOT_ACCEPTABLE 	406
#define PROX_AUTH_REQ	407
#define REQUEST_TIMEOUT	408
#define CONFLICT	409
#define GONE		410
#define LENGTH_REQUIRED 411
#define PRECON_FAILED	412
#define CON_TOO_LARGE	413
#define URI_TOO_LONG	414
#define UNSUPP_MED_TYPE	415
#define RAN_NOT_SATIS	416
#define EXPEC_FAILED	417
#define MISDIR_REQ	421
#define UNPROCSS_CONT	422
#define LOCKED		423
#define FAILED_DEPEN	424
#define TOO_EARLY	425
#define UPGRADE_REQ	426
#define PRECON_REQ	428
#define TOO_MANY_REQ	429
#define REQ_HDR_TOO_LAR	431
#define UNAV_FOR_LEG_P	451

// Server Error Responses
#define INTERNAL_ERROR	500
#define NOT_IMPLEMENTED 501
#define BAD_GATEWAY	502
#define SERV_UNAVAIL	503
#define GATEWAY_TIMEOUT 504
#define HTTP_VERS_N_SUP	505
#define VAR_ALSO_NEG	506
#define INSUFFICIENT_ST	507
#define LOOP_DETECTED 	508
#define NET_AUTH_REQ	511

void get_error_message(int , char *);

#endif

