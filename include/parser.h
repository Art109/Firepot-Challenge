#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
#include <memory>
#include "geometry.h"

using namespace std;

struct Scene {
    vector<Light> lights;
    vector<Point> points;
    vector<std::shared_ptr<Obstacle>> obstacles;
};

Scene parseFile(const string& filename);

#endif
