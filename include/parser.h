/*
 * parser.h
 * ---------
 * Declara as estruturas e funções responsáveis por ler o arquivo de entrada
 * e construir a cena utilizada na simulação de iluminação.
 *
 * A função principal `parseFile()` interpreta cada linha do arquivo de texto,
 * criando os objetos correspondentes:
 *  - Obstáculos (retângulos, círculos e linhas)
 *  - Fontes de luz
 *  - Pontos receptores
 *
 * O resultado é retornado dentro de uma estrutura `Scene`,
 * que agrupa todos os elementos necessários para a simulação.
 */

#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
#include <memory>
#include "geometry.h"

// Representa todos os elementos da cena carregada a partir do arquivo
struct Scene {
    std::vector<Light> lights;                         
    std::vector<Point> points;                         
    std::vector<std::shared_ptr<Obstacle>> obstacles;  
};

// Lê o arquivo especificado e retorna uma cena construída a partir dele
Scene parseFile(const std::string& filename);

#endif

