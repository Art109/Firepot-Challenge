#include <iostream>
#include "../include/parser.h"

using namespace std;

#include "../include/geometry.h"
#include "../include/simulation.h"

int main() {
    Scene scene = parseFile("regiao.txt");
    simulate(scene);
    return 0;
}


