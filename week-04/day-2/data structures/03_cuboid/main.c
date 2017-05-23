#include <stdio.h>

struct rectangular_cuboid {
    double a;
    double b;
    double c;
};

// TODO:
// Write a function called "GetSurface" that takes a RectangularCuboid
// and returns it's surface
double GetSurface(struct rectangular_cuboid rect)
{
    double surf = 2*(rect.a * rect.b + rect.b * rect.c + rect.a * rect.c);
    return surf;
}

// TODO:
// Write a function called "GetVolume" that takes a RectangularCuboid
// and returns it's volume
double GetVolume(struct rectangular_cuboid rect)
{
    double vol = rect.a * rect.b * rect.c;
    return vol;
}

int main()
{
    struct rectangular_cuboid rect1 = {1, 2, 3};
    printf("surface %f\n", GetSurface(rect1));
    printf("volume %f\n", GetVolume(rect1));
    return 0;
}
