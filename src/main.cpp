#include <iostream>
#include "../include/parser.h"
#include "../include/geometry.h"
#include "../include/simulation.h"

// Declaração da função de exportação
void exportScene(const std::vector<std::shared_ptr<Obstacle>>& obstacles,
                 const std::vector<Light>& lights,
                 const std::vector<Point>& receptors);


int main() {
    Scene scene = parseFile("regiao.txt");

    if (!scene.points.empty()) {
    exportScene(scene.obstacles, scene.lights, scene.points); // passa o vetor inteiro
}


    simulate(scene);
    return 0;
}




