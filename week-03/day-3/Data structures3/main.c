#include <stdio.h>

enum CarType {VOLVO, TOYOTA, LAND_ROVER, TESLA};

struct Car {
  enum CarType type;
  double km;
  double gas;
};

// TODO:
// Write a function that takes a Car as an argument and prints all it's stats
// If the car is a Tesla it should not print it's gas level

void CarStats {
    struct Car Volvo = {VOLVO, 1235, 10};
    struct Car Toyota = {TOYOTA, 462, 7};
    struct Car LandRover = {LAND_ROVER, 789215, 15};
    struct Car Tesla = {TESLA, 654, 10};

}

int main() {

  return 0;
}
