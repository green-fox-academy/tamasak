#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>


int main()
{
    system("ping -c 3 google.com | tail -1| awk '{print $4}' | cut -d '/' -f 2");
    return 0;
}
