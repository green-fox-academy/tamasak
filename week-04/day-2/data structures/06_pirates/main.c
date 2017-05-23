#include <stdio.h>

struct pirate {
    char name[256];
    int has_wooden_leg;
    short int gold_count;
};

// TODO:
// Create a function that takes an array of pirates (and it's length) then returns the sum of the golds of all pirates

int sum_gold(struct pirate *array, int length)
{
    int sum = 0;
    for (int i = 0; i < length; i++)
        sum += array[i].gold_count;
    //printf("gold %d", sum);
    return sum;
}

// TODO:
// Create a function that takes an array of pirates (and it's length) then returns the average of the gold / pirate

float average_gold(struct pirate *array, int length)
{
    float ave = sum_gold(array, length) / (float)length;
    return ave;
}

// TODO:
// Create a function that takes an array of pirates (and it's length) then returns the name of the
// richest that has wooden leg

char *richest_pirate(struct pirate *array, int length)
{
    int j = 0;
    int tmp = 0;
    for (int i = 0; i < length; i++) {
        if (array[i].has_wooden_leg != 0) {
            if (array[i].gold_count > j){
                j = array[i].gold_count;
                tmp = i;
            }
        }

    }
    /*if ((j == 0) && (array[0].has_wooden_leg != 0)) {
        j = -1;
    }*/
    //char name[256] = array[j].name;
    //printf("%c\n", name);
    return array[tmp].name;
}

int main()
{
    struct pirate pirates[] = {
        {"Jack", 0, 18},
        {"Uwe", 1, 8},
        {"Hook", 1, 12},
        {"Halloween kid", 0, 0},
        {"Sea Wolf", 1, 14},
        {"Morgan", 0, 1}
    };
    int len = sizeof(pirates) / sizeof(pirates[0]);
    printf("gold %d\n", sum_gold(pirates, len));
    printf("average %f\n", average_gold(pirates, len));
    printf("name of richest %s\n", richest_pirate(pirates, len));

    return 0;
}
