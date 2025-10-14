/*
 * main.cpp
 * ---------
 * Ponto de entrada do programa de simulação de luminosidade.
 * Lê a cena a partir de um arquivo de entrada ("regiao.txt"),
 * valida os dados carregados e executa a simulação de iluminação
 * nos pontos receptores definidos.
 */

#include <iostream>
#include "../include/parser.h"
#include "../include/geometry.h"
#include "../include/simulation.h"

/*
 * exportScene
 * ------------
 * (Opcional) Função auxiliar usada para exportar os dados da cena
 * (obstáculos, luzes e receptores) para depuração ou visualização externa.
 */
void exportScene(const std::vector<std::shared_ptr<Obstacle>>& obstacles,
                 const std::vector<Light>& lights,
                 const std::vector<Point>& receptors);

int main() {
    
    Scene scene = parseFile("regiao.txt");
    
    if (scene.lights.empty() || scene.points.empty()) {
        std::cerr << "⚠️  Cena incompleta: verifique se há fontes e pontos receptores no arquivo.\n";
        return 1; 
    }

    exportScene(scene.obstacles, scene.lights, scene.points);

    simulate(scene);

    return 0;
}





