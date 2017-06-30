#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

//void test_thread (void);



#endif // MAIN_H_INCLUDED

typedef struct {
    char name[255];
    uint32_t ipaddress;
    int port;
} user_info;

typedef struct {
    user_info array[50];
    int length;
} info_storeage;
