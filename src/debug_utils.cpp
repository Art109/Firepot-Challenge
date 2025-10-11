#include <fstream>
#include <iostream>
#include <vector>
#include "../include/geometry.h"
#include "../include/parser.h"

// Agora recebe vários receptores
void exportScene(const std::vector<std::shared_ptr<Obstacle>>& obstacles,
                 const std::vector<Light>& lights,
                 const std::vector<Point>& receptors) {

    std::ofstream out("scene_debug.txt");
    if (!out.is_open()) {
        std::cerr << "Erro ao salvar scene_debug.txt\n";
        return;
    }

    out << "OBSTACULOS\n";
    for (auto& o : obstacles) {
        if (auto* c = dynamic_cast<Circle*>(o.get())) {
            out << "C " << c->center.x << " " << c->center.y << " " << c->radius << "\n";
        } else if (auto* r = dynamic_cast<Rectangle*>(o.get())) {
            out << "R " << r->origin.x << " " << r->origin.y << " "
                << r->width << " " << r->height << "\n";
        } else if (auto* l = dynamic_cast<Line*>(o.get())) {
            out << "L " << l->p1.x << " " << l->p1.y << " "
                << l->p2.x << " " << l->p2.y << "\n";
        }
    }

    out << "LIGHTS\n";
    for (auto& l : lights)
        out << "F " << l.pos.x << " " << l.pos.y << " " << l.intensity << "\n";

    out << "POINTS\n";
    for (auto& p : receptors)
        out << "P " << p.pos.x << " " << p.pos.y << "\n";

    out.close();
    std::cout << "✅ Cena exportada para scene_debug.txt!\n";
}





