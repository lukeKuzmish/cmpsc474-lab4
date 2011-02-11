/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  lab4.c
  Coded by      LUKE KUZMISH
       for      Dr. Su, CMPSC 474

                a simple "who" utility made with function calls
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <unistd.h>
#include <fcntl.h>
#include <utmp.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#define ut_time ut_tv.tv_sec

int main () {
    /* 
        read through /var/run/utmp (read only mode)
        skip unneeded data with lseek sizeof(struct/data type)
        display data needed usefully
        read til the end of the file
    */
    
    int i;                      /* iterator */
    char readableTime[20];      /* holds string rep of logon time */
    struct tm tm_time;          /* temporarily holds logon time in tm format */
    struct utmp current_record; 
    int UTMP_BUFFER = sizeof(struct utmp);
    int moreToRead = 1;
    int utmp_file = open("/var/run/utmp", O_RDONLY);

    while (moreToRead > 0) {
    
    moreToRead = read(utmp_file, &current_record, UTMP_BUFFER);
    
        if ((moreToRead > 0) && (current_record.ut_type == USER_PROCESS)) {

                    /* display next record if there is a record waiting in
                       the buffer AND the user is logged */

                    printf("%s\t", current_record.ut_user);
                    printf("%s\t", current_record.ut_line);

                    gmtime_r(&current_record.ut_time, &tm_time); 
                    strftime (readableTime, 20, "%Y-%m-%d %H:%M", &tm_time);
                    readableTime[strlen(readableTime)-1] = 0; /* ctime adds \n, this line removes it */
        
                    printf("%s  ", readableTime);
                    printf("(%s)\n", current_record.ut_host);
            }
    }
    return 0;
}
