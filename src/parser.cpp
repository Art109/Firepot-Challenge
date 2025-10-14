/*
 * parser.cpp
 * -----------
 * Responsável por interpretar o arquivo de entrada que descreve a cena.
 * Cada linha define um elemento: obstáculo (R, C, L), fonte (F) ou ponto (P).
 * O parser converte essas informações em objetos e os armazena na estrutura `Scene`.
 */

#include "../include/parser.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <limits>

using namespace std;

Scene parseFile(const string& filename) {
    Scene scene;
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Erro: não foi possível abrir o arquivo '" << filename << "'." << endl;
        return scene; 
    }

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue; 
        stringstream ss(line);

        char type;
        ss >> type;

        switch (type) {
            case 'R': { // Retângulo
                int id, reduction, x, y, width, height;
                if (!(ss >> id >> reduction >> x >> y >> width >> height)) {
                    cerr << "Aviso: linha inválida para retângulo. Ignorada." << endl;
                    continue;
                }
                auto rect = make_shared<Rectangle>(id, reduction, x, y, width, height);
                scene.obstacles.push_back(rect);
                break;
            }

            case 'C': { // Círculo
                int id, reduction, x, y, r;
                if (!(ss >> id >> reduction >> x >> y >> r)) {
                    cerr << "Aviso: linha inválida para círculo. Ignorada." << endl;
                    continue;
                }
                auto circle = make_shared<Circle>(id, reduction, x, y, r);
                scene.obstacles.push_back(circle);
                break;
            }

            case 'L': { // Linha
                int id, reduction, x1, y1, x2, y2;
                if (!(ss >> id >> reduction >> x1 >> y1 >> x2 >> y2)) {
                    cerr << "Aviso: linha inválida para linha. Ignorada." << endl;
                    continue;
                }
                auto lineObj = make_shared<Line>(id, reduction, x1, y1, x2, y2);
                scene.obstacles.push_back(lineObj);
                break;
            }

            case 'F': { // Fonte de luz
                int id, x, y;
                double intensity;
                if (!(ss >> id >> intensity >> x >> y)) {
                    cerr << "Aviso: linha inválida para fonte de luz. Ignorada." << endl;
                    continue;
                }
                scene.lights.push_back({id, intensity, {x, y}});
                break;
            }

            case 'P': { // Ponto receptor
                int id, x, y;
                if (!(ss >> id >> x >> y)) {
                    cerr << "Aviso: linha inválida para ponto receptor. Ignorada." << endl;
                    continue;
                }
                scene.points.push_back({id, {x, y}});
                break;
            }

            default:
                cerr << "Aviso: comando desconhecido '" << type << "'. Linha ignorada." << endl;
                break;
        }
    }

    file.close();
    return scene;
}

