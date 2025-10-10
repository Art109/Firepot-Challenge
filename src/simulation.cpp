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

        for (auto& obs : scene.obstacles) {
            int crossings = obs->countIntersections(light.pos, p.pos);
            bool aInside = obs->isInside(light.pos);
            bool bInside = obs->isInside(p.pos);

            int totalReductions = crossings;
            if (totalReductions == 0 && (aInside != bInside))
                totalReductions = 1;

            if (totalReductions > 0) {
                double factor = 1.0 - obs->reduction / 100.0;
                intensity *= pow(factor, totalReductions);
            }

            // Debug opcional
            /*
            cerr << "Obs " << obs->id
                 << " | red=" << obs->reduction
                 << " | crossings=" << crossings
                 << " | insideA=" << aInside
                 << " | insideB=" << bInside
                 << " | totalRed=" << totalReductions
                 << " | factor=" << (1.0 - obs->reduction / 100.0)
                 << " | intensity=" << intensity
                 << endl;
            */
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

    // Ordena os pontos por ID
    sort(results.begin(), results.end(),
         [](auto& a, auto& b) { return a.first < b.first; });

    // Imprime formatado
    for (auto& r : results) {
        cout << "P" << r.first << " = " 
             << fixed << setprecision(2) << r.second << endl;
    }
}
