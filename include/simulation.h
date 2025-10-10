#ifndef SIMULATION_H
#define SIMULATION_H

#include "geometry.h"
#include "parser.h"

double computeIlluminationAt(const Scene& scene, const Point& p);
void simulate(const Scene& scene);

#endif
