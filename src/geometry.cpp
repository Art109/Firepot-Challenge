/*
 * geometry.cpp
 * -------------
 * Implementa as classes geométricas básicas usadas na simulação:
 *  - Rectangle, Circle e Line (todos derivados de Obstacle)
 *  - Funções auxiliares para cálculos de interseção e ponto interno.
 * 
 * Essas classes definem como a luz interage com os obstáculos da cena.
 */

#include "../include/geometry.h"
#include <cmath>
#include <vector>
#include <algorithm>

// ------------------------------------------------------------
// Funções utilitárias para geometria de interseção de segmentos
// ------------------------------------------------------------

// Produto vetorial 2D — determina a orientação entre três pontos
static double cross(const Vector2& A, const Vector2& B, const Vector2& C) {
    return (B.x - A.x) * (C.y - A.y) - (B.y - A.y) * (C.x - A.x);
}

// Testa se dois segmentos (A,B) e (C,D) se intersectam
static bool segmentsIntersect(const Vector2& A, const Vector2& B,
                              const Vector2& C, const Vector2& D) {
    double d1 = cross(A, B, C);
    double d2 = cross(A, B, D);
    double d3 = cross(C, D, A);
    double d4 = cross(C, D, B);

    const double EPS = 1e-9;

    // Caso geral: sinais opostos => interseção
    if ((d1 * d2) < -EPS && (d3 * d4) < -EPS)
        return true;

    // Casos degenerados: pontos colineares
    auto onSegment = [&](const Vector2& P, const Vector2& Q, const Vector2& R) {
        return (std::min(P.x, R.x) - EPS <= Q.x && Q.x <= std::max(P.x, R.x) + EPS &&
                std::min(P.y, R.y) - EPS <= Q.y && Q.y <= std::max(P.y, R.y) + EPS);
    };

    if (std::fabs(d1) < EPS && onSegment(A, C, B)) return true;
    if (std::fabs(d2) < EPS && onSegment(A, D, B)) return true;
    if (std::fabs(d3) < EPS && onSegment(C, A, D)) return true;
    if (std::fabs(d4) < EPS && onSegment(C, B, D)) return true;

    return false;
}

// ------------------------------------------------------------
// Classe Rectangle
// ------------------------------------------------------------

Rectangle::Rectangle(int id, int reduction, int x, int y, int height , int width) {
    this->id = id;
    this->reduction = reduction;
    this->origin = {x, y};
    this->width = width;
    this->height = height;
}

int Rectangle::countIntersections(const Vector2& a, const Vector2& b) const {
    std::vector<Vector2> v = {
        {origin.x, origin.y},
        {origin.x + width, origin.y},
        {origin.x + width, origin.y + height},
        {origin.x, origin.y + height}
    };

    int count = 0;
    for (int i = 0; i < 4; i++)
        if (segmentsIntersect(a, b, v[i], v[(i + 1) % 4])) count++;

    // Limita a contagem a 2 (entrada e saída)
    return std::min(count, 2);
}

// ------------------------------------------------------------
// Classe Circle
// ------------------------------------------------------------

Circle::Circle(int id, int reduction, int x, int y, int r) {
    this->id = id;
    this->reduction = reduction;
    this->center = {x, y};
    this->radius = r;
}

int Circle::countIntersections(const Vector2& a, const Vector2& b) const {
    Vector2 d = {b.x - a.x, b.y - a.y};
    Vector2 f = {a.x - center.x, a.y - center.y};

    double A = d.x * d.x + d.y * d.y;
    double B = 2 * (f.x * d.x + f.y * d.y);
    double C = f.x * f.x + f.y * f.y - radius * radius;

    double disc = B * B - 4 * A * C;
    if (disc < 0) return 0; // sem interseção real

    disc = sqrt(disc);
    double t1 = (-B - disc) / (2 * A);
    double t2 = (-B + disc) / (2 * A);

    int count = 0;
    if (t1 >= 0 && t1 <= 1) count++;
    if (t2 >= 0 && t2 <= 1) count++;
    return std::min(count, 2);
}

// ------------------------------------------------------------
// Classe Line
// ------------------------------------------------------------

Line::Line(int id, int reduction, int x1, int y1, int x2, int y2) {
    this->id = id;
    this->reduction = reduction;
    this->p1 = {x1, y1};
    this->p2 = {x2, y2};
}

int Line::countIntersections(const Vector2& a, const Vector2& b) const {
    return segmentsIntersect(a, b, p1, p2) ? 1 : 0;
}



