#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include "rs232.h"

void run_program()
{
    comEnumerate();
    comOpen(0, 115200);
    //start_stop_log();

}
int main()
{
    run_program();
    char buff_temp;
    while(1) {
        /*time ( &rawtime );
        timeinfo = localtime ( &rawtime );*/
        //sleep (2);
        /*time_t timer;
        char buffer[26];
        struct tm* tm_info;
        time(&timer);
        tm_info = localtime(&timer);
        strftime(buffer, 26, "%Y-%m-%d %H:%M:%S", tm_info);
        puts(buffer);*/
        FILE *file = fopen("rpm.log","a");
        while (comRead(0, &buff_temp, 1) == 0) {
        }
        printf("%c", buff_temp);
        fprintf(file, "%c", buff_temp);
        /*while (comRead(0, &buff_temp, 1) == 0) {
        }
        printf("%c", buff_temp);
        fprintf(file, "%c", buff_temp);
        while (comRead(0, &buff_temp, 1) == 0) {
        }
        printf("%c", buff_temp);
        fprintf(file, "%c", buff_temp);*/
        fclose(file);
        //i=kbhit();
    }
}
