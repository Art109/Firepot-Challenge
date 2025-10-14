/*
 * geometry.h
 * -----------
 * Define todas as estruturas geométricas utilizadas na simulação de iluminação:
 *  - Vetores e pontos bidimensionais
 *  - Fontes de luz e receptores
 *  - Obstáculos (retângulo, círculo e linha)
 *
 * Cada obstáculo implementa o método virtual:
 *  - countIntersections(): calcula quantas vezes um raio atravessa o obstáculo.
 *  
 *
 * Essas classes fornecem a base geométrica para o cálculo da iluminação
 * no módulo "simulation.cpp".
 */

#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <cmath>
#include <vector>
#include <memory>

// Representa um ponto ou vetor em 2D
struct Vector2 {
    int x, y;
    Vector2(int x = 0, int y = 0) : x(x), y(y) {}
};

// Estrutura que define uma fonte de luz
struct Light {
    int id;
    double intensity; // intensidade da luz
    Vector2 pos;      // posição da fonte
};

// Estrutura que define um ponto receptor
struct Point {
    int id;
    Vector2 pos;      // posição do receptor
};

// Classe base abstrata para qualquer tipo de obstáculo
class Obstacle {
public:
    int id;
    int reduction; // redução percentual da luz ao atravessar o obstáculo

    // Retorna o número de interseções entre o obstáculo e o segmento (a, b)
    virtual int countIntersections(const Vector2& a, const Vector2& b) const = 0;

    

    virtual ~Obstacle() = default;
};

// Representa um retângulo na cena
class Rectangle : public Obstacle {
public:
    Vector2 origin; // canto superior esquerdo
    int width, height;

    Rectangle(int id, int reduction, int x, int y, int height , int width);
    int countIntersections(const Vector2& a, const Vector2& b) const override;
    
};

// Representa um círculo na cena
class Circle : public Obstacle {
public:
    Vector2 center;
    int radius;

    Circle(int id, int reduction, int x, int y, int r);
    int countIntersections(const Vector2& a, const Vector2& b) const override;
    
};

// Representa uma linha (segmento) na cena
class Line : public Obstacle {
public:
    Vector2 p1, p2;

    Line(int id, int reduction, int x1, int y1, int x2, int y2);
    int countIntersections(const Vector2& a, const Vector2& b) const override;
    
};

#endif

