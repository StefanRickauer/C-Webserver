#include <string.h>
#include <time.h>

#include "gmt_date.h"

void get_gmt_date_string(char *date)
{
	char w_day[SINGLE_DATE_LEN], day[SINGLE_DATE_LEN], 
	     month[SINGLE_DATE_LEN], year[SINGLE_DATE_LEN], time_of_day[SINGLE_DATE_LEN];
	time_t actual_time;
	struct tm *gmt;

	time(&actual_time);
	gmt = gmtime(&actual_time);

	strftime(w_day       , SINGLE_DATE_LEN, "%a", gmt);
	strftime(day         , SINGLE_DATE_LEN, "%d", gmt);
	strftime(month       , SINGLE_DATE_LEN, "%b", gmt);
	strftime(year        , SINGLE_DATE_LEN, "%Y", gmt);
	strftime(time_of_day , SINGLE_DATE_LEN, "%T", gmt);

	strcpy(date, "Date: ");
	strcat(date, w_day);
	strcat(date, ", ");
	strcat(date, day);
	strcat(date, " ");
	strcat(date, month);
	strcat(date, " ");
	strcat(date, year);
	strcat(date, " ");
	strcat(date, time_of_day);
	strcat(date, " GMT\n");
}
