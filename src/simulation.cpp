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

        cerr << "\nFonte " << light.id 
     << " | inicial=" << intensity
     << " | (" << light.pos.x << "," << light.pos.y << ") -> ("
     << p.pos.x << "," << p.pos.y << ")\n";

     cerr << "Tipos de obstáculos na cena:\n";
for (auto& o : scene.obstacles) {
    cerr << "  Obs " << o->id << " | tipo=" 
         << (dynamic_cast<Rectangle*>(o.get()) ? "Rect" :
             dynamic_cast<Circle*>(o.get()) ? "Circ" :
             dynamic_cast<Line*>(o.get()) ? "Line" : "??")
         << "\n";
}



        for (auto& obs : scene.obstacles) {
            int crossings = obs->countIntersections(light.pos, p.pos);
            bool aInside = obs->isInside(light.pos);
            bool bInside = obs->isInside(p.pos);

            int totalReductions = crossings;
            if (totalReductions == 0 && (aInside != bInside)) {
                totalReductions = 1;
            }

            if (totalReductions > 0) {
                double factor = 1 - obs->reduction / 100.0;
                double before = intensity;
                intensity *= pow(factor, totalReductions);

                cerr << "  Obs " << obs->id
                     << " | tipo=" 
                     << (dynamic_cast<Rectangle*>(obs.get()) ? "Rect" :
                         dynamic_cast<Circle*>(obs.get()) ? "Circ" :
                         dynamic_cast<Line*>(obs.get()) ? "Line" : "??")
                     << " | red=" << obs->reduction
                     << " | crossings=" << crossings
                     << " | insideA=" << aInside
                     << " | insideB=" << bInside
                     << " | totalRed=" << totalReductions
                     << " | fator aplicado=" << pow( 1 - obs->reduction/100.0, totalReductions)
                     << " | " << before << " -> " << intensity
                     << "\n";
            }
        }

        cerr << "  -> intensidade final da fonte " << light.id 
             << " = " << intensity << "\n";

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
