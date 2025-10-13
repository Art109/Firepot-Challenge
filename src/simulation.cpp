/*
 * simulation.cpp
 * ---------------
 * Responsável por executar a simulação de iluminação da cena.
 * Para cada ponto receptor, calcula a intensidade total recebida
 * de todas as fontes luminosas, considerando os obstáculos no caminho.
 *
 * Saída final: apenas os valores de luminosidade no formato:
 *     P<id> = <valor>
 */

#include "../include/simulation.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>

using namespace std;

/*
 * computeIlluminationAt
 * ----------------------
 * Calcula a intensidade total de luz recebida em um ponto receptor `p`.
 * Cada fonte de luz tem sua intensidade reduzida conforme os obstáculos
 * atravessados entre a fonte e o ponto. O número de interseções e a
 * taxa de redução de cada obstáculo determinam a atenuação.
 */
double computeIlluminationAt(const Scene& scene, const Point& p) {
    double total = 0.0;

    for (auto& light : scene.lights) {
        double intensity = light.intensity;

        // Percorre todos os obstáculos e aplica reduções conforme interseções
        for (auto& obs : scene.obstacles) {
            int crossings = obs->countIntersections(light.pos, p.pos);
            bool aInside = obs->isInside(light.pos);
            bool bInside = obs->isInside(p.pos);

            int totalReductions = crossings;
            // Caso apenas uma das extremidades esteja dentro, conta como uma redução
            if (totalReductions == 0 && (aInside != bInside)) {
                totalReductions = 1;
            }

            if (totalReductions > 0) {
                double factor = pow(1 - obs->reduction / 100.0, totalReductions);
                intensity *= factor;
            }
        }

        total += intensity;
    }

    return total;
}

/*
 * simulate
 * --------
 * Executa a simulação para todos os pontos receptores e imprime o resultado.
 * Cada linha da saída representa um ponto no formato:
 *     P<id> = <valor com duas casas decimais>
 */
void simulate(const Scene& scene) {
    vector<pair<int, double>> results;

    // Calcula a luminosidade em cada ponto
    for (auto& p : scene.points) {
        double lum = computeIlluminationAt(scene, p);
        results.push_back({p.id, lum});
    }

    // Ordena os resultados por ID para saída consistente
    sort(results.begin(), results.end(),
         [](auto& a, auto& b) { return a.first < b.first; });

    // Imprime resultados formatados
    for (auto& r : results) {
        cout << "P" << r.first << " = "
             << fixed << setprecision(2) << r.second << endl;
    }
}

