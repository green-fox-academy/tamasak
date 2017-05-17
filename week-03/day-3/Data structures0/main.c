#include <stdio.h>
#include <stdint.h>

struct Bitfield{
    uint8_t boolean_value_1:1;
    uint8_t boolean_value_2:1;
    uint8_t boolean_value_3:1;
    uint8_t boolean_value_4:1;
    uint8_t boolean_value_5:1;
    uint8_t boolean_value_6:1;
    uint8_t boolean_value_7:1;
    uint8_t boolean_value_8:1;
};

struct NotBitfield{
    uint8_t boolean_value_1;
    uint8_t boolean_value_2;
    uint8_t boolean_value_3;
    uint8_t boolean_value_4;
    uint8_t boolean_value_5;
    uint8_t boolean_value_6;
    uint8_t boolean_value_7;
    uint8_t boolean_value_8;
};

int main() {
    // TODO:
    // Print out the size of both structs (use sizeof() function)
    struct Bitfield Bitfield1;
    int a = sizeof(Bitfield1);
    printf("Size of Bitfield: %d\n",a);

    struct NotBitfield NotBitfield1;
    int b = sizeof(NotBitfield1);
    printf("Size of NotBitfield: %d\n",b);

    return 0;
}
