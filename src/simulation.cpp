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
            // Caso apenas uma das extremidades esteja dentro, conta como uma redução caso não tenha sido detectado nenhuma interseção
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

void simulate(const Scene& scene) {
    vector<pair<int, double>> results;

    for (auto& p : scene.points) {
        double lum = computeIlluminationAt(scene, p);
        results.push_back({p.id, lum});
    }

    sort(results.begin(), results.end(),
         [](auto& a, auto& b) { return a.first < b.first; });

    for (auto& r : results) {
        cout << "P" << r.first << " = "
             << fixed << setprecision(2) << r.second << endl;
    }
}

