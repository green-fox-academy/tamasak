#include <stdio.h>

/* Write a void function which can print the following text on the screen:
------------
-- TOTORO --
------------
- GREENFOX -
------------
Name this function as "TotoroLogoPrinter" and call it from the main function!*/

void totoroLogoPrinter();

int main() {

    totoroLogoPrinter();

    return 0;
}

void totoroLogoPrinter() {

    printf("------------\n-- TOTORO --\n------------\n- GREENFOX -\n------------\n");

    return 0;
}
