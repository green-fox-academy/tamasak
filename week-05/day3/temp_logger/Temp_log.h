// Multiple inclusion guard
#include <stdint.h>

#ifndef _TEMP_LOG_H
#define _TEMP_LOG_H
void print_usage(void);
void init_templog(void);
void list_ports(void);
char *set_port_name(void);
void set_write_file(void);
void open_port(void);
void start_stop_log(int log);
char port[80];
char path[100];

#endif // _TC74_DRIVER_H
