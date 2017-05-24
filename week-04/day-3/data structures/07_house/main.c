#include <stdio.h>

// TODO:
// Create a struct that represents a House
// It should store:
//  - The address of the house
//  - The price in EUR
//  - The number of rooms
//  - The area of the house in square meters
struct house
{
    char address[256];
    float price;
    int rooms;
    float area;
};

// TODO:
// The market price of the houses is 400 EUR / square meters
// Create a function that takes a pointer to a house and decides if it's worth to buy
// (if the price is lower than the calculated price from it's area)
int worth_buying(struct house hou)
{
    float ppsq = hou.price / hou.area;
    if (ppsq > 400)
        return 1;
    else
        return 0;
}

// TODO:
// Create a function that takes an array of houses (and it's length), and counts the
// houses that are worth to buy.
int number_worth_buying(struct house hou[], int length)
{
    int number = 0;
    for (int i = 0; i < length; i++)
        number += worth_buying(hou[i]);
    return number;
}

int main()
{
    struct house houses[] = {
        {"gre", 4000, 2, 12},
        {"rsdfg", 50000, 1, 20},
        {"jfaspo", 12000, 2, 60},
        {"nufwpio", 8000, 3, 4},
        {"fuwion", 65000, 4, 10},
        {"kdlnhaf", 10000, 1, 18}
    };
    int len = sizeof(houses) / sizeof(houses[0]);
    printf("%d\n", number_worth_buying(houses, len));

    return 0;
}
