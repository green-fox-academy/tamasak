#include <stdio.h>

struct RectangularCuboid {
    double a;
    double b;
    double c;
};

// TODO:
// Write a function called "GetSurface" that takes a RectangularCuboid
// and returns it's surface
double GetSurface(struct RectangularCuboid rectang1) {
    double surface;
    surface = 2*rectang1.a*rectang1.b + 2*rectang1.a*rectang1.c +2*rectang1.c*rectang1.b;
    return surface;

}

// TODO:
// Write a function called "GetVolume" that takes a RectangularCuboid
// and returns it's volume
double GetVolume(struct RectangularCuboid rectang1) {
    double volume;
    volume = rectang1.a * rectang1.b * rectang1.c;
    return volume;
}

int main() {
    struct RectangularCuboid rectang1 = {2, 3, 4};

    printf("The surface of the rectangular is %f.\n", GetSurface(rectang1));
    printf("The volume of the rectangular is %f.\n", GetVolume(rectang1));

    return 0;
}
