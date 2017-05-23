#include <stdio.h>

enum car_type {VOLVO, TOYOTA, LAND_ROVER, TESLA};

struct car {
    enum car_type type;
    double km;
    double gas;
};

// TODO:
// Write a function that takes a Car as an argument and prints all it's stats
// If the car is a Tesla it should not print it's gas level

void print_stats(struct car show)
{
    printf("%d\n%f\n",show.type,show.km);
    if (show.type != TESLA)
        printf("%f\n",show.gas);
}

int main()
{
    struct car vol = {VOLVO, 10, 32};
    struct car tes = {TESLA, 60};
    print_stats(tes);

    return 0;
}
