#include "../include/parser.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

Scene parseFile(const string& filename) {
    Scene scene;
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Erro ao abrir o arquivo: " << filename << endl;
        return scene;
    }

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue; // ignora linhas em branco
        stringstream ss(line);

        char type;
        ss >> type;

        switch (type) {
            case 'R': {
                int id, reduction, x, y, width, height;
                ss >> id >> reduction >> x >> y >> width >> height;
                auto rect = make_shared<Rectangle>(id, reduction, x, y, width, height);
                scene.obstacles.push_back(rect);
                break;
            }

            case 'C': {
                int id, reduction, x, y, r;
                ss >> id >> reduction >> x >> y >> r;
                auto circle = make_shared<Circle>(id, reduction, x, y, r);
                scene.obstacles.push_back(circle);
                break;
            }

            case 'L': {
                int id, reduction, x1, y1, x2, y2;
                ss >> id >> reduction >> x1 >> y1 >> x2 >> y2;
                auto lineObj = make_shared<Line>(id, reduction, x1, y1, x2, y2);
                scene.obstacles.push_back(lineObj);
                break;
            }

            case 'F': {
                int id, x, y;
                double intensity;
                ss >> id >> intensity >> x >> y;
                scene.lights.push_back({id, intensity, {x, y}});
                break;
            }

            case 'P': {
                int id, x, y;
                ss >> id >> x >> y;
                scene.points.push_back({id, {x, y}});
                break;
            }

            default:
                cerr << "Comando desconhecido: " << type << endl;
                break;
        }
    }

    file.close();
    return scene;
}
