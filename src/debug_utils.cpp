/*
 * export_scene.cpp
 * -----------------
 * Responsável por gerar o arquivo auxiliar "scene_debug.txt",
 * usado para visualização da cena em ferramentas externas.
 * 
 * Caso o arquivo não possa ser criado, o erro é reportado,
 * mas nenhuma mensagem é exibida quando a exportação é bem-sucedida
 * (para manter a saída principal limpa).
 */

#include <fstream>
#include <iostream>
#include <vector>
#include "../include/geometry.h"
#include "../include/parser.h"

/**
 * @brief Exporta os objetos da cena para um arquivo texto legível.
 * 
 * O arquivo gerado ("scene_debug.txt") contém três seções:
 *   - OBSTACULOS: círculos, retângulos e linhas
 *   - LIGHTS: posições e intensidades das fontes
 *   - POINTS: receptores de luz
 *
 * @param obstacles Lista de obstáculos da cena
 * @param lights Fontes de luz
 * @param receptors Pontos receptores
 */
void exportScene(const std::vector<std::shared_ptr<Obstacle>>& obstacles,
                 const std::vector<Light>& lights,
                 const std::vector<Point>& receptors) {
    std::ofstream out("scene_debug.txt");
    
    if (!out.is_open()) {
        std::cerr << "❌ Erro: não foi possível criar o arquivo 'scene_debug.txt'.\n";
        return;
    }

    out << "OBSTACULOS\n";
    for (auto& o : obstacles) {
        if (auto* c = dynamic_cast<Circle*>(o.get())) {
            out << "C " << c->center.x << " " << c->center.y << " " << c->radius << "\n";
        } else if (auto* r = dynamic_cast<Rectangle*>(o.get())) {
            out << "R " << r->origin.x << " " << r->origin.y << " "
                << r->height << " " << r->width << "\n";
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
}






