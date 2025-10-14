/*
 * simulation.h
 * -------------
 * Declara as funções responsáveis pelo cálculo e simulação
 * da iluminação na cena carregada.
 *
 * As principais funções são:
 *  - computeIlluminationAt(): calcula a intensidade total de luz
 *    recebida por um ponto específico, considerando obstáculos
 *    e reduções de intensidade.
 *
 *  - simulate(): processa todos os receptores da cena e imprime
 *    suas respectivas iluminações formatadas.
 */

#ifndef SIMULATION_H
#define SIMULATION_H

#include "geometry.h"
#include "parser.h"


double computeIlluminationAt(const Scene& scene, const Point& p);


void simulate(const Scene& scene);

#endif

